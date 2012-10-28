/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#include "transpolewaitingtimehelper.h"
#include "abstractwaitingtimehelper_p.h"

#include <QtCore/QRegExp>
#include <QtCore/QStringList>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkReply>

#include "common/journeyandwaitingtime.h"
#include "debug.h"

namespace PublicTransportation
{

namespace Provider
{

class TranspoleWaitingTimeHelperPrivate: public PluginHelper::AbstractWaitingTimeHelperPrivate
{
public:
    TranspoleWaitingTimeHelperPrivate(TranspoleWaitingTimeHelper *q);
    virtual void processReply(QNetworkReply *reply);
    virtual void cleanup();
    void performFirstPhase(QNetworkReply *reply);
    void performSecondPhase(const QString &request);
    QString ran;
private:
    Q_DECLARE_PUBLIC(TranspoleWaitingTimeHelper)
};

TranspoleWaitingTimeHelperPrivate::TranspoleWaitingTimeHelperPrivate(TranspoleWaitingTimeHelper *q):
    PluginHelper::AbstractWaitingTimeHelperPrivate(q)
{
}

void TranspoleWaitingTimeHelperPrivate::processReply(QNetworkReply *reply)
{
    // If ran is not here, need to get the ran and
    // perform the phase 2 in getting information
    if (ran.isEmpty()) {
        performFirstPhase(reply);
    } else {
        PluginHelper::AbstractWaitingTimeHelperPrivate::processReply(reply);
    }
}

void TranspoleWaitingTimeHelperPrivate::cleanup()
{
    AbstractOnlineHelperPrivate::cleanup();
}

void TranspoleWaitingTimeHelperPrivate::performFirstPhase(QNetworkReply *reply)
{
    QString request = repliesAndRequests.value(reply);

    QRegExp ranRegExp ("ran: (\\d*)");
    while (!reply->atEnd()) {
        QString data = reply->readLine();
        if (data.indexOf(ranRegExp) != -1) {
            ran = ranRegExp.cap(1);
            break;
        }
    }

    // Send the second phase request
    performSecondPhase(request);
}

void TranspoleWaitingTimeHelperPrivate::performSecondPhase(const QString &request)
{
    Q_Q(TranspoleWaitingTimeHelper);
    QString fullId = station.properties().value("id").toString();
    QStringList idAndLigneSens = fullId.split("_");
    QString id = idAndLigneSens.at(0);

    QString urlString = "http://www.transpole.mobi/index.php?id=690";

    QByteArray postData = "a=refresh&refs=";
    postData.append(QUrl::toPercentEncoding(id));
    postData.append("&ran=");
    postData.append(QUrl::toPercentEncoding(ran));

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(urlString));

    q->post(request, networkRequest, postData);
}

////// End of private class //////

TranspoleWaitingTimeHelper::TranspoleWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                                       QObject *parent):
    PluginHelper::AbstractWaitingTimeHelper(*(new TranspoleWaitingTimeHelperPrivate(this)), parent)
{
    Q_D(TranspoleWaitingTimeHelper);
    d->networkAccessManager = networkAccessManager;
}

void TranspoleWaitingTimeHelper::checkRan(const Company &companyToCheck, const Line &lineToCheck,
                                          const Journey &journeyToCheck,
                                          const Station &stationToCheck)
{
    Q_D(TranspoleWaitingTimeHelper);
    if (companyToCheck != company() || lineToCheck != line() || journeyToCheck != journey()
        || stationToCheck != station()) {
        d->ran.clear();
    }
}

void TranspoleWaitingTimeHelper::load(const QString &request)
{
    Q_D(TranspoleWaitingTimeHelper);
    if (d->ran.isEmpty()) {
        QString fullId = station().properties().value("id").toString();
        QStringList idAndLigneSens = fullId.split("_");
        QString id = idAndLigneSens.at(0);
        QString ligne = idAndLigneSens.at(1);
        QString sens = idAndLigneSens.at(2);

        QString urlString = "http://www.transpole.mobi/index.php?id=690";

        QByteArray postData = "a=recherche_lignes&refs=";
        postData.append(QUrl::toPercentEncoding(id));
        postData.append("&sens=");
        postData.append(QUrl::toPercentEncoding(sens));
        postData.append("&ligne=");
        postData.append(QUrl::toPercentEncoding(ligne));
        postData.append("&list_refs=");
        postData.append(QUrl::toPercentEncoding(fullId));


        QNetworkRequest networkRequest;
        networkRequest.setUrl(QUrl(urlString));

        post(request, networkRequest, postData);
    } else {
        d->performSecondPhase(request);
    }
}

QList<JourneyAndWaitingTime> TranspoleWaitingTimeHelper::processData(QIODevice *input, bool *ok,
                                                                     QString *errorMessage)
{
    Q_D(TranspoleWaitingTimeHelper);
    debug("transpole-plugin") << "Phase 2 using ran" << d->ran;

    QList<JourneyAndWaitingTime> journeysAndWaitingTimes;
    QRegExp timeRegExp ("<li data-theme=\".\" data-icon=\"false\">([^<]*)</li>");
    QRegExp timeFormaRegExp ("(\\d\\d).+(\\d\\d)");
    QTime currentTime = QTime::currentTime();

    while (!input->atEnd()) {
        QString data = input->readLine();
        if (data.indexOf(timeRegExp) != -1) {
            WaitingTime waitingTime;
            QVariantMap properties;
            properties.insert("destination", journey().name());
            QString time = timeRegExp.cap(1);
            if (time.contains("cours")) {
                waitingTime.setWaitingTime(0);
                properties.insert("type", "realtime");
            } else if (time.contains("mn")) {
                int min = time.remove("mn").trimmed().toInt();
                waitingTime.setWaitingTime(min);
                properties.insert("type", "realtime");
            } else if (time.indexOf(timeFormaRegExp) != -1) {
                int timeHours = timeFormaRegExp.cap(1).toInt();
                int timeMinutes = timeFormaRegExp.cap(1).toInt();
                QTime nextTime = QTime(timeHours, timeMinutes);
                int minutes = ((currentTime.secsTo(nextTime) / 60) + 1440) % 1440;
                waitingTime.setWaitingTime(minutes);
                properties.insert("type", "timetable");
            } else {
                warning("transpole-plugin") << time;
                waitingTime.setWaitingTime(-1);
            }
            waitingTime.setProperties(properties);
            journeysAndWaitingTimes.append(JourneyAndWaitingTime(journey(), waitingTime));
        }
    }

    if (ok) {
        *ok = true;
    }

    if (errorMessage) {
        *errorMessage = QString();
    }

    return journeysAndWaitingTimes;
}


}

}

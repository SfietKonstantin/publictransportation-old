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

#include "ratp.h"

#include <QtCore/QFile>
#include <QtCore/QtPlugin>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtXml/QDomDocument>

#include "debug.h"
#include "common/errorid.h"
#include "common/capabilitiesconstants.h"
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/infojourneys.h"
#include "common/journeyandwaitingtime.h"

#include "languagehelper.h"
#include "offlinesuggestedstationshelper.h"
#include "offlinexmljourneysfromstationhelper.h"
#include "abstractwaitingtimehelper.h"

using namespace PublicTransportation::PluginHelper;

namespace PublicTransportation
{

namespace Provider
{

class RatpWaitingTimeHelper: public AbstractWaitingTimeHelper
{
public:
    explicit RatpWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                   QObject *parent = 0);
protected:
    virtual QList<JourneyAndWaitingTime> processData(QIODevice *input, bool *ok,
                                                     QString *errorMessage);
};

class RatpPrivate
{
public:
    RatpPrivate(Ratp *q);
    QStringList stations;
    QNetworkAccessManager *nam;
    RatpWaitingTimeHelper *timeDownloaderHelper;
private:
    Ratp * const q_ptr;
    Q_DECLARE_PUBLIC(Ratp)
};

RatpWaitingTimeHelper::RatpWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                             QObject *parent):
    AbstractWaitingTimeHelper(networkAccessManager, parent)
{
}

QList<JourneyAndWaitingTime> RatpWaitingTimeHelper::processData(QIODevice *input, bool *ok,
                                                                QString *errorMessage)
{
    QList<JourneyAndWaitingTime> journeysAndWaitingTimeList;

    QTime currentTime = QTime::currentTime();
    QRegExp timeMetroRegExp ("&gt;&nbsp;([^<]*)</div><div[^>]*><b>([^<]*)");
    QRegExp timeRerRegExp ("&gt;&nbsp;([^<]*)</div><div[^>]*><a[^>]*>([^<]*)</a></div><div[^>]*>\
<b>([^<]*)");
    QRegExp timeRegExp("(\\d\\d):(\\d\\d)");
    while (!input->atEnd()) {
        QVariantMap journeyProperties = journey().properties();

        QString minutesString;
        QVariantMap properties;
        QString data = input->readLine();
        if (data.indexOf(timeMetroRegExp) != -1) {
            QString destination = timeMetroRegExp.cap(1);
            properties.insert("destination", LanguageHelper::unstripHtmlAccents(destination));
            minutesString = timeMetroRegExp.cap(2);
        } else if (data.indexOf(timeRerRegExp) != -1) {
            QString destination = timeRerRegExp.cap(1);
            destination = LanguageHelper::unstripHtmlAccents(destination);
            properties.insert("destination", destination);
            journeyProperties.insert("to", destination);
            journeyProperties.insert("destination", destination);
            properties.insert("train", LanguageHelper::unstripHtmlAccents(timeRerRegExp.cap(2)));
            minutesString = timeRerRegExp.cap(3);
            debug("test") << minutesString;
        }

        if (!minutesString.isEmpty()) {
            int minutes = -1;
            if (minutesString.contains("Train")) {
                minutes = 0;
            } else if (minutesString.contains("mn")) {
                minutes = minutesString.remove("mn").trimmed().toInt();
            } else if (minutesString.indexOf(timeRegExp) != -1) {
                QTime nextTime = QTime(timeRegExp.capturedTexts().at(1).toInt(),
                                       timeRegExp.capturedTexts().at(2).toInt());
                minutes = ((currentTime.secsTo(nextTime) / 60) + 1440) % 1440;
            }

            Journey newJourney = journey();
            newJourney.setProperties(journeyProperties);

            WaitingTime waitingTime;
            waitingTime.setProperties(properties);
            waitingTime.setWaitingTime(minutes);
            journeysAndWaitingTimeList.append(JourneyAndWaitingTime(newJourney, waitingTime));
        }
    }

    if (ok) {
        *ok = true;
    }

    if (errorMessage) {
        *errorMessage = QString();
    }

    return journeysAndWaitingTimeList;
}

RatpPrivate::RatpPrivate(Ratp *q):
    q_ptr(q)
{
//    waitingTimeReply = 0;

    QFile file (":/data/backward/stations.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        debug("ratp-plugin") << "Failed to read" << file.fileName().constData();
        return;
    }
    QTextStream fileStream (&file);
    while (!fileStream.atEnd()) {
        QString line = fileStream.readLine().trimmed();
        if (!line.isEmpty()) {
            stations.append(line);
        }
    }

    file.close();

}

////// End of private class //////

Ratp::Ratp(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new RatpPrivate(this))
{
    Q_D(Ratp);
    d->nam = new QNetworkAccessManager(this);
    d->timeDownloaderHelper = new RatpWaitingTimeHelper(d->nam, this);
    connect(d->timeDownloaderHelper, SIGNAL(errorRetrieved(QString,QString,QString)),
            this, SIGNAL(errorRetrieved(QString,QString,QString)));
    connect(d->timeDownloaderHelper,
           SIGNAL(waitingTimeRetrieved(QString,QList<PublicTransportation::JourneyAndWaitingTime>)),
            this,
          SIGNAL(waitingTimeRetrieved(QString,QList<PublicTransportation::JourneyAndWaitingTime>)));
}

QStringList Ratp::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    capabilities.append(JOURNEYS_FROM_STATION);
    capabilities.append(WAITING_TIME);
    return capabilities;
}

void Ratp::retrieveCopyright(const QString &request)
{
    QString copyright = tr("This provider uses wap.ratp.fr.") + "\n"
                        + QString::fromUtf8("RATP - Tous droits réservés");
    emit copyrightRetrieved(request, copyright);
}

void Ratp::retrieveSuggestedStations(const QString &request, const QString &partialStation)
{
    Q_D(Ratp);
    if (partialStation.size() < 2) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.ratp");

    QVariantMap properties;
    properties.insert("backendName", "RATP");


    QList<Station> suggestedStations
            = OfflineSuggestedStationsHelper::suggestedStations(partialStation, d->stations,
                                                                disambiguation, properties);

    emit suggestedStationsRetrieved(request, suggestedStations);
}

void Ratp::retrieveJourneysFromStation(const QString &request, const Station &station, int limit)
{
    Q_UNUSED(limit)
    QString fileName = QString(":/data/backward/%1.xml").arg(station.name().at(0).toLower());

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.ratp");

    Company company (disambiguation, "RATP", QVariantMap());

    bool ok;
    QString error;

    QList<InfoJourneys> infoJourneysList =
            OfflineXmlJourneysFromStationHelper::journeysFromStation(fileName, station,
                                                                     disambiguation, company,
                                                                     &ok, &error);

    if (!ok) {
        emit errorRetrieved(request, BACKEND_WARNING, error);
        return;
    }

    debug("ratp-plugin") << infoJourneysList.count();

    emit journeysFromStationRetrieved(request, infoJourneysList);
}

void Ratp::retrieveWaitingTime(const QString &request, const Company &company, const Line &line,
                               const Journey &journey, const Station &station)
{
    Q_D(Ratp);
    Q_UNUSED(company);
    QString urlString = "http://wap.ratp.fr/siv/schedule?service=next&reseau=%1&lineid=%2&\
directionsens=%3&stationid=%4";
    urlString = urlString.arg(line.properties().value("network").toString(),
                              line.properties().value("id").toString(),
                              journey.properties().value("id").toString(),
                              station.properties().value("id").toString());
    d->timeDownloaderHelper->get(request, urlString, company, line, journey, station);
}

}

}

#include "moc_ratp.cpp"

Q_EXPORT_PLUGIN2(ratp, PublicTransportation::Provider::Ratp)

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

#include "transpole.h"

#include <QtCore/QFile>
#include <QtCore/QtPlugin>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "debug.h"
#include "common/capabilitiesconstants.h"
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/infojourneys.h"
#include "common/waitingtime.h"

namespace PublicTransportation
{

namespace Provider
{

class TranspolePrivate
{
public:
    TranspolePrivate(Transpole *q);
    static QString unstripHtmlAccents(const QString &string);
    void perforWaitingTimePhase2();
    void slotSuggestedStationsFinished();
    void slotJourneysFromStationFinished();
    void slotWaitingTimeFinished();
    void slotWaitingTimePhase2Finished();
    QNetworkAccessManager *nam;
    QNetworkReply *suggestedStationsReply;
    QString suggestedStationsRequest;
    QNetworkReply *journeysFromStationReply;
    QString journeysFromStationRequest;
    Station journeysFromStationStation;
    QNetworkReply *waitingTimeReply;
    QString waitingTimeRequest;
    Station waitingTimeStation;
    QString waitingTimeRan;
    QNetworkReply *waitingTimePhase2Reply;
    QString waitingTimeDirection;


private:
    Transpole * const q_ptr;
    Q_DECLARE_PUBLIC(Transpole)
};

TranspolePrivate::TranspolePrivate(Transpole *q):
    q_ptr(q)
{
    suggestedStationsReply = 0;
    journeysFromStationReply = 0;
    waitingTimeReply = 0;
    waitingTimePhase2Reply = 0;
}

QString TranspolePrivate::unstripHtmlAccents(const QString &string)
{
    QString newString = string;
    newString.replace("&Agrave;", QString::fromUtf8("À"));
    newString.replace("&agrave;", QString::fromUtf8("à"));
    newString.replace("&Acirc;", QString::fromUtf8("Â"));
    newString.replace("&acirc;", QString::fromUtf8("â"));
    newString.replace("&Auml;", QString::fromUtf8("Ä"));
    newString.replace("&auml;", QString::fromUtf8("ä"));
    newString.replace("&Egrave;", QString::fromUtf8("È"));
    newString.replace("&egrave;", QString::fromUtf8("è"));
    newString.replace("&Eacute;", QString::fromUtf8("É"));
    newString.replace("&eacute;", QString::fromUtf8("é"));
    newString.replace("&Ecirc;", QString::fromUtf8("Ê"));
    newString.replace("&ecirc;", QString::fromUtf8("ê"));
    newString.replace("&Euml;", QString::fromUtf8("Ë"));
    newString.replace("&euml;", QString::fromUtf8("ë"));
    newString.replace("&Icirc;", QString::fromUtf8("Î"));
    newString.replace("&icirc;", QString::fromUtf8("î"));
    newString.replace("&Iuml;", QString::fromUtf8("Ï"));
    newString.replace("&iuml;", QString::fromUtf8("ï"));
    newString.replace("&Ocirc;", QString::fromUtf8("Ô"));
    newString.replace("&ocirc;", QString::fromUtf8("ô"));
    newString.replace("&Ouml;", QString::fromUtf8("Ö"));
    newString.replace("&ouml;", QString::fromUtf8("ö"));
    newString.replace("&Ugrave;", QString::fromUtf8("Ù"));
    newString.replace("&ugrave;", QString::fromUtf8("ù"));
    newString.replace("&Ucirc;", QString::fromUtf8("Û"));
    newString.replace("&ucirc;", QString::fromUtf8("û"));
    newString.replace("&Uuml;", QString::fromUtf8("Ü"));
    newString.replace("&uuml;", QString::fromUtf8("ü"));
    newString.replace("&Yuml;", QString::fromUtf8("Ÿ"));
    newString.replace("&yuml;", QString::fromUtf8("ÿ"));

    return newString;
}

void TranspolePrivate::perforWaitingTimePhase2()
{
    Q_Q(Transpole);

    if (waitingTimePhase2Reply) {
        if (!waitingTimePhase2Reply->isFinished()) {
            waitingTimePhase2Reply->abort();
        }
        waitingTimePhase2Reply->deleteLater();
    }

    QString fullId = waitingTimeStation.properties().value("id").toString();
    QStringList idAndLigneSens = fullId.split("_");
    QString id = idAndLigneSens.at(0);

    QString urlString = "http://www.transpole.mobi/index.php?id=690";

    QByteArray postData = "a=refresh&refs=";
    postData.append(QUrl::toPercentEncoding(id));
    postData.append("&ran=");
    postData.append(QUrl::toPercentEncoding(waitingTimeRan));

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(urlString));

    waitingTimePhase2Reply = nam->post(networkRequest, postData);

    q->connect(waitingTimePhase2Reply, SIGNAL(finished()),
               q, SLOT(slotWaitingTimePhase2Finished()));
}

void TranspolePrivate::slotSuggestedStationsFinished()
{
    Q_Q(Transpole);
    debug("transpole-plugin") << "Data retrieved from url"
                              << suggestedStationsReply->url().toString();
    QRegExp idRegExp ("<a href=\"#\" id=\"([^\"]*)\"");
    QRegExp lineNameRegExp ("<span class=\"lineName\">([^<]*)</span>");
    QRegExp foundRegExp ("pour l'arr[^t]*t ([^\\(]*)\\(([^\\)]*)");

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.transpole");

    QString currentId;
    QList<Station> suggestedStations;

    while (!suggestedStationsReply->atEnd()) {
        QString data = suggestedStationsReply->readLine();
        if (currentId.isEmpty()) {
            // We already found the correct station
            if (data.indexOf(foundRegExp) != -1) {
                Station station;
                station.setDisambiguation(disambiguation);
                station.setName(unstripHtmlAccents(foundRegExp.cap(1).trimmed()));
                QVariantMap properties;
                properties.insert("code", foundRegExp.cap(2));
                properties.insert("backendName", "Transpole");
                station.setProperties(properties);
                suggestedStations.append(station);
                break;
            }

            // Not found
            if (data.contains("Aucun")) {
                break;
            }

            if (data.indexOf(idRegExp) != -1) {
                currentId = idRegExp.cap(1);
            }
        } else {
            if (data.indexOf(lineNameRegExp) != -1) {
                Station station;
                station.setDisambiguation(disambiguation);
                station.setName(unstripHtmlAccents(lineNameRegExp.cap(1)));
                QVariantMap properties;
                properties.insert("code", currentId);
                properties.insert("providerName", "Transpole");
                station.setProperties(properties);
                suggestedStations.append(station);

                currentId = QString();
            }
        }
    }

    emit q->suggestedStationsRetrieved(suggestedStationsRequest, suggestedStations);
    suggestedStationsRequest = QString();
    suggestedStationsReply->deleteLater();
    suggestedStationsReply = 0;
}

void TranspolePrivate::slotJourneysFromStationFinished()
{
    Q_Q(Transpole);

    debug("transpole-plugin") << "Data retrieved from url"
                              << journeysFromStationReply->url().toString();

    QRegExp idRegExp ("<a href=\"#\" id=\"([^\"]*)\"");
    QRegExp lineRegExp ("<span class=\"linePicto\"><span style=\"display:none\">([^-]*)");
    QRegExp lineNameRegExp ("<span class=\"lineName\">([^<]*)</span>");

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.transpole");

    QString currentId;
    QString currentLine;

    QList<InfoJourneys> infoJourneysList;

    Company company;
    company.setDisambiguation(disambiguation);
    company.setName("Transpole");

    while (!journeysFromStationReply->atEnd()) {
        QString data = journeysFromStationReply->readLine();
        if (currentId.isEmpty()) {
            if (data.indexOf(idRegExp) != -1) {
                currentId = idRegExp.cap(1);
            }
        } else if (currentLine.isEmpty()) {
            if (data.indexOf(lineRegExp) != -1) {
                currentLine = lineRegExp.cap(1).trimmed();
            }
        } else {
            if (data.indexOf(lineNameRegExp) != -1) {
                bool existing = false;
                InfoJourneys infoJourneysToAdd;
                QPair<Journey, Station> journeyAndStation;

                foreach (InfoJourneys infoJourneys, infoJourneysList) {
                    if (infoJourneys.line().name() == currentLine) {
                        infoJourneysToAdd = infoJourneys;
                        existing = true;
                    }
                }

                Line line;
                line.setDisambiguation(disambiguation);
                line.setName(currentLine);

                if (!existing) {
                    infoJourneysToAdd.setCompany(company);
                    infoJourneysToAdd.setLine(line);
                }

                Journey journey;
                journey.setDisambiguation(disambiguation);
                journey.setName(unstripHtmlAccents(lineNameRegExp.cap(1)));
                journeyAndStation.first = journey;

                Station station;
                station.setDisambiguation(disambiguation);
                station.setName(journeysFromStationStation.name());
                QVariantMap properties;
                properties.insert("id", currentId);
                properties.insert("code", journeysFromStationStation.properties().value("code"));
                station.setProperties(properties);
                journeyAndStation.second = station;

                QList<QPair<Journey, Station> > journeysAndStations;

                if (existing) {
                    journeysAndStations = infoJourneysToAdd.journeysAndStations();
                }
                journeysAndStations.append(journeyAndStation);
                infoJourneysToAdd.setJourneysAndStations(journeysAndStations);

                if (!existing) {
                    infoJourneysList.append(infoJourneysToAdd);
                }

                currentId = QString();
                currentLine = QString();
            }
        }
    }

    emit q->journeysFromStationRetrieved(journeysFromStationRequest, infoJourneysList);
    journeysFromStationRequest = QString();
    journeysFromStationStation = Station();
    journeysFromStationReply->deleteLater();
    journeysFromStationReply = 0;
}

void TranspolePrivate::slotWaitingTimeFinished()
{
    debug("transpole-plugin") << "Data retrieved from url"
                              << waitingTimeReply->url().toString();

    QRegExp ranRegExp ("ran: (\\d*)");
    while (!waitingTimeReply->atEnd()) {
        QString data = waitingTimeReply->readLine();
        if (data.indexOf(ranRegExp) != -1) {
            waitingTimeRan = ranRegExp.cap(1);
            break;
        }
    }

    waitingTimeReply->deleteLater();
    waitingTimeReply = 0;

    perforWaitingTimePhase2();
}

void TranspolePrivate::slotWaitingTimePhase2Finished()
{
    Q_Q(Transpole);

    debug("transpole-plugin") << "Phase 2 using ran" << waitingTimeRan;
    debug("transpole-plugin") << "Data retrieved from url"
                              << waitingTimePhase2Reply->url().toString();

    QList<WaitingTime> waitingTimes;
    QRegExp timeRegExp ("<li data-theme=\".\" data-icon=\"false\">([^<]*)</li>");
    QRegExp timeFormaRegExp ("(\\d\\d).(\\d\\d)");
    QTime currentTime = QTime::currentTime();

    while (!waitingTimePhase2Reply->atEnd()) {
        QString data = waitingTimePhase2Reply->readLine();
        if (data.indexOf(timeRegExp) != -1) {
            WaitingTime waitingTime;
            QVariantMap properties;
            properties.insert("destination", waitingTimeDirection);
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
            waitingTimes.append(waitingTime);
        }
    }

    emit q->waitingTimeRetrieved(waitingTimeRequest, waitingTimes);
    waitingTimeRequest = QString();
    waitingTimePhase2Reply->deleteLater();
    waitingTimePhase2Reply = 0;
}

////// End of private class //////

Transpole::Transpole(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new TranspolePrivate(this))
{
    Q_D(Transpole);
    d->nam = new QNetworkAccessManager(this);
}

QStringList Transpole::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    capabilities.append(JOURNEYS_FROM_STATION);
    capabilities.append(WAITING_TIME);
    return capabilities;
}

void Transpole::retrieveCopyright(const QString &request)
{
    QString copyright = tr("Copyright to be registered");
    emit copyrightRetrieved(request, copyright);
}

void Transpole::retrieveSuggestedStations(const QString &request, const QString &partialStation)
{
    Q_D(Transpole);
    if (partialStation.size() < 2) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }

    if (d->suggestedStationsReply) {
        if (!d->suggestedStationsReply->isFinished()) {
            d->suggestedStationsReply->abort();
        }
        d->suggestedStationsReply->deleteLater();
    }

    QString urlString = "http://www.transpole.mobi/index.php?id=690";
    QByteArray postData = QByteArray("a=recherche_arret&arret=");
    postData.append(QUrl::toPercentEncoding(partialStation));

    d->suggestedStationsRequest = request;
    d->suggestedStationsReply = d->nam->post(QNetworkRequest(QUrl(urlString)), postData);
    connect(d->suggestedStationsReply, SIGNAL(finished()),
            this, SLOT(slotSuggestedStationsFinished()));
}

void Transpole::retrieveJourneysFromStation(const QString &request, const Station &station,
                                            int limit)
{
    Q_D(Transpole);
    Q_UNUSED(limit)
    if (d->journeysFromStationReply) {
        if (!d->journeysFromStationReply->isFinished()) {
            d->journeysFromStationReply->abort();
        }
        d->journeysFromStationReply->deleteLater();
    }

    QString urlString = "http://www.transpole.mobi/index.php?id=690";
    QByteArray postData = "a=recherche_codes&code=";
    QString code = station.properties().value("code").toString();
    postData.append(QUrl::toPercentEncoding(code));

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(urlString));

    d->journeysFromStationRequest = request;
    d->journeysFromStationStation = station;
    d->journeysFromStationReply = d->nam->post(networkRequest, postData);

    connect(d->journeysFromStationReply, SIGNAL(finished()),
            this, SLOT(slotJourneysFromStationFinished()));

}

void Transpole::retrieveWaitingTime(const QString &request, const Company &company,
                                    const Line &line, const Journey &journey,
                                    const Station &station)
{
    Q_D(Transpole);
    Q_UNUSED(company)
    Q_UNUSED(line)

    if (d->waitingTimeReply) {
        if (!d->waitingTimeReply->isFinished()) {
            d->waitingTimeReply->abort();
        }
        d->waitingTimeReply->deleteLater();
    }

    d->waitingTimeRequest = request;

    if (station.properties().value("id") == d->waitingTimeStation.properties().value("id")
        && !d->waitingTimeRan.isEmpty()) {
        d->perforWaitingTimePhase2();
        return;
    }

    d->waitingTimeRan = QString();

    QString fullId = station.properties().value("id").toString();
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

    d->waitingTimeStation = station;
    d->waitingTimeDirection = journey.name();
    d->waitingTimeReply = d->nam->post(networkRequest, postData);

    connect(d->waitingTimeReply, SIGNAL(finished()),
            this, SLOT(slotWaitingTimeFinished()));
}

}

}

#include "moc_transpole.cpp"

Q_EXPORT_PLUGIN2(transpole, PublicTransportation::Provider::Transpole)

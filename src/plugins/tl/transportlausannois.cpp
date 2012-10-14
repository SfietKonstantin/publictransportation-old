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

#include "transportlausannois.h"

#include <QtCore/QFile>
#include <QtCore/QtPlugin>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtXml/QDomDocument>
#include <parser.h>

#include "debug.h"
#include "common/errorid.h"
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

class TransportLausannoisPrivate
{
public:
    TransportLausannoisPrivate(TransportLausannois *q);
    void slotWaitingTimeFinished();
    QStringList stations;
    QNetworkAccessManager *nam;
    QMap<QNetworkReply *, QString> waitTimeRequestMap;
private:
    TransportLausannois * const q_ptr;
    Q_DECLARE_PUBLIC(TransportLausannois)
};

TransportLausannoisPrivate::TransportLausannoisPrivate(TransportLausannois *q):
    q_ptr(q)
{
    QFile file (":/data/backward/stations.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        debug("tl-plugin") << "Failed to read" << file.fileName().constData();
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

void TransportLausannoisPrivate::slotWaitingTimeFinished()
{
    Q_Q(TransportLausannois);
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(q->sender());
    QString waitTimeRequest = waitTimeRequestMap.value(reply);

    debug("tl-plugin") << "Data retrieved from url" << reply->url().toString();
    QJson::Parser parser;

    QList<WaitingTime> waitingTimes;
    QVariant parsedValue = parser.parse(reply);
    if (!parsedValue.isValid()) {
        q->errorRetrieved(waitTimeRequest, BACKEND_WARNING,
                          "Failed to get information from TL website");
        reply->deleteLater();
        return;
    }

    QVariantList waitTimeList = parsedValue.toList();
    QTime currentTime = QTime::currentTime();

    foreach (QVariant waitTimeEntry, waitTimeList) {
        QVariantMap waitTimeMap = waitTimeEntry.toMap();
        QString destination = waitTimeMap.value("destination").toString();

        QString time = waitTimeMap.value("time").toString();
        debug("tl-plugin") << time;

        QVariantMap properties;
        properties.insert("destination", destination);

        WaitingTime waitingTime;

        QRegExp timeRegExp("(\\d\\d):(\\d\\d)");
        QRegExp realtimeRegExp("(\\d+)");
        if (time.indexOf(timeRegExp) != -1) {
            QTime nextTime = QTime(timeRegExp.capturedTexts().at(1).toInt(),
                                   timeRegExp.capturedTexts().at(2).toInt());
            int minutes = ((currentTime.secsTo(nextTime) / 60) + 1440) % 1440;
            waitingTime.setWaitingTime(minutes);
            properties.insert("type", "timetable");
            waitingTime.setProperties(properties);
        } else if (time.indexOf(realtimeRegExp) != -1) {
            int minutes = realtimeRegExp.capturedTexts().at(1).toInt();
            waitingTime.setWaitingTime(minutes);
            properties.insert("type", "realtime");
            waitingTime.setProperties(properties);
        } else if (time.contains("now")) {
            waitingTime.setWaitingTime(0);
            properties.insert("type", "realtime");
            waitingTime.setProperties(properties);
        }
        waitingTimes.append(waitingTime);
    }

    emit q->waitingTimeRetrieved(waitTimeRequest, waitingTimes);
    reply->deleteLater();
}

////// End of private class //////

TransportLausannois::TransportLausannois(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new TransportLausannoisPrivate(this))
{
    Q_D(TransportLausannois);
    d->nam = new QNetworkAccessManager(this);
}

QStringList TransportLausannois::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    capabilities.append(JOURNEYS_FROM_STATION);
    capabilities.append(WAITING_TIME);
    return capabilities;
}

void TransportLausannois::retrieveCopyright(const QString &request)
{
    QString copyright = tr("(c) Copyright tl, 2001-2012, tous droits réservés.");
    emit copyrightRetrieved(request, copyright);
}

void TransportLausannois::retrieveSuggestedStations(const QString &request,
                                                    const QString &partialStation)
{
    Q_D(TransportLausannois);
    if (partialStation.size() < 2) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }

    QList<Station> suggestedStations;
    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.tl");

    QVariantMap properties;
    properties.insert("providerName", "Transports Lausannois");


    foreach (QString stationName, d->stations) {
        if (stationName.toLower().startsWith(partialStation.toLower())) {
            Station station (disambiguation, stationName, properties);
            suggestedStations.append(station);
        }
    }
    foreach (QString stationName, d->stations) {
        if (stationName.toLower().contains(partialStation.toLower())) {
            bool added = false;
            foreach (Station station, suggestedStations) {
                if (station.name() == stationName) {
                    added = true;
                }
            }

            if (!added) {
                Station station (disambiguation, stationName, properties);
                suggestedStations.append(station);
            }
        }
    }

    emit suggestedStationsRetrieved(request, suggestedStations);
}

void TransportLausannois::retrieveJourneysFromStation(const QString &request,
                                                      const Station &station, int limit)
{
    Q_UNUSED(limit)
    QString fileName = QString(":/data/backward/%1.xml").arg(station.name().at(0).toLower());

    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        debug("tl-plugin") << "Failed to read" << fileName.toAscii().constData();
        emit errorRetrieved(request, BACKEND_WARNING, QString("Failed to read %1").arg(fileName));
        return;
    }

    QDomDocument document;
    document.setContent(&file);

    file.close();

    QDomElement foundElement;
    QDomElement currentElement = document.documentElement().firstChildElement();

    while (!currentElement.isNull() && foundElement.isNull()) {
        if (currentElement.attribute("name") == station.name()) {
            foundElement = currentElement;
        }
        currentElement = currentElement.nextSiblingElement();
    }

    if (foundElement.isNull()) {
        debug("tl-plugin") << "Failed to find station" << station.name().toAscii().constData();
        emit errorRetrieved(request, BACKEND_WARNING,
                            QString("Failed to find station %1").arg(station.name()));
        return;
    }

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.tl");
    Company company;
    company.setDisambiguation(disambiguation);
    company.setName("Transports Lausannois");

    QList<InfoJourneys> infoJourneysList;
    currentElement = foundElement.firstChildElement();
    while (!currentElement.isNull()) {
        InfoJourneys infoJourneys;
        Line line;
        line.setName(currentElement.attribute("name"));
        QVariantMap properties;
        properties.insert("id", currentElement.attribute("id"));
        properties.insert("description", currentElement.attribute("description"));
        line.setDisambiguation(disambiguation);
        line.setProperties(properties);
        infoJourneys.setCompany(company);
        infoJourneys.setLine(line);

        QList<QPair <Journey, Station> > journeysStations;
        QDomElement journeyElement = currentElement.firstChildElement();
        while (!journeyElement.isNull()) {
            Journey journey;
            Station preciseStation;
            journey.setName(journeyElement.attribute("name"));
            preciseStation.setName(station.name());
            QVariantMap journeyProperties;
            QVariantMap stationProperties;
            journeyProperties.insert("id", journeyElement.attribute("id"));
            journeyProperties.insert("from", journeyElement.attribute("from"));
            journeyProperties.insert("to", journeyElement.attribute("to"));
            journeyProperties.insert("internalDescription",
                              journeyElement.attribute("internalDescription"));
            if (journeyElement.hasAttribute("via")) {
                journeyProperties.insert("via", journeyElement.attribute("via"));
            }
            stationProperties.insert("id", journeyElement.attribute("stationId"));
            stationProperties.insert("city", journeyElement.attribute("stationCity"));
            journey.setDisambiguation(disambiguation);
            journey.setProperties(journeyProperties);
            preciseStation.setDisambiguation(disambiguation);
            preciseStation.setProperties(stationProperties);
            journeysStations.append(QPair<Journey, Station>(journey, preciseStation));

            journeyElement = journeyElement.nextSiblingElement();
        }

        infoJourneys.setJourneysAndStations(journeysStations);
        infoJourneysList.append(infoJourneys);

        currentElement = currentElement.nextSiblingElement();
    }

    debug("tl-plugin") << infoJourneysList.count();

    emit journeysFromStationRetrieved(request, infoJourneysList);
}

void TransportLausannois::retrieveWaitingTime(const QString &request, const Company &company,
                                              const Line &line, const Journey &journey,
                                              const Station &station)
{
    Q_D(TransportLausannois);
    Q_UNUSED(company);
    Q_UNUSED(journey);
    QString urlString = "http://m.t-l.ch/ressources/horaire.php?level=4&id=%1&line=%2";
    urlString = urlString.arg(station.properties().value("id").toString(),
                              line.properties().value("id").toString());

    QNetworkReply *reply = d->nam->get(QNetworkRequest(QUrl(urlString)));
    d->waitTimeRequestMap.insert(reply, request);
    connect(reply, SIGNAL(finished()), this, SLOT(slotWaitingTimeFinished()));
}

}

}

#include "moc_transportlausannois.cpp"

Q_EXPORT_PLUGIN2(tl, PublicTransportation::Provider::TransportLausannois)

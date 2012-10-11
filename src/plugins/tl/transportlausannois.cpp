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
//#include <parser.h>

#include "debug.h"
#include "common/capabilitiesconstants.h"
#include "common/company.h"

namespace PublicTransportation
{

namespace Provider
{

class TransportLausannoisPrivate
{
public:
    TransportLausannoisPrivate(TransportLausannois *q);
    void slotFinished();
    QStringList stations;
    QNetworkAccessManager *nam;
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

void TransportLausannoisPrivate::slotFinished()
{
//    Q_Q(TransportLausannois);
//    QNetworkReply *reply = qobject_cast<QNetworkReply *>(q->sender());

//    debug("tl-plugin") << "Data retrieved from url" << reply->url().toString();
//    QJson::Parser parser;

//    QList<WaitingTime> waitingTimes;
//    QVariantList waitTimeList = parser.parse(reply).toList();
//    foreach (QVariant waitTimeEntry, waitTimeList) {
//        QVariantMap waitTimeMap = waitTimeEntry.toMap();
//        QString stop = waitTimeMap.value("stop").toString();
//        QString destination = waitTimeMap.value("destination").toString();

//        QString time = waitTimeMap.value("time").toString();

//        QVariantMap properties;
//        properties.insert("name", QString("%1 > %2").arg(stop, destination));

//        WaitingTime waitingTime;

//        QRegExp timeRegExp("(\\d\\d):(\\d\\d)");
//        QRegExp realtimeRegExp("(\\d+)");
//        QTime currentTime = QTime::currentTime();
//        if (time.indexOf(timeRegExp) != -1) {
//            QTime nextTime = QTime(timeRegExp.capturedTexts().at(1).toInt(),
//                                   timeRegExp.capturedTexts().at(2).toInt());
//            int minutes = currentTime.secsTo(nextTime) / 60;
//            waitingTime.setWaitingTime(minutes);
//            properties.insert("type", "timetable");
//            waitingTime.setProperties(properties);
//        } else if (time.indexOf(realtimeRegExp) != -1) {
//            int minutes = realtimeRegExp.capturedTexts().at(1).toInt();
//            waitingTime.setWaitingTime(minutes);
//            properties.insert("type", "realtime");
//            waitingTime.setProperties(properties);
//        } else if (time.contains("now")) {
//            waitingTime.setWaitingTime(0);
//            properties.insert("type", "realtime");
//            waitingTime.setProperties(properties);
//        }
//        waitingTimes.append(waitingTime);
//    }

//    q->waitingTimeRetrieved(companyForWaitTime, lineForWaitTime,
//                            journeyForWaitTime, stationForWaitTime, waitingTimes);

//    companyForWaitTime = Company();
//    lineForWaitTime = Line();
//    journeyForWaitTime = Journey();
//    stationForWaitTime = Station();
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
    return capabilities;
}

void TransportLausannois::retrieveSuggestedStations(const QString &request,
                                                    const QString &partialStation)
{
    Q_D(TransportLausannois);
    if (partialStation.size() < 3) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }

    QList<Station> suggestedStations;
    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.tl");

    QVariantMap properties;
    properties.insert("providerName", "Transports Lausannois");


    foreach (QString stationName, d->stations) {
        if (stationName.toLower().contains(partialStation.toLower())) {
            Station station (disambiguation, stationName, properties);
            suggestedStations.append(station);
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
        emit errorRetrieved(request, QString("Failed to read %1").arg(fileName));
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
        emit errorRetrieved(request, QString("Failed to find station %1").arg(station.name()));
    }

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.tl");

    QList<LineJourneys> lineJourneysList;
    currentElement = foundElement.firstChildElement();
    while (!currentElement.isNull()) {
        LineJourneys lineJourney;
        Line line;
        line.setName(currentElement.attribute("name"));
        QVariantMap properties;
        properties.insert("id", currentElement.attribute("id"));
        properties.insert("description", currentElement.attribute("description"));
        line.setDisambiguation(disambiguation);
        line.setProperties(properties);
        lineJourney.setLine(line);

        QList<Journey> journeys;
        QDomElement journeyElement = currentElement.firstChildElement();
        while (!journeyElement.isNull()) {
            Journey journey;
            journey.setName(journeyElement.attribute("name"));
            QVariantMap properties;
            properties.insert("id", journeyElement.attribute("id"));
            properties.insert("from", journeyElement.attribute("from"));
            properties.insert("to", journeyElement.attribute("to"));
            properties.insert("internalDescription", journeyElement.attribute("internalDescription"));
            journey.setProperties(properties);
            journeys.append(journey);

            journeyElement = journeyElement.nextSiblingElement();
        }

        lineJourney.setJourneys(journeys);
        lineJourneysList.append(lineJourney);

        currentElement = currentElement.nextSiblingElement();

    }

    emit journeysFromStationRetrieved(request, lineJourneysList);
}

}

}

#include "moc_transportlausannois.cpp"

Q_EXPORT_PLUGIN2(tl, PublicTransportation::Provider::TransportLausannois)

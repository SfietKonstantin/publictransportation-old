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
#include "common/journeyandwaitingtime.h"

#include "offlinesuggestedstationshelper.h"
#include "offlinexmljourneysfromstationhelper.h"
#include "abstractwaitingtimehelper.h"

using namespace PublicTransportation::PluginHelper;

namespace PublicTransportation
{

namespace Provider
{

class TransportLausannoisTimeHelper: public AbstractWaitingTimeHelper
{
public:
    explicit TransportLausannoisTimeHelper(QNetworkAccessManager *networkAccessManager,
                                           QObject *parent = 0);
protected:
    virtual QList<JourneyAndWaitingTime> processData(QIODevice *input, bool *ok,
                                                     QString *errorMessage);
};

class TransportLausannoisPrivate
{
public:
    TransportLausannoisPrivate(TransportLausannois *q);
    void slotWaitingTimeFinished();
    QStringList stations;
    QNetworkAccessManager *nam;
    TransportLausannoisTimeHelper *waitingTimeHelper;
private:
    TransportLausannois * const q_ptr;
    Q_DECLARE_PUBLIC(TransportLausannois)
};

TransportLausannoisTimeHelper
    ::TransportLausannoisTimeHelper(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractWaitingTimeHelper(networkAccessManager, parent)
{
}

QList<JourneyAndWaitingTime> TransportLausannoisTimeHelper::processData(QIODevice *input,
                                                                        bool *ok,
                                                                        QString *errorMessage)
{
    QJson::Parser parser;

    QList<JourneyAndWaitingTime> journeysAndWaitingTimes;
    QVariant parsedValue = parser.parse(input);
    if (!parsedValue.isValid()) {
        if (ok) {
            *ok = false;
        }
        if (errorMessage) {
            *errorMessage = "Failed to get information from TL website";
        }
        return journeysAndWaitingTimes;
    }

    QVariantList waitTimeList = parsedValue.toList();
    QTime currentTime = QTime::currentTime();

    foreach (QVariant waitTimeEntry, waitTimeList) {
        QVariantMap waitTimeMap = waitTimeEntry.toMap();
        QString destination = waitTimeMap.value("destination").toString();

        QString time = waitTimeMap.value("time").toString();
        debug("tl-plugin") << time;

        Journey newJourney = journey();
        QVariantMap journeyProperties = newJourney.properties();
        journeyProperties.insert("to", destination);
        journeyProperties.insert("destination", destination);
        newJourney.setProperties(journeyProperties);

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
        journeysAndWaitingTimes.append(JourneyAndWaitingTime(newJourney, waitingTime));
    }

    if (ok) {
        *ok = true;
    }

    if (errorMessage) {
        *errorMessage = QString();
    }

    return journeysAndWaitingTimes;
}

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

////// End of private class //////

TransportLausannois::TransportLausannois(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new TransportLausannoisPrivate(this))
{
    Q_D(TransportLausannois);
    d->nam = new QNetworkAccessManager(this);
    d->waitingTimeHelper = new TransportLausannoisTimeHelper(d->nam, this);
    connect(d->waitingTimeHelper, SIGNAL(errorRetrieved(QString,QString,QString)),
            this, SIGNAL(errorRetrieved(QString,QString,QString)));
    connect(d->waitingTimeHelper,
           SIGNAL(waitingTimeRetrieved(QString,QList<PublicTransportation::JourneyAndWaitingTime>)),
            this,
          SIGNAL(waitingTimeRetrieved(QString,QList<PublicTransportation::JourneyAndWaitingTime>)));
}

QStringList TransportLausannois::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    capabilities.append(JOURNEYS_FROM_STATION);
    capabilities.append(WAITING_TIME);
    capabilities.append(STATIONS_FROM_JOURNEY);
    return capabilities;
}

void TransportLausannois::retrieveCopyright(const QString &request)
{
    QString copyright = tr("This provider uses tl live website.") + "\n"
                        + QString::fromUtf8("(c) Copyright tl, 2001-2012, tous droits réservés.");
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

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.tl");

    QVariantMap properties;
    properties.insert("backendName", "Transports Lausannois");

    QList<Station> suggestedStations
            = OfflineSuggestedStationsHelper::suggestedStations(partialStation, d->stations,
                                                                disambiguation, properties);

    emit suggestedStationsRetrieved(request, suggestedStations);
}

void TransportLausannois::retrieveJourneysFromStation(const QString &request,
                                                      const Station &station, int limit)
{
    Q_UNUSED(limit)
    QString fileName = QString(":/data/backward/%1.xml").arg(station.name().at(0).toLower());


    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.tl");

    Company company (disambiguation, "Transports Lausannois", QVariantMap());

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

    debug("tl-plugin") << infoJourneysList.count();

    emit journeysFromStationRetrieved(request, infoJourneysList);
}

void TransportLausannois::retrieveWaitingTime(const QString &request, const Company &company,
                                              const Line &line, const Journey &journey,
                                              const Station &station)
{
    Q_D(TransportLausannois);
    Q_UNUSED(company);

    QString urlString = "http://m.t-l.ch/ressources/horaire.php?level=4&id=%1&line=%2";
    urlString = urlString.arg(station.properties().value("id").toString(),
                              line.properties().value("id").toString());

    d->waitingTimeHelper->get(request, urlString, company, line, journey, station);
}

void TransportLausannois::retrieveStationsFromJourney(const QString &request,
                                                      const Company &company,
                                                      const Line &line, const Journey &journey,
                                                      const Station &station)
{
    Q_UNUSED(company)
    Q_UNUSED(line)

    QString journeyId = journey.properties().value("id").toString();
    QString fileName = QString(":/data/forward/%1.txt").arg(journeyId);

    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        debug("tl-plugin") << "Failed to read" << fileName.toAscii().constData();
        emit errorRetrieved(request, BACKEND_WARNING, QString("Failed to read %1").arg(fileName));
        return;
    }

    QList<Station> stationList;
    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.tl");

    QTextStream stream (&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QString stationName = line.split("::").at(2);

        QVariantMap properties;
        if (stationName == station.name()) {
            properties.insert("current", true);
        }

        Station journeyStation (disambiguation, stationName, properties);
        stationList.append(journeyStation);
    }

    Station firstStation = stationList.first();
    QVariantMap properties = firstStation.properties();
    properties.insert("terminus", true);
    firstStation.setProperties(properties);

    Station lastStation = stationList.last();
    properties = lastStation.properties();
    properties.insert("terminus", true);
    lastStation.setProperties(properties);

    emit stationsFromJourneyRetrieved(request, stationList);
}

}

}

#include "moc_transportlausannois.cpp"

Q_EXPORT_PLUGIN2(tl, PublicTransportation::Provider::TransportLausannois)

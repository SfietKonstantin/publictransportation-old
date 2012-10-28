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
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

#include "debug.h"
#include "common/errorid.h"
#include "common/capabilitiesconstants.h"
#include "common/infojourneys.h"

#include "offlinesuggestedstationshelper.h"
#include "offlinexmljourneysfromstationhelper.h"
#include "transportlausannoiswaitingtimehelper.h"

using namespace PublicTransportation::PluginHelper;

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
    TransportLausannoisWaitingTimeHelper *waitingTimeHelper;
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

////// End of private class //////

TransportLausannois::TransportLausannois(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new TransportLausannoisPrivate(this))
{
    Q_D(TransportLausannois);
    d->nam = new QNetworkAccessManager(this);
    d->waitingTimeHelper = new TransportLausannoisWaitingTimeHelper(d->nam, this);
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

    d->waitingTimeHelper->setData(company, line, journey, station);
    d->waitingTimeHelper->get(request, QNetworkRequest(urlString));
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

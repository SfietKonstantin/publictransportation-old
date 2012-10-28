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
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

#include "debug.h"
#include "common/errorid.h"
#include "common/capabilitiesconstants.h"
#include "common/infojourneys.h"

#include "ratpwaitingtimehelper.h"
#include "offlinesuggestedstationshelper.h"
#include "offlinexmljourneysfromstationhelper.h"

using namespace PublicTransportation::PluginHelper;

namespace PublicTransportation
{

namespace Provider
{

class RatpPrivate
{
public:
    RatpPrivate(Ratp *q);
    QStringList stations;
    QNetworkAccessManager *nam;
    RatpWaitingTimeHelper *waitingTimeHelper;
private:
    Ratp * const q_ptr;
    Q_DECLARE_PUBLIC(Ratp)
};

RatpPrivate::RatpPrivate(Ratp *q):
    q_ptr(q)
{
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
    d->waitingTimeHelper = new RatpWaitingTimeHelper(d->nam, this);
    connect(d->waitingTimeHelper, SIGNAL(errorRetrieved(QString,QString,QString)),
            this, SIGNAL(errorRetrieved(QString,QString,QString)));
    connect(d->waitingTimeHelper,
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
    d->waitingTimeHelper->setData(company, line, journey, station);
    d->waitingTimeHelper->get(request, QNetworkRequest(urlString));
}

}

}

#include "moc_ratp.cpp"

Q_EXPORT_PLUGIN2(ratp, PublicTransportation::Provider::Ratp)

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

#include "sibra.h"

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

static const char *USER_AGENT = "Mozilla/5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) \
AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16";

namespace PublicTransportation
{

namespace Provider
{

class SibraPrivate
{
public:
    SibraPrivate(Sibra *q);
    void slotSuggestedStationsFinished();
    void slotJourneysFromStationFinished();
    void emitSuggestedStationsRetrieved(const QString &request, const QString &partialStation);
    QNetworkAccessManager *nam;
    QNetworkReply *suggestedStationsReply;
    QNetworkReply *journeysFromStationReply;
    QString suggestedStationsRequest;
    QString suggestedStationsPartialStation;
    QString journeysFromStationRequest;
    Station journeysFromStationStation;
    QList<Station> stations;

private:
    Sibra * const q_ptr;
    Q_DECLARE_PUBLIC(Sibra)
};

SibraPrivate::SibraPrivate(Sibra *q):
    q_ptr(q)
{
    suggestedStationsReply = 0;
    journeysFromStationReply = 0;
}

void SibraPrivate::slotSuggestedStationsFinished()
{
    debug("sibra-plugin") << "Data retrieved from url" << suggestedStationsReply->url().toString();

    QRegExp stationRegExp
            = QRegExp("<li><a class=\"lien_arret[^\"]*\" href=\"([^\"]*)\"><span>([^<]*)<");

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.sibra");
    while (!suggestedStationsReply->atEnd()) {
        QString data = suggestedStationsReply->readLine();
        if (data.indexOf(stationRegExp) != -1) {
            Station station;
            QString name = stationRegExp.cap(2).toLower();
            name[0] = name[0].toUpper();

            QVariantMap properties;
            properties.insert("subUrl", stationRegExp.cap(1));
            properties.insert("providerName", "SIBRA");

            station.setDisambiguation(disambiguation);
            station.setName(name);
            station.setProperties(properties);

            stations.append(station);
        }
    }

    emitSuggestedStationsRetrieved(suggestedStationsRequest, suggestedStationsPartialStation);
    suggestedStationsRequest = QString();
    suggestedStationsPartialStation = QString();
    suggestedStationsReply->deleteLater();
    suggestedStationsReply = 0;
}

void SibraPrivate::slotJourneysFromStationFinished()
{
    Q_Q(Sibra);
    debug("sibra-plugin") << "Data retrieved from url"
                          << journeysFromStationReply->url().toString();

    QRegExp journeysRegExp = QRegExp("<span class=\"picto-arret-ligne picto-arret-l[^\"]\"><span>\
([^<]*)</span></span><span class=\"horaire\">Prochain bus à <strong>([^<]*)[^D]*Direction <strong>\
([^<]*)");

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.sibra");

    QTime currentTime = QTime::currentTime();
    QList<InfoJourneys> infoJourneysList;

    while (!journeysFromStationReply->atEnd()) {
        QString data = journeysFromStationReply->readLine();
        if (data.indexOf(journeysRegExp) != -1) {

            InfoJourneys infoJourneys;

            Company company;
            company.setDisambiguation(disambiguation);
            company.setName("SIBRA");
            infoJourneys.setCompany(company);


            Line line;
            line.setDisambiguation(disambiguation);
            line.setName(journeysRegExp.cap(1));
            infoJourneys.setLine(line);

            QList <QPair<Journey, Station> > journeysAndStations;
            QPair<Journey, Station> journeyAndStation;

            QTime nextTime = QTime::fromString(journeysRegExp.cap(2), "hh:mm");
            int minutes = ((currentTime.secsTo(nextTime) / 60) + 1440) % 1440;
            debug("sibra-plugin") << journeysRegExp.capturedTexts();

            Journey journey;
            journey.setDisambiguation(disambiguation);
            journey.setName(journeysRegExp.cap(3));
            journeyAndStation.first = journey;

            Station station;
            station.setName(journeysFromStationStation.name());
            station.setDisambiguation(disambiguation);
            QVariantMap properties;
            properties.insert("waitingTime", minutes);
            station.setProperties(properties);
            journeyAndStation.second = station;

            journeysAndStations.append(journeyAndStation);
            infoJourneys.setJourneysAndStations(journeysAndStations);
            infoJourneysList.append(infoJourneys);
        }
    }

    emit q->journeysFromStationRetrieved(journeysFromStationRequest, infoJourneysList);
    journeysFromStationRequest = QString();
    journeysFromStationStation = Station();
    journeysFromStationReply->deleteLater();
    journeysFromStationReply = 0;
}

void SibraPrivate::emitSuggestedStationsRetrieved(const QString &request,
                                                  const QString &partialStation)
{
    Q_Q(Sibra);
    QList<Station> suggestedStations;
    foreach (Station station, stations) {
        if (station.name().toLower().startsWith(partialStation.toLower())) {
            suggestedStations.append(station);
        }
    }
    foreach (Station station, stations) {
        if (station.name().toLower().contains(partialStation.toLower())
            && !suggestedStations.contains(station)) {
            suggestedStations.append(station);
        }
    }
    emit q->suggestedStationsRetrieved(request, suggestedStations);
}

////// End of private class //////

Sibra::Sibra(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new SibraPrivate(this))
{
    Q_D(Sibra);
    d->nam = new QNetworkAccessManager(this);
}

QStringList Sibra::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    capabilities.append(JOURNEYS_FROM_STATION);
    capabilities.append(WAITING_TIME);
    return capabilities;
}

void Sibra::retrieveCopyright(const QString &request)
{
    QString copyright = "Le site www.sibra.fr est la propriété de la Communauté de l'agglomération \
d'Annecy et de la Société Intercommunale des Bus de la Région Annécienne (SIBRA).";
    emit copyrightRetrieved(request, copyright);
}

void Sibra::retrieveSuggestedStations(const QString &request, const QString &partialStation)
{
    Q_D(Sibra);
    if (partialStation.size() < 2) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }

    if (d->stations.isEmpty()) {
        QString urlString = "http://m.sibra.fr/temps-reel-mobile";

        if (d->suggestedStationsReply) {
            if (!d->suggestedStationsReply->isFinished()) {
                d->suggestedStationsReply->abort();
            }
            d->suggestedStationsReply->deleteLater();
        }

        QNetworkRequest networkRequest;
        networkRequest.setUrl(QUrl(urlString));
        networkRequest.setRawHeader("User-Agent", USER_AGENT);

        d->suggestedStationsRequest = request;
        d->suggestedStationsPartialStation = partialStation;
        d->suggestedStationsReply = d->nam->get(networkRequest);
        connect(d->suggestedStationsReply, SIGNAL(finished()),
                this, SLOT(slotSuggestedStationsFinished()));
    } else {
        d->emitSuggestedStationsRetrieved(request, partialStation);
    }
}

void Sibra::retrieveJourneysFromStation(const QString &request, const Station &station, int limit)
{
    Q_D(Sibra);
    Q_UNUSED(limit)
    if (d->journeysFromStationReply) {
        if (!d->journeysFromStationReply->isFinished()) {
            d->journeysFromStationReply->abort();
        }
        d->journeysFromStationReply->deleteLater();
    }

    QString urlString = "http://m.sibra.fr/%1";
    urlString = urlString.arg(station.properties().value("subUrl").toString());

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(urlString));
    networkRequest.setRawHeader("User-Agent", USER_AGENT);

    d->journeysFromStationRequest = request;
    d->journeysFromStationStation = station;
    d->journeysFromStationReply = d->nam->get(networkRequest);
    connect(d->journeysFromStationReply, SIGNAL(finished()),
            this, SLOT(slotJourneysFromStationFinished()));

}

void Sibra::retrieveWaitingTime(const QString &request, const Company &company,
                                const Line &line, const Journey &journey, const Station &station)
{
    Q_UNUSED(company);
    Q_UNUSED(line);
    Q_UNUSED(journey);

    WaitingTime waitingTime;
    QVariantMap properties;
    properties.insert("destination", journey.name());
    waitingTime.setWaitingTime(station.properties().value("waitingTime").toInt());
    waitingTime.setProperties(properties);

    QList<WaitingTime> waitingTimeList;
    waitingTimeList.append(waitingTime);
    emit waitingTimeRetrieved(request, waitingTimeList);
}

}

}

#include "moc_sibra.cpp"

Q_EXPORT_PLUGIN2(sibra, PublicTransportation::Provider::Sibra)

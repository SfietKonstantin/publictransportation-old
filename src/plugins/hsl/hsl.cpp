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

#include "hsl.h"

#include <QtCore/QFile>
#include <QtCore/QtPlugin>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QtDBus/QDBusVariant>
#include <QtXml/QDomDocument>

#include "debug.h"
#include "common/capabilitiesconstants.h"
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/infojourneys.h"
#include "common/waitingtime.h"

static const char *USER = "sfietkonstantin";
static const char *PASSWORD = "publictransportation";

namespace PublicTransportation
{

namespace Provider
{

class HslPrivate
{
public:
    HslPrivate(Hsl *q);
    void slotSuggestedStationsFinished();
    void slotJourneysFromStationFinished();
    QNetworkAccessManager *nam;
    QNetworkReply *suggestedStationsReply;
    QString suggestedStationsRequest;
    QNetworkReply *journeysFromStationReply;
    QString journeysFromStationRequest;
    Station journeysFromStationStation;


private:
    Hsl * const q_ptr;
    Q_DECLARE_PUBLIC(Hsl)
};

HslPrivate::HslPrivate(Hsl *q):
    q_ptr(q)
{
    suggestedStationsReply = 0;
    journeysFromStationReply = 0;
}

void HslPrivate::slotSuggestedStationsFinished()
{
    Q_Q(Hsl);
    debug("hsl-plugin") << "Data retrieved from url"
                               << suggestedStationsReply->url().toString();

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.hsl");

    QDomDocument document;
    document.setContent(suggestedStationsReply);

    QList<Station> suggestedStations;

    QDomElement locElement = document.documentElement().firstChildElement().firstChildElement();
    while (!locElement.isNull()) {
        if (locElement.attribute("category") == "stop") {
            Station station;
            station.setDisambiguation(disambiguation);
            station.setName(locElement.attribute("name1"));

            QVariantMap properties;
            properties.insert("code", locElement.attribute("code"));
            properties.insert("backendName", "Hsl");
            properties.insert("city", locElement.attribute("city"));
            station.setProperties(properties);

            suggestedStations.append(station);
        }
        locElement = locElement.nextSiblingElement();
    }

    emit q->suggestedStationsRetrieved(suggestedStationsRequest, suggestedStations);
    suggestedStationsRequest = QString();
    suggestedStationsReply->deleteLater();
    suggestedStationsReply = 0;
}

void HslPrivate::slotJourneysFromStationFinished()
{
    Q_Q(Hsl);

    debug("hsl-plugin") << "Data retrieved from url"
                        << journeysFromStationReply->url().toString();

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.hsl");
    QTime currentTime = QTime::currentTime();

    Company company (disambiguation, "Hsl", QVariantMap());

    QMap<QString, QMap<QString, QList<int> > > lineToJourneysToWaitingTime;

    bool firstLineSkipped = false;
    while (!journeysFromStationReply->atEnd()) {
        QString line = journeysFromStationReply->readLine();
        if (!firstLineSkipped) {
            firstLineSkipped = true;
        } else {
            QStringList splittedLine = line.split("|");

            QString line = splittedLine.at(1);
            QString journey = splittedLine.at(2);

            QTime nextTime = QTime::fromString(splittedLine.at(0), "hhmm");
            if (nextTime.isValid()) {
                int minutes = ((currentTime.secsTo(nextTime) / 60) + 1440) % 1440;

                if (!lineToJourneysToWaitingTime.contains(line)) {
                    lineToJourneysToWaitingTime.insert(line, QMap<QString, QList<int> >());
                }

                if (!lineToJourneysToWaitingTime[line].contains(journey)) {
                    lineToJourneysToWaitingTime[line].insert(journey, QList<int>());
                }

                lineToJourneysToWaitingTime[line][journey].append(minutes);
            }
        }
    }

    QList<InfoJourneys> infoJourneysList;
    foreach (QString lineName, lineToJourneysToWaitingTime.keys()) {
        InfoJourneys infoJourneys;
        Line line (disambiguation, lineName, QVariantMap());
        infoJourneys.setCompany(company);
        infoJourneys.setLine(line);
        QList <QPair<Journey, Station> > journeysAndStations;

        bool ok = true;
        foreach (QString journeyName, lineToJourneysToWaitingTime.value(lineName).keys()) {
            Journey journey (disambiguation, journeyName, QVariantMap());

            QVariantMap properties;
            QList<int> waitingTimes
                    = lineToJourneysToWaitingTime.value(lineName).value(journeyName);
            properties.insert("waitingTimeCount", waitingTimes.count());

            if (waitingTimes.count() == 0) {
                ok = false;
            }

            for (int i = 0; i < waitingTimes.count(); i++) {
                properties.insert(QString("waitingTime%1").arg(i), waitingTimes.at(i));
            }

            Station station (disambiguation, journeysFromStationStation.name(), properties);
            QPair <Journey, Station> journeyAndStation;
            journeyAndStation.first = journey;
            journeyAndStation.second = station;
            journeysAndStations.append(journeyAndStation);
        }

        infoJourneys.setJourneysAndStations(journeysAndStations);
        if (ok) {
            infoJourneysList.append(infoJourneys);
        }
    }

    emit q->journeysFromStationRetrieved(journeysFromStationRequest, infoJourneysList);
    journeysFromStationRequest = QString();
    journeysFromStationStation = Station();
    journeysFromStationReply->deleteLater();
    journeysFromStationReply = 0;
}

////// End of private class //////

Hsl::Hsl(QObject *parent):
    ProviderPluginObject(parent), d_ptr(new HslPrivate(this))
{
    Q_D(Hsl);
    d->nam = new QNetworkAccessManager(this);
}

QStringList Hsl::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    capabilities.append(JOURNEYS_FROM_STATION);
    capabilities.append(WAITING_TIME);
    return capabilities;
}

void Hsl::retrieveCopyright(const QString &request)
{
    QString copyright = "Copyright HSL";
    emit copyrightRetrieved(request, copyright);
}

void Hsl::retrieveSuggestedStations(const QString &request, const QString &partialStation)
{
    Q_D(Hsl);
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

    QString urlString = "http://api.reittiopas.fi/public-ytv/fi/api/?key=%1&user=%2&pass=%3";
    urlString = urlString.arg(QUrl::toPercentEncoding(partialStation), USER, PASSWORD);

    d->suggestedStationsRequest = request;
    d->suggestedStationsReply = d->nam->get(QNetworkRequest(QUrl(urlString)));
    connect(d->suggestedStationsReply, SIGNAL(finished()),
            this, SLOT(slotSuggestedStationsFinished()));
}

void Hsl::retrieveJourneysFromStation(const QString &request, const Station &station,
                                            int limit)
{
    Q_D(Hsl);
    Q_UNUSED(limit)
    if (d->journeysFromStationReply) {
        if (!d->journeysFromStationReply->isFinished()) {
            d->journeysFromStationReply->abort();
        }
        d->journeysFromStationReply->deleteLater();
    }

    QString urlString = "http://api.reittiopas.fi/public-ytv/fi/api/?stop=%1&user=%2&pass=%3";
    QString stopCode = station.properties().value("code").toString();
    urlString = urlString.arg(QUrl::toPercentEncoding(stopCode), USER, PASSWORD);

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(urlString));

    d->journeysFromStationRequest = request;
    d->journeysFromStationStation = station;
    d->journeysFromStationReply = d->nam->get(networkRequest);

    connect(d->journeysFromStationReply, SIGNAL(finished()),
            this, SLOT(slotJourneysFromStationFinished()));

}

void Hsl::retrieveWaitingTime(const QString &request, const Company &company,
                              const Line &line, const Journey &journey, const Station &station)
{
    Q_UNUSED(company);
    Q_UNUSED(line);
    /// @todo do better here !
    QVariantMap properties;
    properties.insert("destination", journey.name());

    QList<WaitingTime> waitingTimeList;
    for (int i = 0; i < station.properties().value("waitingTimeCount").toInt(); i++) {
        WaitingTime waitingTime;
        waitingTime.setProperties(properties);
        int minutes = station.properties().value(QString("waitingTime%1").arg(i)).toInt();
        waitingTime.setWaitingTime(minutes);
        waitingTimeList.append(waitingTime);
    }

    emit waitingTimeRetrieved(request, waitingTimeList);
}

}

}

#include "moc_hsl.cpp"

Q_EXPORT_PLUGIN2(hsl, PublicTransportation::Provider::Hsl)

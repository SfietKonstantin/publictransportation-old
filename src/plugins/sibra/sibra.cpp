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
#include "common/journeyandwaitingtime.h"

#include "abstractcachedsuggestedstationshelper.h"

static const char *USER_AGENT = "Mozilla/5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) \
AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16";
static const char *JOURNEYS_REGEXP = "<span class=\"picto-arret-ligne picto-arret-l[^\"]\"><span>\
([^<]*)</span></span><span class=\"horaire\">Prochain bus à <strong>([^<]*)[^D]*Direction <strong>\
([^<]*)";

using namespace PublicTransportation::PluginHelper;

namespace PublicTransportation
{

namespace Provider
{

class SibraSuggestedStationHelper: public AbstractCachedSuggestedStationsHelper
{
public:
    explicit SibraSuggestedStationHelper(QNetworkAccessManager *networkAccessManager,
                                         QObject *parent = 0);
protected:
    virtual QList<Station> processData(QIODevice *input, bool *ok, QString *errorMessage);
};

class SibraPrivate
{
public:
    enum OperationType {
        Nothing,
        RetrieveJourneys,
        RetrieveWaitingTime
    };
    SibraPrivate(Sibra *q);
    static QString unaccent(const QString &string);
    void slotSuggestedStationsFinished();
    void slotJourneysOrWaitingTimeFinished();
    void emitSuggestedStationsRetrieved(const QString &request, const QString &partialStation);
    void createJourneysFromStation();
    void createWaitingTime();
    QNetworkAccessManager *nam;
    QNetworkReply *journeysOrWaitingTimeReply;
    OperationType journeysOrWaitingTimeOperation;
    QString journeysOrWaitingTimeRequest;
    Journey journeysOrWaitingTimeJourney;
    Station journeysOrWaitingTimeStation;
    QString journeysOrWaitingTimeJourneyName;
    SibraSuggestedStationHelper *suggestedStationsHelper;

private:
    Sibra * const q_ptr;
    Q_DECLARE_PUBLIC(Sibra)
};

SibraSuggestedStationHelper
    ::SibraSuggestedStationHelper(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractCachedSuggestedStationsHelper(networkAccessManager, parent)
{
}

QList<Station> SibraSuggestedStationHelper::processData(QIODevice *input, bool *ok,
                                                        QString *errorMessage)
{
    QRegExp stationRegExp
            = QRegExp("<li><a class=\"lien_arret[^\"]*\" href=\"([^\"]*)\"><span>([^<]*)<");

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.sibra");

    QList<Station> stations;

    while (!input->atEnd()) {
        QString data = input->readLine();
        if (data.indexOf(stationRegExp) != -1) {
            Station station;
            QString name = stationRegExp.cap(2).toLower();
            name[0] = name[0].toUpper();

            QVariantMap properties;
            properties.insert("subUrl", stationRegExp.cap(1));
            properties.insert("backendName", "SIBRA");

            station.setDisambiguation(disambiguation);
            station.setName(name);
            station.setProperties(properties);

            stations.append(station);
        }
    }

    if (ok) {
        *ok = true;
    }

    if (errorMessage) {
        *errorMessage = QString();
    }

    return stations;
}

SibraPrivate::SibraPrivate(Sibra *q):
    q_ptr(q)
{
    journeysOrWaitingTimeReply = 0;
    journeysOrWaitingTimeOperation = Nothing;
}

QString SibraPrivate::unaccent(const QString &string)
{
    QString canonicalForm = string.toLower().normalized(QString::NormalizationForm_D);
    QString returnedString;
    foreach (QChar c, canonicalForm) {
        if (c.category() != QChar::Mark_NonSpacing &&
            c.category() != QChar::Mark_SpacingCombining) {
              returnedString.append(c);
         }
    }

    return returnedString;
}

void SibraPrivate::slotJourneysOrWaitingTimeFinished()
{
    debug("sibra-plugin") << "Data retrieved from url"
                          << journeysOrWaitingTimeReply->url().toString();


    switch (journeysOrWaitingTimeOperation) {
    case RetrieveJourneys:
        createJourneysFromStation();
        break;
    case RetrieveWaitingTime:
        createWaitingTime();
        break;
    default:
        break;
    }

    journeysOrWaitingTimeRequest = QString();
    journeysOrWaitingTimeJourney = Journey();
    journeysOrWaitingTimeStation = Station();
    journeysOrWaitingTimeReply->deleteLater();
    journeysOrWaitingTimeReply = 0;
}

void SibraPrivate::createJourneysFromStation()
{
    Q_Q(Sibra);

    QRegExp journeysRegExp = QRegExp(JOURNEYS_REGEXP);

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.sibra");
    Company company (disambiguation, "SIBRA", QVariantMap());

    QMap<QString, QMap<QString, QList<int> > > lineToJourneysToWaitingTime;

    QTime currentTime = QTime::currentTime();

    while (!journeysOrWaitingTimeReply->atEnd()) {
        QString data = journeysOrWaitingTimeReply->readLine();
        if (data.indexOf(journeysRegExp) != -1) {

            QString line = journeysRegExp.cap(1);
            QString journey = journeysRegExp.cap(3);

            QTime nextTime = QTime::fromString(journeysRegExp.cap(2), "hh:mm");
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
            properties.insert("lastUpdateTime", currentTime.toString("hh:mm:ss"));
            properties.insert("subUrl", journeysOrWaitingTimeStation.properties().value("subUrl"));
            properties.insert("waitingTimeCount", waitingTimes.count());

            if (waitingTimes.count() == 0) {
                ok = false;
            }

            for (int i = 0; i < waitingTimes.count(); i++) {
                properties.insert(QString("waitingTime%1").arg(i), waitingTimes.at(i));
            }

            Station station (disambiguation, journeysOrWaitingTimeStation.name(), properties);
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


    emit q->journeysFromStationRetrieved(journeysOrWaitingTimeRequest, infoJourneysList);
}

void SibraPrivate::createWaitingTime()
{
    Q_Q(Sibra);

    QRegExp journeysRegExp = QRegExp(JOURNEYS_REGEXP);

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.sibra");

    QTime currentTime = QTime::currentTime();
    QList<JourneyAndWaitingTime> journeyAndWaitingTimeList;

    while (!journeysOrWaitingTimeReply->atEnd()) {
        QString data = journeysOrWaitingTimeReply->readLine();
        if (data.indexOf(journeysRegExp) != -1) {
            if (journeysRegExp.cap(3) == journeysOrWaitingTimeJourneyName) {
                QTime nextTime = QTime::fromString(journeysRegExp.cap(2), "hh:mm");
                int minutes = ((currentTime.secsTo(nextTime) / 60) + 1440) % 1440;

                QVariantMap properties;
                properties.insert("destination", journeysOrWaitingTimeJourneyName);
                WaitingTime waitingTime;
                waitingTime.setProperties(properties);
                waitingTime.setWaitingTime(minutes);
                journeyAndWaitingTimeList.append(JourneyAndWaitingTime(journeysOrWaitingTimeJourney,
                                                                       waitingTime));
            }
        }
    }

    emit q->waitingTimeRetrieved(journeysOrWaitingTimeRequest, journeyAndWaitingTimeList);
    journeysOrWaitingTimeJourneyName = QString();
}

////// End of private class //////

Sibra::Sibra(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new SibraPrivate(this))
{
    Q_D(Sibra);
    d->nam = new QNetworkAccessManager(this);
    d->suggestedStationsHelper = new SibraSuggestedStationHelper(d->nam, this);

    connect(d->suggestedStationsHelper, SIGNAL(errorRetrieved(QString,QString,QString)),
            this, SIGNAL(errorRetrieved(QString,QString,QString)));
    connect(d->suggestedStationsHelper,
            SIGNAL(suggestedStationsRetrieved(QString,QList<PublicTransportation::Station>)),
            this, SIGNAL(suggestedStationsRetrieved(QString,QList<PublicTransportation::Station>)));
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
    QString copyright = tr("This provider uses m.sibra.fr.") + "\n"
                        + QString::fromUtf8("Le site www.sibra.fr est la propriété de la \
Communauté de l'agglomération d'Annecy et de la Société Intercommunale des Bus de la Région \
Annécienne (SIBRA).");
    emit copyrightRetrieved(request, copyright);
}

void Sibra::retrieveSuggestedStations(const QString &request, const QString &partialStation)
{
    Q_D(Sibra);
    if (partialStation.size() < 2) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }

    QString urlString = "http://m.sibra.fr/temps-reel-mobile";
    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(urlString));
    networkRequest.setRawHeader("User-Agent", USER_AGENT);

    d->suggestedStationsHelper->suggestGet(request, networkRequest, partialStation);
}

void Sibra::retrieveJourneysFromStation(const QString &request, const Station &station, int limit)
{
    Q_D(Sibra);
    Q_UNUSED(limit)
    if (d->journeysOrWaitingTimeReply) {
        if (!d->journeysOrWaitingTimeReply->isFinished()) {
            d->journeysOrWaitingTimeReply->abort();
        }
        d->journeysOrWaitingTimeReply->deleteLater();
    }

    QString urlString = "http://m.sibra.fr/%1";
    urlString = urlString.arg(station.properties().value("subUrl").toString());

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(urlString));
    networkRequest.setRawHeader("User-Agent", USER_AGENT);

    d->journeysOrWaitingTimeOperation = SibraPrivate::RetrieveJourneys;
    d->journeysOrWaitingTimeRequest = request;
    d->journeysOrWaitingTimeStation = station;
    d->journeysOrWaitingTimeReply = d->nam->get(networkRequest);
    connect(d->journeysOrWaitingTimeReply, SIGNAL(finished()),
            this, SLOT(slotJourneysOrWaitingTimeFinished()));

}

void Sibra::retrieveWaitingTime(const QString &request, const Company &company,
                                const Line &line, const Journey &journey, const Station &station)
{
    Q_D(Sibra);
    Q_UNUSED(company);
    Q_UNUSED(line);


    QTime lastUpdate = QTime::fromString(station.properties().value("lastUpdateTime").toString(),
                                         "hh:mm:ss");
    QTime currentTime = QTime::currentTime();
    int secondsTo = lastUpdate.secsTo(currentTime);
    if (secondsTo < 0 || secondsTo > 20) {
        d->journeysOrWaitingTimeJourneyName = journey.name();

        QString urlString = "http://m.sibra.fr/%1";
        urlString = urlString.arg(station.properties().value("subUrl").toString());

        QNetworkRequest networkRequest;
        networkRequest.setUrl(QUrl(urlString));
        networkRequest.setRawHeader("User-Agent", USER_AGENT);

        d->journeysOrWaitingTimeOperation = SibraPrivate::RetrieveWaitingTime;
        d->journeysOrWaitingTimeRequest = request;
        d->journeysOrWaitingTimeJourney = journey;
        d->journeysOrWaitingTimeStation = station;
        d->journeysOrWaitingTimeReply = d->nam->get(networkRequest);
        connect(d->journeysOrWaitingTimeReply, SIGNAL(finished()),
                this, SLOT(slotJourneysOrWaitingTimeFinished()));
        return;
    }

    QVariantMap properties;
    properties.insert("destination", journey.name());

    QList<JourneyAndWaitingTime> journeyAndWaitingTimeList;
    for (int i = 0; i < station.properties().value("waitingTimeCount").toInt(); i++) {
        WaitingTime waitingTime;
        waitingTime.setProperties(properties);
        int minutes = station.properties().value(QString("waitingTime%1").arg(i)).toInt();
        waitingTime.setWaitingTime(minutes);
        journeyAndWaitingTimeList.append(JourneyAndWaitingTime(journey, waitingTime));
    }

    emit waitingTimeRetrieved(request, journeyAndWaitingTimeList);
}

}

}

#include "moc_sibra.cpp"

Q_EXPORT_PLUGIN2(sibra, PublicTransportation::Provider::Sibra)

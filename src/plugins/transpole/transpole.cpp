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

#include <QtCore/QtPlugin>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "debug.h"
#include "common/capabilitiesconstants.h"
#include "common/infojourneys.h"
#include "common/journeyandwaitingtime.h"

#include "languagehelper.h"
#include "transpolesuggestedstationshelper.h"
#include "transpolejourneysfromstationhelper.h"
#include "transpolewaitingtimehelper.h"

using namespace PublicTransportation::PluginHelper;

namespace PublicTransportation
{

namespace Provider
{

class TranspolePrivate
{
public:
    TranspolePrivate(Transpole *q);
    QNetworkAccessManager *nam;
    TranspoleSuggestedStationsHelper *suggestedStationsHelper;
    TranspoleJourneysFromStationHelper *journeysFromStationHelper;
    TranspoleWaitingTimeHelper *waitingTimeHelper;


private:
    Transpole * const q_ptr;
    Q_DECLARE_PUBLIC(Transpole)
};

TranspolePrivate::TranspolePrivate(Transpole *q):
    q_ptr(q)
{
}

////// End of private class //////

Transpole::Transpole(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new TranspolePrivate(this))
{
    Q_D(Transpole);
    d->nam = new QNetworkAccessManager(this);
    d->suggestedStationsHelper = new TranspoleSuggestedStationsHelper(d->nam, this);

    connect(d->suggestedStationsHelper, SIGNAL(errorRetrieved(QString,QString,QString)),
            this, SIGNAL(errorRetrieved(QString,QString,QString)));
    connect(d->suggestedStationsHelper,
            SIGNAL(suggestedStationsRetrieved(QString,QList<PublicTransportation::Station>)),
            this, SIGNAL(suggestedStationsRetrieved(QString,QList<PublicTransportation::Station>)));

    d->journeysFromStationHelper = new TranspoleJourneysFromStationHelper(d->nam, this);
    connect(d->journeysFromStationHelper, SIGNAL(errorRetrieved(QString,QString,QString)),
            this, SIGNAL(errorRetrieved(QString,QString,QString)));
    connect(d->journeysFromStationHelper,
            SIGNAL(journeysFromStationRetrieved(QString,QList<PublicTransportation::InfoJourneys>)),
            this,
           SIGNAL(journeysFromStationRetrieved(QString,QList<PublicTransportation::InfoJourneys>)));

    d->waitingTimeHelper = new TranspoleWaitingTimeHelper(d->nam, this);
    connect(d->waitingTimeHelper, SIGNAL(errorRetrieved(QString,QString,QString)),
            this, SIGNAL(errorRetrieved(QString,QString,QString)));
    connect(d->waitingTimeHelper,
           SIGNAL(waitingTimeRetrieved(QString,QList<PublicTransportation::JourneyAndWaitingTime>)),
            this,
          SIGNAL(waitingTimeRetrieved(QString,QList<PublicTransportation::JourneyAndWaitingTime>)));
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
    QString copyright = tr("This provider uses www.transpole.mobi/.") + "\n"
                        + "Transpole do not provide any copyright notice on the website, however\
we can assume that all the provided data are copyrighted transpole.";
    emit copyrightRetrieved(request, copyright);
}

void Transpole::retrieveSuggestedStations(const QString &request, const QString &partialStation)
{
    Q_D(Transpole);
    if (partialStation.size() < 2) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }


    QString urlString = "http://www.transpole.mobi/index.php?id=690";
    QByteArray postData = QByteArray("a=recherche_arret&arret=");
    postData.append(QUrl::toPercentEncoding(partialStation));

    d->suggestedStationsHelper->setData(LanguageHelper::unaccent(partialStation));
    d->suggestedStationsHelper->post(request, QNetworkRequest(urlString) , postData);
}

void Transpole::retrieveJourneysFromStation(const QString &request, const Station &station,
                                            int limit)
{
    Q_D(Transpole);

    QString urlString = "http://www.transpole.mobi/index.php?id=690";
    QByteArray postData = "a=recherche_codes&code=";
    QString code = station.properties().value("code").toString();
    postData.append(QUrl::toPercentEncoding(code));

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(urlString));

    d->journeysFromStationHelper->setData(station, limit);
    d->journeysFromStationHelper->post(request, networkRequest, postData);
}

void Transpole::retrieveWaitingTime(const QString &request, const Company &company,
                                    const Line &line, const Journey &journey,
                                    const Station &station)
{
    Q_D(Transpole);
    d->waitingTimeHelper->checkRan(company, line, journey, station);
    d->waitingTimeHelper->setData(company, line, journey, station);
    d->waitingTimeHelper->load(request);
}

}

}

#include "moc_transpole.cpp"

Q_EXPORT_PLUGIN2(transpole, PublicTransportation::Provider::Transpole)

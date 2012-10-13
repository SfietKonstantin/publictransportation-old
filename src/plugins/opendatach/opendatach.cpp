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

#include "opendatach.h"

#include <QtCore/QFile>
#include <QtCore/QtPlugin>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <parser.h>

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

class OpenDataChPrivate
{
public:
    OpenDataChPrivate(OpenDataCh *q);
    void slotSuggestedStationsFinished();
    QNetworkAccessManager *nam;
    QNetworkReply *suggestedStationsReply;
    QString suggestedStationsRequest;
private:
    OpenDataCh * const q_ptr;
    Q_DECLARE_PUBLIC(OpenDataCh)
};

OpenDataChPrivate::OpenDataChPrivate(OpenDataCh *q):
    q_ptr(q)
{
    suggestedStationsReply = 0;
}

void OpenDataChPrivate::slotSuggestedStationsFinished()
{
    Q_Q(OpenDataCh);
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(q->sender());

    debug("opendatach-plugin") << "Data retrieved from url" << reply->url().toString();
    QJson::Parser parser;

    QVariantMap data = parser.parse(reply).toMap();
    QVariantList stationDataList = data.value("stations").toList();

    QList<Station> suggestedStations;
    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.opendatach");

    QVariantMap properties;
    properties.insert("providerName", "transport.opendata.ch");

    foreach (QVariant stationData, stationDataList) {
        QVariantMap stationDataMap = stationData.toMap();
        Station station (disambiguation, stationDataMap.value("name").toString(), properties);
        suggestedStations.append(station);
    }

    emit q->suggestedStationsRetrieved(suggestedStationsRequest, suggestedStations);
}

////// End of private class //////

OpenDataCh::OpenDataCh(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new OpenDataChPrivate(this))
{
    Q_D(OpenDataCh);
    d->nam = new QNetworkAccessManager(this);
}

QStringList OpenDataCh::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    return capabilities;
}

void OpenDataCh::retrieveSuggestedStations(const QString &request, const QString &partialStation)
{
    Q_D(OpenDataCh);
    if (partialStation.size() < 3) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }

    if (d->suggestedStationsReply) {
        if (!d->suggestedStationsReply->isFinished()) {
            d->suggestedStationsReply->abort();
        }
        d->suggestedStationsReply->deleteLater();
    }

    d->suggestedStationsRequest = request;

    QString urlString = "http://transport.opendata.ch/v1/locations?query=%1&type=station";
    urlString = urlString.arg(partialStation);

    d->suggestedStationsReply = d->nam->get(QNetworkRequest(QUrl(urlString)));
    connect(d->suggestedStationsReply, SIGNAL(finished()),
            this, SLOT(slotSuggestedStationsFinished()));
}

}

}

#include "moc_opendatach.cpp"

Q_EXPORT_PLUGIN2(tl, PublicTransportation::Provider::OpenDataCh)

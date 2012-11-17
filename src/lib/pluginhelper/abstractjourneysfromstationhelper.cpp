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

/**
 * @file abstractjourneysfromstationhelper.cpp
 * @short Implementation of PublicTransportation::PluginHelper::AbstractJourneysFromStationHelper
 */

#include "abstractjourneysfromstationhelper.h"
#include "abstractjourneysfromstationhelper_p.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "common/errorid.h"
#include "common/infojourneys.h"
#include "debug.h"

namespace PublicTransportation
{

namespace PluginHelper
{

AbstractJourneysFromStationHelperPrivate
    ::AbstractJourneysFromStationHelperPrivate(AbstractJourneysFromStationHelper *q):
    AbstractOnlineHelperPrivate(q)
{
}

void AbstractJourneysFromStationHelperPrivate::processReply(QNetworkReply *reply)
{
    Q_Q(AbstractJourneysFromStationHelper);

    QString request = repliesAndRequests.value(reply);

    bool ok;
    QString errorMessage;
    QList<InfoJourneys> infoJourneysList = q->processData(reply, &ok, &errorMessage);
    if (!ok) {
        emit q->errorRetrieved(request, BACKEND_WARNING, errorMessage);
    } else {
        emit q->journeysFromStationRetrieved(request, infoJourneysList);
    }
}

void AbstractJourneysFromStationHelperPrivate::cleanup()
{
    station = Station();
    limit = -1;
    AbstractOnlineHelperPrivate::cleanup();
}

////// End of private class //////

AbstractJourneysFromStationHelper
    ::AbstractJourneysFromStationHelper(QNetworkAccessManager *networkAccessManager,
                                        QObject *parent):
    AbstractOnlineHelper(*(new AbstractJourneysFromStationHelperPrivate(this)), parent)
{
    Q_D(AbstractJourneysFromStationHelper);
    d->networkAccessManager = networkAccessManager;
}

AbstractJourneysFromStationHelper
    ::AbstractJourneysFromStationHelper(AbstractJourneysFromStationHelperPrivate &dd,
                                        QObject *parent):
    AbstractOnlineHelper(dd, parent)
{
}

void AbstractJourneysFromStationHelper::setData(const Station &station, int limit)
{
    Q_D(AbstractJourneysFromStationHelper);
    d->station = station;
    d->limit = limit;
}

Station AbstractJourneysFromStationHelper::station() const
{
    Q_D(const AbstractJourneysFromStationHelper);
    return d->station;
}

int AbstractJourneysFromStationHelper::limit() const
{
    Q_D(const AbstractJourneysFromStationHelper);
    return d->limit;
}

}

}

#include "moc_abstractsuggestedstationshelper.cpp"

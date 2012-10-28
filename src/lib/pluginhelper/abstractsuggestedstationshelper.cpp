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

#include "abstractsuggestedstationshelper.h"
#include "abstractsuggestedstationshelper_p.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "common/errorid.h"
#include "common/station.h"
#include "debug.h"

namespace PublicTransportation
{

namespace PluginHelper
{

AbstractSuggestedStationsHelperPrivate
    ::AbstractSuggestedStationsHelperPrivate(AbstractSuggestedStationsHelper *q):
    AbstractOnlineHelperPrivate(q)
{
}

void AbstractSuggestedStationsHelperPrivate::processReply(QNetworkReply *reply)
{
    Q_Q(AbstractSuggestedStationsHelper);

    QString request = repliesAndRequests.value(reply);

    bool ok;
    QString errorMessage;
    QList<Station> suggestedStations = q->processData(reply, &ok, &errorMessage);
    if (!ok) {
        emit q->errorRetrieved(request, BACKEND_WARNING, errorMessage);
    } else {
        emit q->suggestedStationsRetrieved(request, suggestedStations);
    }
}

void AbstractSuggestedStationsHelperPrivate::cleanup()
{
    partialStation = QString();
    AbstractOnlineHelperPrivate::cleanup();
}

////// End of private class //////

AbstractSuggestedStationsHelper
    ::AbstractSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractOnlineHelper(*(new AbstractSuggestedStationsHelperPrivate(this)), parent)
{
    Q_D(AbstractSuggestedStationsHelper);
    d->networkAccessManager = networkAccessManager;
}

AbstractSuggestedStationsHelper
    ::AbstractSuggestedStationsHelper(AbstractSuggestedStationsHelperPrivate &dd, QObject *parent):
    AbstractOnlineHelper(dd, parent)
{
}

void AbstractSuggestedStationsHelper::setData(const QString &partialStation)
{
    Q_D(AbstractSuggestedStationsHelper);
    d->partialStation = partialStation;
}

QString AbstractSuggestedStationsHelper::partialStation() const
{
    Q_D(const AbstractSuggestedStationsHelper);
    return d->partialStation;
}

}

}

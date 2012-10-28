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
    q_ptr(q)
{
    reply = 0;
}

AbstractSuggestedStationsHelperPrivate::~AbstractSuggestedStationsHelperPrivate()
{
}

void AbstractSuggestedStationsHelperPrivate::slotFinished()
{
    Q_Q(AbstractSuggestedStationsHelper);
    debug("helper-abssuggestedstations") << "Data retrieved from url" << reply->url().toString();

    bool ok;
    QString errorMessage;
    QList<Station> suggestedStations = q->processData(reply, &ok, &errorMessage);
    if (!ok) {
        emit q->errorRetrieved(request, BACKEND_WARNING, errorMessage);
    } else {
        emit q->suggestedStationsRetrieved(request, suggestedStations);
    }
    reply->deleteLater();
    reply = 0;
    request = QString();
    partialStation = QString();
}

////// End of private class //////

AbstractSuggestedStationsHelper
    ::AbstractSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager, QObject *parent):
    QObject(parent), d_ptr(new AbstractSuggestedStationsHelperPrivate(this))
{
    Q_D(AbstractSuggestedStationsHelper);
    d->networkAccessManager = networkAccessManager;
}

AbstractSuggestedStationsHelper
    ::AbstractSuggestedStationsHelper(AbstractSuggestedStationsHelperPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
}

AbstractSuggestedStationsHelper::~AbstractSuggestedStationsHelper()
{
}

void AbstractSuggestedStationsHelper::get(const QString &request,
                                          const QNetworkRequest &networkRequest,
                                          const QString &partialStation)
{
    Q_D(AbstractSuggestedStationsHelper);
    if (!d->networkAccessManager) {
        return;
    }

    if (d->reply) {
        if (!d->reply->isFinished()) {
            d->reply->abort();
        }
        d->reply->deleteLater();
    }

    d->request = request;
    d->partialStation = partialStation;


    d->reply = d->networkAccessManager->get(networkRequest);
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
}

void AbstractSuggestedStationsHelper::post(const QString &request,
                                           const QNetworkRequest &networkRequest,
                                           const QByteArray &data, const QString &partialStation)
{
    Q_D(AbstractSuggestedStationsHelper);
    if (!d->networkAccessManager) {
        return;
    }

    if (d->reply) {
        if (!d->reply->isFinished()) {
            d->reply->abort();
        }
        d->reply->deleteLater();
    }

    d->request = request;
    d->partialStation = partialStation;

    d->reply = d->networkAccessManager->post(networkRequest, data);
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
}

QString AbstractSuggestedStationsHelper::partialStation() const
{
    Q_D(const AbstractSuggestedStationsHelper);
    return d->partialStation;
}

}

}

#include "moc_abstractsuggestedstationshelper.cpp"

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

#include "abstractonlinehelper.h"
#include "abstractonlinehelper_p.h"

#include <QtNetwork/QNetworkAccessManager>

#include "common/errorid.h"
#include "debug.h"

namespace PublicTransportation
{

namespace PluginHelper
{

AbstractOnlineHelperPrivate::AbstractOnlineHelperPrivate(AbstractOnlineHelper *q):
    q_ptr(q)
{
}

AbstractOnlineHelperPrivate::~AbstractOnlineHelperPrivate()
{
}

void AbstractOnlineHelperPrivate::slotFinished()
{
    Q_Q(AbstractOnlineHelper);
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(q->sender());

    if (!reply) {
        return;
    }

    debug("helper-abstractonline") << "Data retrieved from url" << reply->url().toString();

    processReply(reply);
    cleanup();
}

void AbstractOnlineHelperPrivate::slotError(QNetworkReply::NetworkError networkError)
{
    warning("helper-abstractonline") << "Network error" << networkError;
}

void AbstractOnlineHelperPrivate::cleanup()
{
    foreach (QNetworkReply *reply, repliesAndRequests.keys()) {
        if (reply->isFinished()) {
            repliesAndRequests.remove(reply);
            reply->deleteLater();
        }
    }
}

////// End of private class //////

AbstractOnlineHelper::AbstractOnlineHelper(AbstractOnlineHelperPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
}

AbstractOnlineHelper::~AbstractOnlineHelper()
{
}

void AbstractOnlineHelper::get(const QString &request, const QNetworkRequest &networkRequest)
{
    Q_D(AbstractOnlineHelper);
    if (!d->networkAccessManager) {
        return;
    }

    foreach (QNetworkReply *reply, d->repliesAndRequests.keys()) {
        if (!reply->isFinished()) {
            reply->abort();
        }
    }


    QNetworkReply *reply = d->networkAccessManager->get(networkRequest);
    connect(reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
    d->repliesAndRequests.insert(reply, request);
}

void AbstractOnlineHelper::post(const QString &request, const QNetworkRequest &networkRequest,
                                const QByteArray &data)
{
    Q_D(AbstractOnlineHelper);
    if (!d->networkAccessManager) {
        return;
    }

    foreach (QNetworkReply *reply, d->repliesAndRequests.keys()) {
        if (!reply->isFinished()) {
            reply->abort();
        }
    }

    QNetworkReply *reply = d->networkAccessManager->post(networkRequest, data);
    connect(reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
    d->repliesAndRequests.insert(reply, request);
}

}

}

#include "moc_abstractonlinehelper.cpp"

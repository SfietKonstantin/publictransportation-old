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

#include "abstractwaitingtimehelper.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "common/errorid.h"
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/journeyandwaitingtime.h"
#include "debug.h"

namespace PublicTransportation
{

namespace PluginHelper
{

class AbstractWaitingTimeHelperPrivate
{
public:
    AbstractWaitingTimeHelperPrivate(AbstractWaitingTimeHelper *q);
    void slotFinished();
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *reply;
    QString request;
    Company company;
    Line line;
    Journey journey;
    Station station;
private:
    AbstractWaitingTimeHelper * const q_ptr;
    Q_DECLARE_PUBLIC(AbstractWaitingTimeHelper)
};

AbstractWaitingTimeHelperPrivate
    ::AbstractWaitingTimeHelperPrivate(AbstractWaitingTimeHelper *q):
    q_ptr(q)
{
}

void AbstractWaitingTimeHelperPrivate::slotFinished()
{
    Q_Q(AbstractWaitingTimeHelper);
    debug("helper-abswaitingtime") << "Data retrieved from url"
                                   << reply->url().toString();

    bool ok;
    QString errorMessage;
    QList<JourneyAndWaitingTime> journeysAndWaitingTimes = q->processData(reply, &ok,
                                                                          &errorMessage);
    if (!ok) {
        emit q->errorRetrieved(request, BACKEND_WARNING, errorMessage);
    } else {
        emit q->waitingTimeRetrieved(request, journeysAndWaitingTimes);
    }
    reply->deleteLater();
    reply = 0;

    request = QString();
    company = Company();
    line = Line();
    journey = Journey();
    station = Station();
}

////// End of private class //////

AbstractWaitingTimeHelper::AbstractWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                                     QObject *parent):
    QObject(parent), d_ptr(new AbstractWaitingTimeHelperPrivate(this))
{
    Q_D(AbstractWaitingTimeHelper);
    d->networkAccessManager = networkAccessManager;
    d->reply = 0;
}

AbstractWaitingTimeHelper::~AbstractWaitingTimeHelper()
{
}

void AbstractWaitingTimeHelper::get(const QString &request, const QString &url,
                                    const Company &company, const Line &line,
                                    const Journey &journey, const Station &station)
{
    Q_D(AbstractWaitingTimeHelper);
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
    d->company = company;
    d->line = line;
    d->journey = journey;
    d->station = station;


    d->reply = d->networkAccessManager->get(QNetworkRequest(QUrl(url)));
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
}

void AbstractWaitingTimeHelper::post(const QString &request, const QString &url,
                                               const QByteArray &data,
                                               const Company &company, const Line &line,
                                               const Journey &journey, const Station &station)
{
    Q_D(AbstractWaitingTimeHelper);
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
    d->company = company;
    d->line = line;
    d->journey = journey;
    d->station = station;


    d->reply = d->networkAccessManager->post(QNetworkRequest(QUrl(url)), data);
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
}

Company AbstractWaitingTimeHelper::company() const
{
    Q_D(const AbstractWaitingTimeHelper);
    return d->company;
}

Line AbstractWaitingTimeHelper::line() const
{
    Q_D(const AbstractWaitingTimeHelper);
    return d->line;
}

Journey AbstractWaitingTimeHelper::journey() const
{
    Q_D(const AbstractWaitingTimeHelper);
    return d->journey;
}

Station AbstractWaitingTimeHelper::station() const
{
    Q_D(const AbstractWaitingTimeHelper);
    return d->station;
}

}

}

#include "moc_abstractwaitingtimehelper.cpp"

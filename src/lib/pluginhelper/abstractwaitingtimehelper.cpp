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
 * @file abstractwaitingtimehelper.cpp
 * @short Implementation of PublicTransportation::PluginHelper::AbstractWaitingTimeHelper
 */

#include "abstractwaitingtimehelper.h"
#include "abstractwaitingtimehelper_p.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "common/errorid.h"
#include "common/journeyandwaitingtime.h"
#include "debug.h"

namespace PublicTransportation
{

namespace PluginHelper
{

AbstractWaitingTimeHelperPrivate
    ::AbstractWaitingTimeHelperPrivate(AbstractWaitingTimeHelper *q):
    AbstractOnlineHelperPrivate(q)
{
}

void AbstractWaitingTimeHelperPrivate::processReply(QNetworkReply *reply)
{
    Q_Q(AbstractWaitingTimeHelper);

    QString request = repliesAndRequests.value(reply);

    bool ok;
    QString errorMessage;
    QList<JourneyAndWaitingTime> journeysAndWaitingTimes = q->processData(reply, &ok,
                                                                          &errorMessage);
    if (!ok) {
        emit q->errorRetrieved(request, BACKEND_WARNING, errorMessage);
    } else {
        emit q->waitingTimeRetrieved(request, journeysAndWaitingTimes);
    }
}

void AbstractWaitingTimeHelperPrivate::cleanup()
{
    company = Company();
    line = Line();
    journey = Journey();
    station = Station();

    AbstractOnlineHelperPrivate::cleanup();
}

////// End of private class //////

AbstractWaitingTimeHelper::AbstractWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                                     QObject *parent):
    AbstractOnlineHelper(*(new AbstractWaitingTimeHelperPrivate(this)), parent)
{
    Q_D(AbstractWaitingTimeHelper);
    d->networkAccessManager = networkAccessManager;
}

AbstractWaitingTimeHelper::AbstractWaitingTimeHelper(AbstractWaitingTimeHelperPrivate &dd,
                                                     QObject *parent):
    AbstractOnlineHelper(dd, parent)
{
}

void AbstractWaitingTimeHelper::setData(const Company &company, const Line &line,
                                        const Journey &journey, const Station &station)
{
    Q_D(AbstractWaitingTimeHelper);
    d->company = company;
    d->line = line;
    d->journey = journey;
    d->station = station;
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

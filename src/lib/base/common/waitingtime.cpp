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
 * @file waitingtime.cpp
 * @short Implementation of PublicTransportation::WaitingTime
 */

#include "waitingtime.h"

namespace PublicTransportation
{

WaitingTime::WaitingTime():
    d_ptr(new WaitingTimePrivate)
{
    Q_D(WaitingTime);
    d->waitingTime = -1;
}

WaitingTime::WaitingTime(int waitingTime, const QVariantMap &properties):
    d_ptr(new WaitingTimePrivate)
{
    Q_D(WaitingTime);
    d->waitingTime = waitingTime;
    d->properties = properties;
}

WaitingTime::WaitingTime(const WaitingTime &other):
    d_ptr(other.d_ptr)
{
}

WaitingTime::WaitingTime(WaitingTimePrivate &dd):
    d_ptr(&dd)
{
}

WaitingTime::~WaitingTime()
{
}

bool WaitingTime::isNull() const
{
    Q_D(const WaitingTime);
    return (d->waitingTime < 0);
}

int WaitingTime::waitingTime() const
{
    Q_D(const WaitingTime);
    return d->waitingTime;
}

void WaitingTime::setWaitingTime(int waitingTime)
{
    Q_D(WaitingTime);
    d->waitingTime = waitingTime;
}

QVariantMap WaitingTime::properties() const
{
    Q_D(const WaitingTime);
    return d->properties;
}

void WaitingTime::setProperties(const QVariantMap &properties)
{
    Q_D(WaitingTime);
    d->properties = properties;
}

}

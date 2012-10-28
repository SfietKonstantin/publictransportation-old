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
 * @file journeyandwaitingtime.cpp
 * @short Implemnetation of PublicTransportation::JourneyAndWaitingTime
 */

#include "journeyandwaitingtime.h"

namespace PublicTransportation
{

JourneyAndWaitingTime::JourneyAndWaitingTime():
    d_ptr(new JourneyAndWaitingTimePrivate())
{
}

JourneyAndWaitingTime::JourneyAndWaitingTime(const Journey &journey,
                                             const WaitingTime &waitingTime):
    d_ptr(new JourneyAndWaitingTimePrivate())
{
    Q_D(JourneyAndWaitingTime);
    d->journey = journey;
    d->waitingTime = waitingTime;
}

JourneyAndWaitingTime::JourneyAndWaitingTime(const JourneyAndWaitingTime &other):
    d_ptr(other.d_ptr)
{
}

JourneyAndWaitingTime::~JourneyAndWaitingTime()
{
}

bool JourneyAndWaitingTime::operator==(const JourneyAndWaitingTime &other) const
{
    Q_D(const JourneyAndWaitingTime);
    return (d->journey == other.journey());
}

bool JourneyAndWaitingTime::isNull() const
{
    Q_D(const JourneyAndWaitingTime);
    return d->journey.isNull();
}

Journey JourneyAndWaitingTime::journey() const
{
    Q_D(const JourneyAndWaitingTime);
    return d->journey;
}

void JourneyAndWaitingTime::setJourney(const Journey &journey)
{
    Q_D(JourneyAndWaitingTime);
    d->journey = journey;
}

WaitingTime JourneyAndWaitingTime::waitingTime() const
{
    Q_D(const JourneyAndWaitingTime);
    return d->waitingTime;
}

void JourneyAndWaitingTime::setWaitingTime(const WaitingTime &waitingTime)
{
    Q_D(JourneyAndWaitingTime);
    d->waitingTime = waitingTime;
}

}

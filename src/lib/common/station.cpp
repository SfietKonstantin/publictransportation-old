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
 * @file station.cpp
 * @short Implementation of PublicTransportation::Station
 */

#include "station.h"

#include "journey.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::Station
 */
class StationPrivate: public TransportationObjectPrivate
{
public:
    /**
     * @internal
     * @brief Journey
     */
    Journey journey;
    /**
     * @internal
     * @brief Waiting time
     */
    QList<WaitingTime> waitingTime;
};

////// End of private class //////


Station::Station() :
    TransportationObject(* new StationPrivate)
{
}

Station::Station(const QVariantMap &disambiguation, const QString &name,
                 const Journey &journey, const QVariantMap &properties):
    TransportationObject(* new StationPrivate)
{
    Q_D(Station);
    d->disambiguation = disambiguation;
    d->name = name;
    d->properties = properties;

    setJourney(journey);
}

Station::~Station()
{
}

Journey Station::journey() const
{
    Q_D(const Station);
    return d->journey;
}

void Station::setJourney(const Journey &journey)
{
    Q_D(Station);
    d->journey = journey;
    d->journey.addStation(*this);
}

QList<WaitingTime> Station::waitingTime() const
{
    Q_D(const Station);
    return d->waitingTime;
}

void Station::setWaitingTime(const QList<WaitingTime> &waitingTime)
{
    Q_D(Station);
    d->waitingTime = waitingTime;
}

}

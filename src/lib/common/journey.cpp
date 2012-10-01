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
 * @file journey.cpp
 * @short Implementation of PublicTransportation::Journey
 */

#include "journey.h"

#include <QtCore/QList>

#include "line.h"
#include "station.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::Journey
 */
struct JourneyPrivate: public TransportationObjectPrivate
{
    /**
     * @internal
     * @brief Line
     */
    Line line;
    /**
     * @internal
     * @brief Stations
     */
    QList<Station> stations;
};

////// End of private class //////

Journey::Journey() :
    TransportationObject(*new JourneyPrivate)
{
}

Journey::Journey(const QVariantMap &disambiguation, const QString &name,
                 const Line &line, const QVariantMap &properties):
    TransportationObject(*new JourneyPrivate)
{
    Q_D(Journey);

    d->disambiguation = disambiguation;
    d->name = name;
    d->properties = properties;

    setLine(line);
}

Journey::~Journey()
{
}

Line Journey::line() const
{
    Q_D(const Journey);
    return d->line;
}

void Journey::setLine(const Line &line)
{
    Q_D(Journey);
    d->line = line;
    d->line.addJourney(*this);
}

QList<Station> Journey::stations() const
{
    Q_D(const Journey);
    return d->stations;
}

void Journey::addStation(const Station &station)
{
    Q_D(Journey);
    if (d->stations.contains(station)) {
        return;
    }

    d->stations.append(station);
}

void Journey::removeStation(const Station &station)
{
    Q_D(Journey);
    if (!d->stations.contains(station)) {
        return;
    }

    d->stations.removeAll(station);
}

}

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
 * @file line.cpp
 * @short Implementation of PublicTransportation::Line
 */

#include "line.h"

#include "company.h"
#include "journey.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::Line
 */
struct LinePrivate: public TransportationObjectPrivate
{
    /**
     * @internal
     * @brief Company
     */
    Company company;
    /**
     * @internal Journeys
     * @brief journeys
     */
    QList<Journey> journeys;
};

////// End of private class //////

Line::Line() :
    TransportationObject(*new LinePrivate)
{
}

Line::Line(const QVariantMap &disambiguation, const QString &name,
           const Company &company, const QVariantMap &properties):
    TransportationObject(*new LinePrivate)
{
    Q_D(Line);
    d->disambiguation = disambiguation;
    d->name = name;
    d->properties = properties;

    setCompany(company);
}

Line::~Line()
{
}

Company Line::company() const
{
    Q_D(const Line);
    return d->company;
}

void Line::setCompany(const Company &company)
{
    Q_D(Line);
    d->company = company;
    d->company.addLine(*this);
}

QList<Journey> Line::journeys() const
{
    Q_D(const Line);
    return d->journeys;
}

void Line::addJourney(const Journey &journey)
{
    Q_D(Line);
    if (d->journeys.contains(journey)) {
        return;
    }

    d->journeys.append(journey);
}

void Line::removeJourney(const Journey &journey)
{
    Q_D(Line);
    if (!d->journeys.contains(journey)) {
        return;
    }

    d->journeys.removeAll(journey);
}

}

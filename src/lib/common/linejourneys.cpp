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

#include "linejourneys.h"

namespace PublicTransportation
{

LineJourneys::LineJourneys():
    d_ptr(new LineJourneysPrivate())
{
}

LineJourneys::LineJourneys(const Line &line, const QList<Journey> &journeys):
    d_ptr(new LineJourneysPrivate())
{
    Q_D(LineJourneys);
    d->line = line;
    d->journeys = journeys;
}

LineJourneys::LineJourneys(const LineJourneys &other):
    d_ptr(other.d_ptr)
{
}

LineJourneys::~LineJourneys()
{
}

bool LineJourneys::operator==(const LineJourneys &other) const
{
    Q_D(const LineJourneys);
    return (d->line == other.line()) && (d->journeys == other.journeys());
}

bool LineJourneys::isNull() const
{
    Q_D(const LineJourneys);
    return d->line.isNull();
}

Line LineJourneys::line() const
{
    Q_D(const LineJourneys);
    return d->line;
}

void LineJourneys::setLine(const Line &line)
{
    Q_D(LineJourneys);
    d->line = line;
}

QList<Journey> LineJourneys::journeys() const
{
    Q_D(const LineJourneys);
    return d->journeys;
}

void LineJourneys::setJourneys(const QList<Journey> &journeys)
{
    Q_D(LineJourneys);
    d->journeys = journeys;
}

}

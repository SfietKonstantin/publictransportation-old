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
 * @file infojourneys.cpp
 * @short Implemnetation of PublicTransportation::InfoJourneys
 */

#include "infojourneys.h"

namespace PublicTransportation
{

InfoJourneys::InfoJourneys():
    d_ptr(new InfoJourneysPrivate())
{
}

InfoJourneys::InfoJourneys(const Company &company, const Line &line,
                           const QList<QPair<Journey, Station> > &journeysStations):
    d_ptr(new InfoJourneysPrivate())
{
    Q_D(InfoJourneys);
    d->company = company;
    d->line = line;
    d->journeysStations = journeysStations;
}

InfoJourneys::InfoJourneys(const InfoJourneys &other):
    d_ptr(other.d_ptr)
{
}

InfoJourneys::~InfoJourneys()
{
}

bool InfoJourneys::operator==(const InfoJourneys &other) const
{
    Q_D(const InfoJourneys);
    return (d->company == other.company())
            && (d->line == other.line())
            && (d->journeysStations == other.journeysAndStations());
}

bool InfoJourneys::isNull() const
{
    Q_D(const InfoJourneys);
    return d->company.isNull() || d->line.isNull();
}

Company InfoJourneys::company() const
{
    Q_D(const InfoJourneys);
    return d->company;
}

void InfoJourneys::setCompany(const Company &company)
{
    Q_D(InfoJourneys);
    d->company = company;
}

Line InfoJourneys::line() const
{
    Q_D(const InfoJourneys);
    return d->line;
}

void InfoJourneys::setLine(const Line &line)
{
    Q_D(InfoJourneys);
    d->line = line;
}

QList<QPair<Journey, Station> > InfoJourneys::journeysAndStations() const
{
    Q_D(const InfoJourneys);
    return d->journeysStations;
}

void InfoJourneys::setJourneysAndStations(const QList<QPair<Journey, Station> > &journeysStations)
{
    Q_D(InfoJourneys);
    d->journeysStations = journeysStations;
}

}

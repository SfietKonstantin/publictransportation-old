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
 * @file infojourneywaitingtime.cpp
 * @short Implemnetation of PublicTransportation::InfoJourneys
 */

#include "infojourneywaitingtime.h"

namespace PublicTransportation
{

InfoJourneyWaitingTime::InfoJourneyWaitingTime():
    d_ptr(new InfoJourneyWaitingTimePrivate())
{
}

InfoJourneyWaitingTime::InfoJourneyWaitingTime(const Company &company, const Line &line,
                                               const Journey &journey, const Station &station):
    d_ptr(new InfoJourneyWaitingTimePrivate())
{
    Q_D(InfoJourneyWaitingTime);
    d->company = company;
    d->line = line;
    d->journey = journey;
    d->station = station;
}

InfoJourneyWaitingTime::InfoJourneyWaitingTime(const InfoJourneyWaitingTime &other):
    d_ptr(other.d_ptr)
{
}

InfoJourneyWaitingTime::~InfoJourneyWaitingTime()
{
}

bool InfoJourneyWaitingTime::operator==(const InfoJourneyWaitingTime &other) const
{
    Q_D(const InfoJourneyWaitingTime);
    return (d->company == other.company())
            && (d->line == other.line())
            && (d->journey == other.journey()
            && (d->station == other.station()));
}

bool InfoJourneyWaitingTime::isNull() const
{
    Q_D(const InfoJourneyWaitingTime);
    return d->company.isNull() || d->line.isNull() || d->journey.isNull() || d->station.isNull();
}

Company InfoJourneyWaitingTime::company() const
{
    Q_D(const InfoJourneyWaitingTime);
    return d->company;
}

void InfoJourneyWaitingTime::setCompany(const Company &company)
{
    Q_D(InfoJourneyWaitingTime);
    d->company = company;
}

Line InfoJourneyWaitingTime::line() const
{
    Q_D(const InfoJourneyWaitingTime);
    return d->line;
}

void InfoJourneyWaitingTime::setLine(const Line &line)
{
    Q_D(InfoJourneyWaitingTime);
    d->line = line;
}

Journey InfoJourneyWaitingTime::journey() const
{
    Q_D(const InfoJourneyWaitingTime);
    return d->journey;
}

void InfoJourneyWaitingTime::setJourney(const Journey &journey)
{
    Q_D(InfoJourneyWaitingTime);
    d->journey = journey;
}

Station InfoJourneyWaitingTime::station() const
{
    Q_D(const InfoJourneyWaitingTime);
    return d->station;
}

void InfoJourneyWaitingTime::setStation(const Station &station)
{
    Q_D(InfoJourneyWaitingTime);
    d->station = station;
}

}

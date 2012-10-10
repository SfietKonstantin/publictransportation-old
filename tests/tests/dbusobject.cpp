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

#include "dbusobject.h"
#include <QtCore/QDebug>

DBusObject::DBusObject(QObject *parent) :
    QObject(parent)
{
}

PublicTransportation::Company DBusObject::company() const
{
    return m_company;
}

PublicTransportation::Line DBusObject::line() const
{
    return m_line;
}

PublicTransportation::Journey DBusObject::journey() const
{
    return m_journey;
}

PublicTransportation::Station DBusObject::station() const
{
    return m_station;
}

PublicTransportation::WaitingTime DBusObject::waitingTime() const
{
    return m_waitingTime;
}

void DBusObject::receiveCompany(const PublicTransportation::Company &company)
{
    qDebug() << "Company received";
    m_company = company;
}

void DBusObject::receiveLine(const PublicTransportation::Line &line)
{
    qDebug() << "Line received";
    m_line = line;
}

void DBusObject::receiveJourney(const PublicTransportation::Journey &journey)
{
    qDebug() << "Journey received";
    m_journey = journey;
}

void DBusObject::receiveStation(const PublicTransportation::Station &station)
{
    qDebug() << "Station received";
    m_station = station;
}

void DBusObject::receiveWaitingTime(const PublicTransportation::WaitingTime &waitingTime)
{
    qDebug() << "Waiting time received";
    m_waitingTime = waitingTime;
}

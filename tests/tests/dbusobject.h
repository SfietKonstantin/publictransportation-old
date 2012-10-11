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

#ifndef DBUSOBJECT_H
#define DBUSOBJECT_H

#include <QtCore/QObject>
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/waitingtime.h"
#include "common/linejourneys.h"

class DBusObject : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.SfietKonstantin.publictransportation")
public:
    explicit DBusObject(QObject *parent = 0);
    PublicTransportation::Company company() const;
    PublicTransportation::Line line() const;
    PublicTransportation::Journey journey() const;
    PublicTransportation::Station station() const;
    PublicTransportation::WaitingTime waitingTime() const;
    PublicTransportation::LineJourneys lineJourneys() const;
public slots:
    void receiveCompany(const PublicTransportation::Company &company);
    void receiveLine(const PublicTransportation::Line &line);
    void receiveJourney(const PublicTransportation::Journey &journey);
    void receiveStation(const PublicTransportation::Station &station);
    void receiveWaitingTime(const PublicTransportation::WaitingTime &waitingTime);
    void receiveLineJourneys(const PublicTransportation::LineJourneys &lineJourneys);
private:
    PublicTransportation::Company m_company;
    PublicTransportation::Line m_line;
    PublicTransportation::Journey m_journey;
    PublicTransportation::Station m_station;
    PublicTransportation::WaitingTime m_waitingTime;
    PublicTransportation::LineJourneys m_lineJourneys;

};

#endif // DBUSOBJECT_H

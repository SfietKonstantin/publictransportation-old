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

#ifndef PUBLICTRANSPORTATION_INFOJOURNEYWAITINGTIME_H
#define PUBLICTRANSPORTATION_INFOJOURNEYWAITINGTIME_H

/**
 * @file infojourneywaitingtime.h
 * @short Definition of PublicTransportation::InfoJourneyWaitingTime
 */

#include "publictransportation_global.h"

#include <QtCore/QExplicitlySharedDataPointer>

#include "company.h"
#include "line.h"
#include "journey.h"
#include "station.h"
#include "waitingtime.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::InfoJourneyWaitingTime
 *
 * This class is used to store the explicitly shared
 * data for PublicTransportation::InfoJourneyWaitingTime.
 */
class InfoJourneyWaitingTimePrivate: public QSharedData
{
public:
    /**
     * @internal
     * @brief Company
     */
    Company company;
    /**
     * @internal
     * @brief Line
     */
    Line line;
    /**
     * @internal
     * @brief Journey
     */
    Journey journey;
    /**
     * @internal
     * @brief Station
     */
    Station station;
    /**
     * @internal
     * @brief Waiting time
     */
    WaitingTime waitingTime;
};


/**
 * @brief Class to provide informations about journeys and waiting times
 *
 * This class is used to provide informations related to journeys and
 * waiting times. For some backends, it might be better to provide
 * a list of entries, containing both a company, a line, a single journey
 * and a waiting time for this journey. This class is used to provide
 * those informations. Moreover, a station can be provided in order to
 * give more informations, (like some id, that are specific to the
 * station on the journey).
 *
 * Properties for an information about journeys and waiting times are then
 * - company()
 * - line()
 * - journey()
 * - station()
 * - waitingTime()
 *
 * and can be set using
 * - setCompany()
 * - setLine()
 * - setJourney()
 * - setStation()
 * - setWaitingTime()
 *
 * This class is an explicitely shared class, that means that
 * any copy of this class refers to the same instance, and
 * changing one copy will change all the others.
 */
class PUBLICTRANSPORTATION_EXPORT InfoJourneyWaitingTime
{
public:
    /**
     * @brief Default constructor
     */
    explicit InfoJourneyWaitingTime();
    /**
     * @brief Constructor
     * @param company company.
     * @param line line.
     * @param journey journey.
     * @param station station.
     * @param waitingTime waiting time.
     */
    explicit InfoJourneyWaitingTime(const Company &company, const Line &line,
                                    const Journey &journey, const Station &station,
                                    const WaitingTime &waitingTime);
    /**
     * @brief Copy constructor
     * @param other other information about journey object.
     */
    InfoJourneyWaitingTime(const InfoJourneyWaitingTime &other);
    /**
     * @brief Destructor
     */
    virtual ~InfoJourneyWaitingTime();
    /**
     * @brief Equality
     * @param other information about journey to compare to.
     * @return if the two information about journey are equal.
     */
    bool operator==(const InfoJourneyWaitingTime &other) const;
    /**
     * @brief If the information about journey is null
     * @return if the information about journey is null.
     */
    bool isNull() const;
    /**
     * @brief Company
     * @return company.
     */
    Company company() const;
    /**
     * @brief Set the company
     * @param company company to set.
     */
    void setCompany(const Company &company);
    /**
     * @brief Line
     * @return line.
     */
    Line line() const;
    /**
     * @brief Set the line
     * @param line line to set.
     */
    void setLine(const Line &line);
    /**
     * @brief Journey
     * @return journey.
     */
    Journey journey() const;
    /**
     * @brief Set the journey
     * @param journey journey to set.
     */
    void setJourney(const Journey &journey);
    /**
     * @brief Station
     * @return station.
     */
    Station station() const;
    /**
     * @brief Set the station
     * @param station station to set.
     */
    void setStation(const Station &station);
    /**
     * @brief Waiting time
     * @return waiting time.
     */
    WaitingTime waitingTime() const;
    /**
     * @brief Set the waiting time
     * @param waitingTime waiting time to set.
     */
    void setWaitingTime(const WaitingTime &waitingTime);
protected:
    /**
     * @brief D-pointer
     */
    QExplicitlySharedDataPointer<InfoJourneyWaitingTimePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(InfoJourneyWaitingTime)
};

}

Q_DECLARE_METATYPE(PublicTransportation::InfoJourneyWaitingTime)
Q_DECLARE_METATYPE(QList<PublicTransportation::InfoJourneyWaitingTime>)

#endif // PUBLICTRANSPORTATION_INFOJOURNEYWAITINGTIME_H

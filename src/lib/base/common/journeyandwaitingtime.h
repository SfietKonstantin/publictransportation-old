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

#ifndef PUBLICTRANSPORTATION_JOURNEYANDWAITINGTIME_H
#define PUBLICTRANSPORTATION_JOURNEYANDWAITINGTIME_H

/**
 * @file journeyandwaitingtime.h
 * @short Definition of PublicTransportation::JourneyAndWaitingTime
 */

#include "publictransportation_global.h"

#include <QtCore/QExplicitlySharedDataPointer>

#include "journey.h"
#include "waitingtime.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::JourneyAndWaitingTime
 *
 * This class is used to store the explicitly shared
 * data for PublicTransportation::JourneyAndWaitingTime.
 */
class JourneyAndWaitingTimePrivate: public QSharedData
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
    WaitingTime waitingTime;
};


/**
 * @brief Class to provide a waiting time for a given journey
 *
 * This class is used to provide a information about a waiting time
 * by providing the journey on which the waiting time is set.
 *
 * Properties for this class are then
 * - journey()
 * - waitingTime()
 *
 * and can be set using
 * - setJourney()
 * - setWaitingTime()
 *
 * This class is an explicitely shared class, that means that
 * any copy of this class refers to the same instance, and
 * changing one copy will change all the others.
 */
class PUBLICTRANSPORTATION_EXPORT JourneyAndWaitingTime
{
public:
    /**
     * @brief Default constructor
     */
    explicit JourneyAndWaitingTime();
    /**
     * @brief Constructor
     * @param journey journey.
     * @param waitingTime waiting time.
     */
    explicit JourneyAndWaitingTime(const Journey &journey, const WaitingTime &waitingTime);
    /**
     * @brief Copy constructor
     * @param other other journey and waiting time object.
     */
    JourneyAndWaitingTime(const JourneyAndWaitingTime &other);
    /**
     * @brief Destructor
     */
    virtual ~JourneyAndWaitingTime();
    /**
     * @brief Equality
     * @param other journey and waiting time to compare to.
     * @return if the two journey and waiting time are equal.
     */
    bool operator==(const JourneyAndWaitingTime &other) const;
    /**
     * @brief If the journey and waiting time is null
     * @return if the journey and waiting time is null.
     */
    bool isNull() const;
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
    QExplicitlySharedDataPointer<JourneyAndWaitingTimePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(JourneyAndWaitingTime)
};

}

Q_DECLARE_METATYPE(PublicTransportation::JourneyAndWaitingTime)
Q_DECLARE_METATYPE(QList<PublicTransportation::JourneyAndWaitingTime>)

#endif // PUBLICTRANSPORTATION_JOURNEYANDWAITINGTIME_H

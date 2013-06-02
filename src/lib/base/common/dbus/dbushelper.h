/*
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * The names of its contributors may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */
#ifndef PT2_DBUSHELPER_H
#define PT2_DBUSHELPER_H

/**
 * @file dbushelper.h
 * @short Definition of helper functions used by DBus interface
 */

#include <QtCore/QList>
//#include <QtCore/QPair>
#include <QtCore/QMetaType>

//#include "common/ride.h"
//#include "common/station.h"

class QDBusArgument;

namespace PT2
{

class Object;
class Company;
class Line;
class Ride;
class Station;
//class WaitingTime;
//class InfoJourneys;
//class JourneyAndWaitingTime;
//class InfoJourneyWaitingTime;



/**
 * @brief A pair with a journey and a station
 */
//typedef QPair<Journey, Station> JourneyAndStation;
/**
 * @brief Marshall a transportation object to a DBus argument
 *
 * This method is used to marshall a transportation object
 * to a DBus argument, making it transportable through DBus.
 *
 * A transportation object is marshalled as (sa{sv}sa{sv}), where
 * the first string contains the identifier, the first map contains
 * the internal parametrs, the second string contains the name,
 * and the second variant map contains the properties.
 *
 * @param[out] argument DBus argument.
 * @param[in] object transportation object.
 * @return DBus argument containing the transportation object.
 */
QDBusArgument & objectToDBus(QDBusArgument &argument, const Object &object);
/**
 * @brief Demarshall a transportation object from a DBus argument
 *
 * This method is used to demarshall a transportation object
 * from a DBus argument.
 *
 * A transportation object is marshalled as (sa{sv}sa{sv}), where
 * the first string contains the identifier, the first map contains
 * the internal parametrs, the second string contains the name,
 * and the second variant map contains the properties.
 *
 * @param[in] argument DBus argument.
 * @param[out] object transportation object.
 * @return DBus argument without the transportation object.
 */
const QDBusArgument & objectFromDBus(const QDBusArgument &argument, Object &object);

/**
 * @brief Marshall a company
 * @param[out] argument DBus argument.
 * @param[in] company company.
 * @return DBus argument containing the company.
 */
QDBusArgument & operator<<(QDBusArgument &argument, const Company &company);
/**
 * @brief Demarshall a company
 * @param[in] argument DBus argument.
 * @param[out] company company.
 * @return DBus argument without the company.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument, Company &company);
/**
 * @brief Marshall a line
 * @param[out] argument DBus argument.
 * @param[in] line line.
 * @return DBus argument containing the line.
 */
QDBusArgument & operator<<(QDBusArgument &argument, const Line &line);
/**
 * @brief Demarshall a line
 * @param[in] argument DBus argument.
 * @param[out] line line.
 * @return DBus argument without the line.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument, Line &line);
/**
 * @brief Marshall a ride
 * @param[out] argument DBus argument.
 * @param[in] ride ride.
 * @return DBus argument containing the ride.
 */
QDBusArgument & operator<<(QDBusArgument &argument, const Ride &ride);
/**
 * @brief Demarshall a ride
 * @param[in] argument DBus argument.
 * @param[out] ride ride.
 * @return DBus argument without the ride.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument, Ride &ride);
/**
 * @brief Marshall a station
 * @param[out] argument DBus argument.
 * @param[in] station station.
 * @return DBus argument containing the station.
 */
QDBusArgument & operator<<(QDBusArgument &argument, const Station &station);
/**
 * @brief Demarshall a station
 * @param[in] argument DBus argument.
 * @param[out] station station.
 * @return DBus argument without the station.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument, Station &station);
/**
 * @brief Marshall a waiting time
 * @param[out] argument DBus argument.
 * @param[in] waitingTime waiting time.
 * @return DBus argument containing the waiting thme.
 */
//QDBusArgument & operator<<(QDBusArgument &argument, const WaitingTime &waitingTime);
/**
 * @brief Demarshall a waiting time
 * @param[in] argument DBus argument.
 * @param[out] waitingTime waiting time.
 * @return DBus argument without the waiting thme.
 */
//const QDBusArgument & operator>>(const QDBusArgument &argument, WaitingTime &waitingTime);
/**
 * @brief Marshall a journey and a station
 * @param[out] argument DBus argument.
 * @param[in] journeyAndStation a journey and a station.
 * @return DBus argument containing the journey and station.
 */
//QDBusArgument & operator<<(QDBusArgument &argument, const JourneyAndStation &journeyAndStation);
/**
 * @brief Demarshall a journey and a station
 * @param[in] argument DBus argument.
 * @param[out] journeyAndStation a journey and a station.
 * @return DBus argument without the journey and station.
 */
//const QDBusArgument & operator>>(const QDBusArgument &argument,
//                                 JourneyAndStation &journeyAndStation);
/**
 * @brief Marshall an informations about journeys
 * @param[out] argument DBus argument.
 * @param[in] infoJourneys an informations about journeys.
 * @return DBus argument containing the informations about journeys.
 */
//QDBusArgument & operator<<(QDBusArgument &argument, const InfoJourneys &infoJourneys);
/**
 * @brief Demarshall an informations about journeys
 * @param[out] argument DBus argument.
 * @param[in] infoJourneys an informations about journeys.
 * @return DBus argument without the informations about journeys.
 */
//const QDBusArgument & operator>>(const QDBusArgument &argument, InfoJourneys &infoJourneys);
/**
 * @brief Marshall a journey and waiting time
 * @param[out] argument DBus argument.
 * @param[in] journeyAndWaitingTime a journey and waiting time.
 * @return DBus argument containing the journey and waiting time.
 */
//QDBusArgument & operator<<(QDBusArgument &argument,
//                           const JourneyAndWaitingTime &journeyAndWaitingTime);
/**
 * @brief Demarshall a journey and waiting time
 * @param[out] argument DBus argument.
 * @param[in] journeyAndWaitingTime a journey and waiting time.
 * @return DBus argument without the journey and waiting time.
 */
//const QDBusArgument & operator>>(const QDBusArgument &argument,
//                                 JourneyAndWaitingTime &journeyAndWaitingTime);
/**
 * @brief Marshall an informations about journeys
 * @param[out] argument DBus argument.
 * @param[in] infoJourneyWaitingTime an informations about journey and waiting time.
 * @return DBus argument containing the informations about journey and waiting time.
 */
//QDBusArgument & operator<<(QDBusArgument &argument,
//                           const InfoJourneyWaitingTime &infoJourneyWaitingTime);
/**
 * @brief Demarshall an informations about journeys
 * @param[out] argument DBus argument.
 * @param[in] infoJourneyWaitingTime an informations about journey and waiting time.
 * @return DBus argument without the informations about journey and waiting time.
 */
//const QDBusArgument & operator>>(const QDBusArgument &argument,
//                                 InfoJourneyWaitingTime &infoJourneyWaitingTime);

/**
 * @brief Register DBus types
 *
 * This method is used to register complex types to the
 * DBus type system. This method should be called before
 * making any DBus call involving these complex types.
 */
void registerDBusTypes();

}

//Q_DECLARE_METATYPE(PublicTransportation::JourneyAndStation)
//Q_DECLARE_METATYPE(QList<PublicTransportation::JourneyAndStation>)

#endif // PT2_DBUSHELPER_H

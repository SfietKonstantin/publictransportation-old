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

#ifndef PUBLICTRANSPORTATION_DBUSHELPER_H
#define PUBLICTRANSPORTATION_DBUSHELPER_H

/**
 * @file dbushelper.h
 * @short Definition of helper functions used by DBus interface
 */

#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QMetaType>

#include "common/journey.h"
#include "common/station.h"

class QDBusArgument;

namespace PublicTransportation
{

class TransportationObject;
class Company;
class Line;
class WaitingTime;
class InfoJourneys;
class JourneyAndWaitingTime;
class InfoJourneyWaitingTime;



/**
 * @brief A pair with a journey and a station
 */
typedef QPair<Journey, Station> JourneyAndStation;
/**
 * @brief Marshall a transportation object to a DBus argument
 *
 * This method is used to marshall a transportation object
 * to a DBus argument, making it transportable through DBus.
 *
 * A transportation object is marshalled as (a{sv}sa{sv}), where
 * the first map contains the disambiguation parametrs, the string
 * contains the name, and the second variant map contains the
 * properties.
 *
 * @param[out] argument DBus argument.
 * @param[in] transportationObject transportation object.
 * @return DBus argument containing the transportation object.
 */
QDBusArgument & transportationObjectToDBus(QDBusArgument &argument,
                                           const TransportationObject &transportationObject);
/**
 * @brief Demarshall a transportation object from a DBus argument
 *
 * This method is used to demarshall a transportation object
 * from a DBus argument.
 *
 * A transportation object is demarshalled from (a{sv}sa{sv}), where
 * the first map contains the disambiguation parametrs, the string
 * contains the name, and the second variant map contains the
 * properties.
 *
 * @param[in] argument DBus argument.
 * @param[out] transportationObject transportation object.
 * @return DBus argument without the transportation object.
 */
const QDBusArgument & transportationObjectFromDBus(const QDBusArgument &argument,
                                                   TransportationObject &transportationObject);

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
 * @brief Marshall a journey
 * @param[out] argument DBus argument.
 * @param[in] journey journey.
 * @return DBus argument containing the journey.
 */
QDBusArgument & operator<<(QDBusArgument &argument, const Journey &journey);
/**
 * @brief Demarshall a journey
 * @param[in] argument DBus argument.
 * @param[out] journey journey.
 * @return DBus argument without the journey.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument, Journey &journey);
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
QDBusArgument & operator<<(QDBusArgument &argument, const WaitingTime &waitingTime);
/**
 * @brief Demarshall a waiting time
 * @param[in] argument DBus argument.
 * @param[out] waitingTime waiting time.
 * @return DBus argument without the waiting thme.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument, WaitingTime &waitingTime);
/**
 * @brief Marshall a journey and a station
 * @param[out] argument DBus argument.
 * @param[in] journeyAndStation a journey and a station.
 * @return DBus argument containing the journey and station.
 */
QDBusArgument & operator<<(QDBusArgument &argument, const JourneyAndStation &journeyAndStation);
/**
 * @brief Demarshall a journey and a station
 * @param[in] argument DBus argument.
 * @param[out] journeyAndStation a journey and a station.
 * @return DBus argument without the journey and station.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument,
                                 JourneyAndStation &journeyAndStation);
/**
 * @brief Marshall an informations about journeys
 * @param[out] argument DBus argument.
 * @param[in] infoJourneys an informations about journeys.
 * @return DBus argument containing the informations about journeys.
 */
QDBusArgument & operator<<(QDBusArgument &argument, const InfoJourneys &infoJourneys);
/**
 * @brief Demarshall an informations about journeys
 * @param[out] argument DBus argument.
 * @param[in] infoJourneys an informations about journeys.
 * @return DBus argument without the informations about journeys.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument, InfoJourneys &infoJourneys);
/**
 * @brief Marshall a journey and waiting time
 * @param[out] argument DBus argument.
 * @param[in] journeyAndWaitingTime a journey and waiting time.
 * @return DBus argument containing the journey and waiting time.
 */
QDBusArgument & operator<<(QDBusArgument &argument,
                           const JourneyAndWaitingTime &journeyAndWaitingTime);
/**
 * @brief Demarshall a journey and waiting time
 * @param[out] argument DBus argument.
 * @param[in] journeyAndWaitingTime a journey and waiting time.
 * @return DBus argument without the journey and waiting time.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument,
                                 JourneyAndWaitingTime &journeyAndWaitingTime);
/**
 * @brief Marshall an informations about journeys
 * @param[out] argument DBus argument.
 * @param[in] infoJourneyWaitingTime an informations about journey and waiting time.
 * @return DBus argument containing the informations about journey and waiting time.
 */
QDBusArgument & operator<<(QDBusArgument &argument,
                           const InfoJourneyWaitingTime &infoJourneyWaitingTime);
/**
 * @brief Demarshall an informations about journeys
 * @param[out] argument DBus argument.
 * @param[in] infoJourneyWaitingTime an informations about journey and waiting time.
 * @return DBus argument without the informations about journey and waiting time.
 */
const QDBusArgument & operator>>(const QDBusArgument &argument,
                                 InfoJourneyWaitingTime &infoJourneyWaitingTime);

/**
 * @brief Register DBus types
 *
 * This method is used to register complex types to the
 * DBus type system. This method should be called before
 * making any DBus call involving these complex types.
 */
void registerDBusTypes();

}

Q_DECLARE_METATYPE(PublicTransportation::JourneyAndStation)
Q_DECLARE_METATYPE(QList<PublicTransportation::JourneyAndStation>)

#endif // PUBLICTRANSPORTATION_DBUSHELPER_H

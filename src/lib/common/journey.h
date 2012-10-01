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

#ifndef PUBLICTRANSPORTATION_JOURNEY_H
#define PUBLICTRANSPORTATION_JOURNEY_H

/**
 * @file journey.h
 * @short Definition of PublicTransportation::Journey
 */

#include "publictransportation_global.h"
#include "transportationobject.h"
#include <QtCore/QVariantMap>

namespace PublicTransportation
{

class Line;
class Station;
class JourneyPrivate;

/**
 * @brief A public transportation journey
 *
 * This class is used to represent a public transportation
 * journey. A journey is a transportation entity that have a name,
 * that should be a descriptive, a disambiguation parameter,
 * a line on which the journey belongs, and some properties.
 *
 * %Line can be accessed and set using
 * - line()
 * - setLine()
 *
 * A journey also have stations. Those stations might vary during the life
 * of the instance for example for web providers that only provide
 * information for the incoming trains.
 *
 * In order to access and update the registered stations, those methods
 * can be used
 * - stations()
 * - addStation() that adds a station to the journey.
 * - removeStation() that remove a station from the journey.
 *
 * While creating journeys, the journey will also automatically
 * be attached to the line.
 *
 * Please note that when comparing two journeys, the stations that these
 * journeys stores are not compared.
 */
class PUBLICTRANSPORTATION_EXPORT Journey : public TransportationObject
{
public:
    /**
     * @brief Default constructor
     */
    explicit Journey();
    /**
     * @brief Constructor
     * @param disambiguation disambiguation.
     * @param name name.
     * @param line line.
     * @param properties properties.
     */
    explicit Journey(const QVariantMap &disambiguation, const QString &name,
                     const Line &line, const QVariantMap &properties);
    /**
     * @brief Destructor
     */
    virtual ~Journey();
    /**
     * @brief Line
     * @return line.
     */
    Line line() const;
    /**
     * @brief Set line
     * @param line line to set.
     */
    void setLine(const Line &line);
    /**
     * @brief Stations
     * @return stations.
     */
    QList<Station> stations() const;
    /**
     * @brief Add station
     * @param station station to add.
     */
    void addStation(const Station &station);
    /**
     * @brief Remove station
     * @param station station to remove.
     */
    void removeStation(const Station &station);
private:
    Q_DECLARE_PRIVATE(Journey)
};

}

Q_DECLARE_METATYPE(PublicTransportation::Journey)
Q_DECLARE_METATYPE(QList<PublicTransportation::Journey>)

#endif // PUBLICTRANSPORTATION_JOURNEY_H

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

#ifndef PUBLICTRANSPORTATION_INFOJOURNEYS_H
#define PUBLICTRANSPORTATION_INFOJOURNEYS_H

/**
 * @file infojourneys.h
 * @short Definition of PublicTransportation::InfoJourneys
 */

#include "publictransportation_global.h"

#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QExplicitlySharedDataPointer>

#include "company.h"
#include "line.h"
#include "journey.h"
#include "station.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::InfoJourneys
 *
 * This class is used to store the explicitly shared
 * data for PublicTransportation::InfoJourneys.
 */
class InfoJourneysPrivate: public QSharedData
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
     * @brief List of journeys and stations
     */
    QList<QPair<Journey, Station> > journeysStations;
};

/**
 * @brief Class to provide informations about journeys
 *
 * This class is used to provide informations related to journeys.
 * From a station, a list of journeys, associated to a given company,
 * on a given line. For each journey, a station is associated, in order
 * to provide more information (like some id, that are specific to the
 * station on the journey). This class then provide a list of
 * journey-station pairs.
 *
 * Properties for an information about journeys are then
 * - company()
 * - line()
 * - journeysAndStations()
 *
 * and can be set using
 * - setCompany()
 * - setLine()
 * - setJourneysAndStations()
 *
 * This class is an explicitely shared class, that means that
 * any copy of this class refers to the same instance, and
 * changing one copy will change all the others.
 */
class PUBLICTRANSPORTATION_EXPORT InfoJourneys
{
public:
    /**
     * @brief Default constructor
     */
    explicit InfoJourneys();
    /**
     * @brief Constructor
     * @param company company.
     * @param line line.
     * @param journeysStations journeys and stations.
     */
    explicit InfoJourneys(const Company &company, const Line &line,
                          const QList<QPair<Journey, Station> > &journeysStations);
    /**
     * @brief Copy constructor
     * @param other other information about journeys object.
     */
    InfoJourneys(const InfoJourneys &other);
    /**
     * @brief Destructor
     */
    virtual ~InfoJourneys();
    /**
     * @brief Equality
     * @param other information about journeys to compare to.
     * @return if the two information about journeys are equal.
     */
    bool operator==(const InfoJourneys &other) const;
    /**
     * @brief If the information about journeys is null
     * @return if the information about journeys is null.
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
     * @brief Journeys and stations
     * @return journeys and stations.
     */
    QList<QPair<Journey, Station> > journeysAndStations() const;
    /**
     * @brief Set journeys and stations
     * @param journeysStations journeys and stations to set.
     */
    void setJourneysAndStations(const QList<QPair<Journey, Station> > &journeysStations);
protected:
    /**
     * @brief D-pointer
     */
    QExplicitlySharedDataPointer<InfoJourneysPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(InfoJourneys)
};

}

Q_DECLARE_METATYPE(PublicTransportation::InfoJourneys)
Q_DECLARE_METATYPE(QList<PublicTransportation::InfoJourneys>)

#endif // PUBLICTRANSPORTATION_INFOJOURNEYS_H

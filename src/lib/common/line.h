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

#ifndef PUBLICTRANSPORTATION_LINE_H
#define PUBLICTRANSPORTATION_LINE_H

/**
 * @file line.h
 * @short Definition of PublicTransportation::Line
 */

#include "publictransportation_global.h"
#include "transportationobject.h"

namespace PublicTransportation
{

class Company;
class Journey;
class LinePrivate;

/**
 * @brief A public transportation line
 *
 * This class is used to represent a public transportation
 * line. A line is a transportation entity that
 * have a name, that should be the official name of the line,
 * a disambiguation parameter, a company on which the line
 * belongs, and other properties, such as the color of the
 * line, or the logo.
 *
 * %Company can be accessed and set using
 * - company()
 * - setCompany()
 *
 * A line also have journeys. Those journeys might vary during the life
 * of the instance for example for web providers that only provide
 * information for the incoming trains.
 *
 * In order to access and update the registered journeys, those methods
 * can be used
 * - journeys()
 * - addJourney() that adds a journey to the line.
 * - removeJourney() that remove a line from the line.
 *
 * While creating lines, the line will also automatically
 * be attached to the company.
 *
 * Please note that when comparing two lines, the journeys that these
 * lines stores are not compared.
 */
class PUBLICTRANSPORTATION_EXPORT Line: public TransportationObject
{
public:
    /**
     * @brief Default constructor
     */
    explicit Line();
    /**
     * @brief Constructor
     * @param disambiguation disambiguation.
     * @param name name.
     * @param company company.
     * @param properties properties.
     */
    explicit Line(const QVariantMap &disambiguation, const QString &name,
                  const Company &company, const QVariantMap &properties);
    /**
     * @brief Destructor
     */
    virtual ~Line();
    /**
     * @brief Company
     * @return company.
     */
    Company company() const;
    /**
     * @brief Set company
     * @param company company to set.
     */
    void setCompany(const Company &company);
    /**
     * @brief Journeys
     * @return journeys.
     */
    QList<Journey> journeys() const;
    /**
     * @brief Add journey
     * @param journey journey to add.
     */
    void addJourney(const Journey &journey);
    /**
     * @brief Remove journey
     * @param journey journey to remove.
     */
    void removeJourney(const Journey &journey);
private:
    Q_DECLARE_PRIVATE(Line)
};

}

Q_DECLARE_METATYPE(PublicTransportation::Line)
Q_DECLARE_METATYPE(QList<PublicTransportation::Line>)

#endif // PUBLICTRANSPORTATION_LINE_H

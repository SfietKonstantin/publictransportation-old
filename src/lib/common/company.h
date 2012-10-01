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

#ifndef PUBLICTRANSPORTATION_COMPANY_H
#define PUBLICTRANSPORTATION_COMPANY_H

/**
 * @file company.h
 * @short Definition of PublicTransportation::Company
 */

#include "publictransportation_global.h"
#include "transportationobject.h"

namespace PublicTransportation
{

class Line;
class CompanyPrivate;
/**
 * @brief A public transportation company
 *
 * This class is used to represent a public transportation
 * company. A company is a transportation entity that
 * have a name, that is the official name of the company,
 * a disambiguation parameter, and other properties, including
 * a copyright, that can be used to provide copyright information.
 *
 * Copyright can be accessed and set using
 * - copyright()
 * - setCopyright()
 *
 * It is also stored in the properties of the company.
 *
 * A company also have transportation lines. Those transportation
 * lines might vary during the life of the instance for example for
 * web providers that only provide information for the incoming trains.
 *
 * In order to access and update the registered lines, those methods
 * can be used
 * - lines()
 * - addLine() that adds a line to the company.
 * - removeLine() that remove a line from the company.
 *
 * Please note that when comparing two companies, the lines that these
 * companies stores are not compared.
 */
class PUBLICTRANSPORTATION_EXPORT Company: public TransportationObject
{
public:
    /**
     * @brief Default constructor
     */
    explicit Company();
    /**
     * @brief Constructor
     * @param disambiguation disambiguation.
     * @param name name.
     * @param copyright copyright.
     * @param properties properties.
     */
    explicit Company(const QVariantMap &disambiguation, const QString &name,
                     const QString &copyright, const QVariantMap &properties);
    /**
     * @brief Destructor
     */
    virtual ~Company();
    /**
     * @brief Copyright
     * @return copyrignt.
     */
    QString copyright() const;
    /**
     * @brief Set copyright
     * @param copyright copyright to set.
     */
    void setCopyright(const QString &copyright);
    /**
     * @brief Lines
     * @return lines.
     */
    QList<Line> lines() const;
//    void setLines(const QList<Line> &lines);
    /**
     * @brief Add line
     * @param line line to add.
     */
    void addLine(const Line &line);
    /**
     * @brief Remove line
     * @param line line to remove.
     */
    void removeLine(const Line &line);
private:
    Q_DECLARE_PRIVATE(Company)
};

}

Q_DECLARE_METATYPE(PublicTransportation::Company)
Q_DECLARE_METATYPE(QList<PublicTransportation::Company>)

#endif // PUBLICTRANSPORTATION_COMPANY_H

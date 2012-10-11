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

/**
 * @brief A public transportation company
 *
 * This class is used to represent a public transportation
 * company. A company is a transportation entity that
 * have a name, that is the official name of the company,
 * a disambiguation parameter, and other properties.
 *
 * It is also stored in the properties of the company.
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
     * @param properties properties.
     */
    explicit Company(const QVariantMap &disambiguation, const QString &name,
                     const QVariantMap &properties);
private:
    Q_DECLARE_PRIVATE(TransportationObject)
};

}

Q_DECLARE_METATYPE(PublicTransportation::Company)
Q_DECLARE_METATYPE(QList<PublicTransportation::Company>)

#endif // PUBLICTRANSPORTATION_COMPANY_H

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

namespace PublicTransportation
{

/**
 * @brief A public transportation journey
 *
 * This class is used to represent a public transportation
 * journey. A journey is a transportation entity that have a name,
 * that should be a descriptive, a disambiguation parameter,
 * and some properties.
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
     * @param properties properties.
     */
    explicit Journey(const QVariantMap &disambiguation, const QString &name,
                     const QVariantMap &properties);
private:
    Q_DECLARE_PRIVATE(TransportationObject)
};

}

Q_DECLARE_METATYPE(PublicTransportation::Journey)
Q_DECLARE_METATYPE(QList<PublicTransportation::Journey>)

#endif // PUBLICTRANSPORTATION_JOURNEY_H

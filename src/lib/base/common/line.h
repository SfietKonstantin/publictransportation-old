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

/**
 * @brief A public transportation line
 *
 * This class is used to represent a public transportation
 * line. A line is a transportation entity that
 * have a name, that should be the official name of the line,
 * a disambiguation parameter, and other properties, such as
 * the color of the line, or the logo.
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
     * @param properties properties.
     */
    explicit Line(const QVariantMap &disambiguation, const QString &name,
                  const QVariantMap &properties);
private:
    Q_DECLARE_PRIVATE(TransportationObject)
};

}

Q_DECLARE_METATYPE(PublicTransportation::Line)
Q_DECLARE_METATYPE(QList<PublicTransportation::Line>)

#endif // PUBLICTRANSPORTATION_LINE_H

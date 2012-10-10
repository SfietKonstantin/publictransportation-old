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

/**
 * @file station.cpp
 * @short Implementation of PublicTransportation::Station
 */

#include "station.h"

namespace PublicTransportation
{

Station::Station() :
    TransportationObject()
{
}

Station::Station(const QVariantMap &disambiguation, const QString &name,
                 const QVariantMap &properties):
    TransportationObject()
{
    Q_D(TransportationObject);
    d->disambiguation = disambiguation;
    d->name = name;
    d->properties = properties;
}

}

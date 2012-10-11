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
 * @file transportationobject.cpp
 * @short Implementation of PublicTransportation::TransportationObject
 */

#include "transportationobject.h"

namespace PublicTransportation
{

TransportationObject::TransportationObject():
    d_ptr(new TransportationObjectPrivate)
{
}

TransportationObject::TransportationObject(const TransportationObject &other):
    d_ptr(other.d_ptr)
{
}

TransportationObject::TransportationObject(TransportationObjectPrivate &dd):
    d_ptr(&dd)
{
}

TransportationObject::~TransportationObject()
{
}

bool TransportationObject::operator==(const TransportationObject &other) const
{
    Q_D(const TransportationObject);
    return (d->name == other.name()) && (d->disambiguation == other.disambiguation());
}

bool TransportationObject::operator<(const TransportationObject &other) const
{
    Q_D(const TransportationObject);
    return (d->name < other.name());
}

bool TransportationObject::isNull() const
{
    Q_D(const TransportationObject);
    return (d->disambiguation.isEmpty() && d->name.isNull() && d->properties.isEmpty());
}

QString TransportationObject::name() const
{
    Q_D(const TransportationObject);
    return d->name;
}

void TransportationObject::setName(const QString &name)
{
    Q_D(TransportationObject);
    d->name = name;
}

QVariantMap TransportationObject::disambiguation() const
{
    Q_D(const TransportationObject);
    return d->disambiguation;
}

void TransportationObject::setDisambiguation(const QVariantMap &disambiguation)
{
    Q_D(TransportationObject);
    d->disambiguation = disambiguation;
}

QVariantMap TransportationObject::properties() const
{
    Q_D(const TransportationObject);
    return d->properties;
}

void TransportationObject::setProperties(const QVariantMap &properties)
{
    Q_D(TransportationObject);
    d->properties = properties;
}

}

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
 * @file company.cpp
 * @short Implementation of PublicTransportation::Company
 */

#include "company.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief COPYRIGHT_KEY
 *
 * Used in PublicTransportation::Company.
 */
static const char *COPYRIGHT_KEY = "copyright";

Company::Company():
    TransportationObject()
{
}

Company::Company(const QVariantMap &disambiguation, const QString &name,
                 const QString &copyright, const QVariantMap &properties):
    TransportationObject()
{
    Q_D(TransportationObject);
    d->disambiguation = disambiguation;
    d->name = name;
    d->properties = properties;
    d->properties.insert(COPYRIGHT_KEY, copyright);
}

Company::~Company()
{
}

QString Company::copyright() const
{
    Q_D(const TransportationObject);
    return d->properties.value(COPYRIGHT_KEY).toString();
}

void Company::setCopyright(const QString &copyright)
{
    Q_D(TransportationObject);
    d->properties.insert(COPYRIGHT_KEY, copyright);
}

}

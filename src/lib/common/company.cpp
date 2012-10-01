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

#include <QtCore/QDebug>
#include <QtCore/QList>

#include "line.h"

namespace PublicTransportation
{

/**
 * @brief COPYRIGHT_KEY
 *
 * Used in PublicTransportation::Company.
 */
static const char *COPYRIGHT_KEY = "copyright";


/**
 * @internal
 * @brief Private class for PublicTransportation::Company
 */
class CompanyPrivate: public TransportationObjectPrivate
{
public:
    /**
     * @internal Lines
     * @brief lines
     */
    QList<Line> lines;
};

////// End of private class //////

Company::Company():
    TransportationObject(*new CompanyPrivate)
{
}

Company::Company(const QVariantMap &disambiguation, const QString &name,
                 const QString &copyright, const QVariantMap &properties):
    TransportationObject(*new CompanyPrivate)
{
    Q_D(Company);
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
    Q_D(const Company);
    return d->properties.value(COPYRIGHT_KEY).toString();
}

void Company::setCopyright(const QString &copyright)
{
    Q_D(Company);
    d->properties.insert(COPYRIGHT_KEY, copyright);
}

QList<Line> Company::lines() const
{
    Q_D(const Company);
    return d->lines;
}

void Company::addLine(const Line &line)
{
    Q_D(Company);
    if (d->lines.contains(line)) {
        return;
    }

    d->lines.append(line);
}

void Company::removeLine(const Line &line)
{
    Q_D(Company);
    if (!d->lines.contains(line)) {
        return;
    }

    d->lines.removeAll(line);
}

}

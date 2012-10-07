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

#include "transportlausannois.h"

#include <QtCore/QtPlugin>

#include "common/capabilitiesconstants.h"
#include "common/company.h"

#include "tllist.h"

namespace PublicTransportation
{

namespace Provider
{

class TransportLausannoisPrivate
{
public:
    QList<Company> companies;
};

////// End of private class //////

TransportLausannois::TransportLausannois(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new TransportLausannoisPrivate)
{
    Q_D(TransportLausannois);
    Company tl (QVariantMap(), "tl", QString(), QVariantMap());
    d->companies.append(tl);
}

TransportLausannois::~TransportLausannois()
{
}

QStringList TransportLausannois::capabilities() const
{
    QStringList capabilities;
    capabilities.append(CAPABILITY_LIST_COMPANIES);
    capabilities.append(CAPABILITY_LIST_LINES);
    capabilities.append(CAPABILITY_LIST_JOURNEYS);
    capabilities.append(CAPABILITY_LIST_STATIONS);
    return capabilities;
}

QList<Company> TransportLausannois::listCompanies() const
{
    Q_D(const TransportLausannois);
    return d->companies;
}

QList<Line> TransportLausannois::listLines(const Company &company) const
{
    Q_UNUSED(company)
    return TlList::lines();
}

QList<Journey> TransportLausannois::listJourneys(const Company &company, const Line &line) const
{
    Q_UNUSED(company)
    return TlList::journeys(line);
}

QList<Station> TransportLausannois::listStations(const Company &company, const Line &line,
                                             const Journey &journey) const
{
    Q_UNUSED(company)
    return TlList::stations(line, journey);
}

}

}

Q_EXPORT_PLUGIN2(tl, PublicTransportation::Provider::TransportLausannois)

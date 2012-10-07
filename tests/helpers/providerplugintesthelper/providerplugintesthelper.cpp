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

#include "providerplugintesthelper.h"

#include <QtCore/QtPlugin>

#include "common/capabilitiesconstants.h"
#include "common/company.h"

namespace PublicTransportation
{


ProviderPluginTestHelper::ProviderPluginTestHelper(QObject *parent) :
    ProviderPluginObject(parent)
{

}

ProviderPluginTestHelper::~ProviderPluginTestHelper()
{
}

QStringList ProviderPluginTestHelper::capabilities() const
{
    QStringList capabilities;
    capabilities.append(CAPABILITY_LIST_COMPANIES);
    capabilities.append(CAPABILITY_LIST_LINES);
    capabilities.append(CAPABILITY_LIST_JOURNEYS);
    capabilities.append(CAPABILITY_LIST_STATIONS);
    return capabilities;
}

QList<Company> ProviderPluginTestHelper::listCompanies() const
{
    QVariantMap disambiguation;
    disambiguation.insert("test1", 12345);
    disambiguation.insert("test2", "abcde");

    QVariantMap properties;
    properties.insert("property1", 67890);
    properties.insert("property2", "fghij");

    Company company (disambiguation, "testCompany", "some copyright", properties);
    QList<Company> companies;
    companies.append(company);

    return companies;
}

QList<Line> ProviderPluginTestHelper::listLines(const Company &company) const
{
    Q_UNUSED(company)

    QVariantMap disambiguation;
    disambiguation.insert("test1", 12345);
    disambiguation.insert("test2", "abcde");

    QVariantMap properties;
    properties.insert("property1", 67890);
    properties.insert("property2", "fghij");

    Line line (disambiguation, "testLine", Company(), properties);
    QList<Line> lines;
    lines.append(line);

    return lines;
}

QList<Journey> ProviderPluginTestHelper::listJourneys(const Company &company,
                                                      const Line &line) const
{
    Q_UNUSED(company)
    Q_UNUSED(line)

    QVariantMap disambiguation;
    disambiguation.insert("test1", 12345);
    disambiguation.insert("test2", "abcde");

    QVariantMap properties;
    properties.insert("property1", 67890);
    properties.insert("property2", "fghij");

    Journey journey (disambiguation, "testJourney", Line(), properties);
    QList<Journey> journeys;
    journeys.append(journey);

    return journeys;
}

QList<Station> ProviderPluginTestHelper::listStations(const Company &company, const Line &line,
                                             const Journey &journey) const
{
    Q_UNUSED(company)
    Q_UNUSED(line)
    Q_UNUSED(journey)

    QVariantMap disambiguation;
    disambiguation.insert("test1", 12345);
    disambiguation.insert("test2", "abcde");

    QVariantMap properties;
    properties.insert("property1", 67890);
    properties.insert("property2", "fghij");

    Station station (disambiguation, "testStation", Journey(), properties);
    QList<Station> stations;
    stations.append(station);

    return stations;
}

}

Q_EXPORT_PLUGIN2(providerplugintesthelper, PublicTransportation::ProviderPluginTestHelper)

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

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtDBus/QDBusInterface>

#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/capabilitiesconstants.h"
#include "common/dbus/dbusconstants.h"
#include "common/dbus/dbushelper.h"

int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);
    Q_UNUSED(app)

    PublicTransportation::registerDBusTypes();

    QStringList arguments = app.arguments();
    if (arguments.count() < 3) {
        return 1;
    }

    if (arguments.at(1) != "--identifier") {
        return 2;
    }

    QString identifier = arguments.at(2);

    QDBusInterface interface (DBUS_SERVICE, QString("/backend/") + identifier);
    QStringList capabilities;
    capabilities.append(CAPABILITY_LIST_COMPANIES);
    capabilities.append(CAPABILITY_LIST_LINES);
    capabilities.append(CAPABILITY_LIST_JOURNEYS);
    capabilities.append(CAPABILITY_LIST_STATIONS);
    capabilities.append(CAPABILITY_REAL_TIME);

    interface.call("registerBackend", capabilities);

    QVariantMap disambiguation;
    disambiguation.insert("test1", 12345);
    disambiguation.insert("test2", "abcde");

    QVariantMap properties;
    properties.insert("property1", 67890);
    properties.insert("property2", "fghij");

    PublicTransportation::Company company (disambiguation, "testCompany", "some copyright",
                                           properties);
    QList<PublicTransportation::Company> companies;
    companies.append(company);

    interface.call("registerListedCompanies", QVariant::fromValue(companies));

    PublicTransportation::Line line (disambiguation, "testLine", company, properties);
    QList<PublicTransportation::Line> lines;
    lines.append(line);

    interface.call("registerListedLines", QVariant::fromValue(company), QVariant::fromValue(lines));

    PublicTransportation::Journey journey (disambiguation, "testJourney", line, properties);
    QList<PublicTransportation::Journey> journeys;
    journeys.append(journey);

    interface.call("registerListedJourneys", QVariant::fromValue(company),
                   QVariant::fromValue(line),
                   QVariant::fromValue(journeys));

    PublicTransportation::Station station (disambiguation, "testStation", journey, properties);
    QList<PublicTransportation::Station> stations;
    stations.append(station);

    interface.call("registerListedStations", QVariant::fromValue(company),
                   QVariant::fromValue(line), QVariant::fromValue(journey),
                   QVariant::fromValue(stations));
}

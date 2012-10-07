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
#include <QtDBus/QDBusInterface>

#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/dbus/dbusconstants.h"
#include "common/dbus/dbushelper.h"

int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);
    Q_UNUSED(app)

    PublicTransportation::registerDBusTypes();


    QVariantMap disambiguation;
    disambiguation.insert("test1", 12345);
    disambiguation.insert("test2", "abcde");

    QVariantMap properties;
    properties.insert("property1", 67890);
    properties.insert("property2", "fghij");
    PublicTransportation::Company company (disambiguation, "testCompany", "some copyright",
                                           properties);

    QDBusInterface interface (DBUS_SERVICE, "/");
    interface.call("receiveCompany", QVariant::fromValue(company));

    PublicTransportation::Line line (disambiguation, "testLine", company, properties);
    interface.call("receiveLine", QVariant::fromValue(line));

    PublicTransportation::Journey journey (disambiguation, "testJourney", line, properties);
    interface.call("receiveJourney", QVariant::fromValue(journey));

    PublicTransportation::Station station (disambiguation, "testStation", journey, properties);
    interface.call("receiveStation", QVariant::fromValue(station));
}

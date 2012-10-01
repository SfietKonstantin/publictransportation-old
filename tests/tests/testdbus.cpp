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

#include "testdbus.h"

#include <QtCore/QProcess>
#include <QtDBus/QDBusConnection>
#include <QtTest/QTest>

#include "dbusobject.h"
#include "common/dbus/dbushelper.h"
#include "common/dbus/dbusconstants.h"



void TestDBus::testSimpleReceive()
{
    PublicTransportation::registerDBusTypes();

    DBusObject *dbusObject = new DBusObject(this);
    QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
    QDBusConnection::sessionBus().registerObject("/", dbusObject,
                                                 QDBusConnection::ExportAllContents);

    QProcess *helperProcess = new QProcess(this);
    helperProcess->startDetached(QString(HELPER_FOLDER) + "/dbustesthelper");
    QTest::qWait(300);

    QCOMPARE(dbusObject->company().name(), QString("testCompany"));
    QCOMPARE(dbusObject->company().copyright(), QString("some copyright"));
    QCOMPARE(dbusObject->company().disambiguation().count(), 2);
    QCOMPARE(dbusObject->company().disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(dbusObject->company().disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(dbusObject->company().properties().count(), 3);
    QCOMPARE(dbusObject->company().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->company().properties().value("property2"), QVariant("fghij"));

    QCOMPARE(dbusObject->line().name(), QString("testLine"));
    QCOMPARE(dbusObject->line().company().isNull(), true);
    QCOMPARE(dbusObject->line().disambiguation().count(), 2);
    QCOMPARE(dbusObject->line().disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(dbusObject->line().disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(dbusObject->line().properties().count(), 2);
    QCOMPARE(dbusObject->line().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->line().properties().value("property2"), QVariant("fghij"));

    QCOMPARE(dbusObject->journey().name(), QString("testJourney"));
    QCOMPARE(dbusObject->journey().line().isNull(), true);
    QCOMPARE(dbusObject->journey().disambiguation().count(), 2);
    QCOMPARE(dbusObject->journey().disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(dbusObject->journey().disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(dbusObject->journey().properties().count(), 2);
    QCOMPARE(dbusObject->journey().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->journey().properties().value("property2"), QVariant("fghij"));

    QCOMPARE(dbusObject->station().name(), QString("testStation"));
    QCOMPARE(dbusObject->station().journey().isNull(), true);
    QCOMPARE(dbusObject->station().disambiguation().count(), 2);
    QCOMPARE(dbusObject->station().disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(dbusObject->station().disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(dbusObject->station().properties().count(), 2);
    QCOMPARE(dbusObject->station().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->station().properties().value("property2"), QVariant("fghij"));
}

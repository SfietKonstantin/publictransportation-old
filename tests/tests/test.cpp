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

#include "test.h"

#include <QtCore/QProcess>
#include <QtCore/QTemporaryFile>
#include <QtDBus/QDBusConnection>
#include <QtTest/QtTest>

#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/waitingtime.h"
#include "common/dbus/dbushelper.h"
#include "common/dbus/dbusconstants.h"
#include "manager/backendinfo.h"
#include "manager/dbus/dbusbackendwrapper.h"
#include "manager/dbus/dbusbackendmanager.h"

#include "generator.h"
#include "dbusobject.h"
#include "signalreceiver.h"


using namespace PublicTransportation;

void Test::testBaseCommonEntities()
{
    Generator::initRand();

    // Test explicit sharing capabilities of TransportationObject
    TransportationObject tO1;
    TransportationObject tO2 = tO1;
    TransportationObject tO3 (tO1);

    tO1.setDisambiguation(Generator::generateRandomVariantMap());
    tO1.setName(Generator::generateRandomString());
    tO1.setProperties(Generator::generateRandomVariantMap());
    QCOMPARE(tO1 == tO2, true);
    QCOMPARE(tO1 == tO3, true);

    TransportationObject tO4 (tO1);
    TransportationObject tO5 = tO1;
    QCOMPARE(tO1 == tO4, true);
    QCOMPARE(tO1 == tO5, true);

    // Test explicit sharing capabilities of WaitingTime
    WaitingTime wT1;
    WaitingTime wT2 = wT1;
    WaitingTime wT3 (wT1);

    wT1.setWaitingTime(Generator::generateRandomNumber());
    tO1.setProperties(Generator::generateRandomVariantMap());
    QCOMPARE(wT1.waitingTime() == wT2.waitingTime(), true);
    QCOMPARE(wT1.properties() == wT2.properties(), true);
    QCOMPARE(wT1.waitingTime() == wT3.waitingTime(), true);
    QCOMPARE(wT1.properties() == wT3.properties(), true);

    WaitingTime wT4 (wT1);
    WaitingTime wT5 = wT1;
    QCOMPARE(wT1.waitingTime() == wT4.waitingTime(), true);
    QCOMPARE(wT1.properties() == wT4.properties(), true);
    QCOMPARE(wT1.waitingTime() == wT5.waitingTime(), true);
    QCOMPARE(wT1.properties() == wT5.properties(), true);
}

void Test::testDBusSimpleReceive()
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
    QCOMPARE(dbusObject->company().disambiguation().count(), 2);
    QCOMPARE(dbusObject->company().disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(dbusObject->company().disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(dbusObject->company().properties().count(), 2);
    QCOMPARE(dbusObject->company().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->company().properties().value("property2"), QVariant("fghij"));

    QCOMPARE(dbusObject->line().name(), QString("testLine"));
    QCOMPARE(dbusObject->line().disambiguation().count(), 2);
    QCOMPARE(dbusObject->line().disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(dbusObject->line().disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(dbusObject->line().properties().count(), 2);
    QCOMPARE(dbusObject->line().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->line().properties().value("property2"), QVariant("fghij"));

    QCOMPARE(dbusObject->journey().name(), QString("testJourney"));
    QCOMPARE(dbusObject->journey().disambiguation().count(), 2);
    QCOMPARE(dbusObject->journey().disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(dbusObject->journey().disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(dbusObject->journey().properties().count(), 2);
    QCOMPARE(dbusObject->journey().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->journey().properties().value("property2"), QVariant("fghij"));

    QCOMPARE(dbusObject->station().name(), QString("testStation"));
    QCOMPARE(dbusObject->station().disambiguation().count(), 2);
    QCOMPARE(dbusObject->station().disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(dbusObject->station().disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(dbusObject->station().properties().count(), 2);
    QCOMPARE(dbusObject->station().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->station().properties().value("property2"), QVariant("fghij"));

    QCOMPARE(dbusObject->waitingTime().waitingTime(), 12345);
    QCOMPARE(dbusObject->waitingTime().properties().value("property1"), QVariant(67890));
    QCOMPARE(dbusObject->waitingTime().properties().value("property2"), QVariant("fghij"));

    QDBusConnection::sessionBus().unregisterObject("/");
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
}

void Test::testBackendInfo()
{
    // Check a good desktop file
    QTemporaryFile desktopFile1;
    if (!desktopFile1.open()) {
        return;
    }

    QString name = Generator::generateRandomString();
    QString comment = Generator::generateRandomString();
    QString icon = Generator::generateRandomString();
    QString exec = Generator::generateRandomString();
    QString id = Generator::generateRandomString();
    QString author = Generator::generateRandomString();
    QString email = Generator::generateRandomString();
    QString website = Generator::generateRandomString();
    QString version = Generator::generateRandomString();

    QTextStream outStream1(&desktopFile1);

    outStream1 << "[Desktop Entry]\n";
    outStream1 << QString("Name=%1\n").arg(name);
    outStream1 << QString("Comment=%1\n").arg(comment);
    outStream1 << QString("Icon=%1\n").arg(icon);
    outStream1 << QString("Type=Service\n");
    outStream1 << QString("Exec=%1\n").arg(exec);
    outStream1 << QString("X-PublicTransportation-BackendInfo-Id=%1\n").arg(id);
    outStream1 << QString("X-PublicTransportation-BackendInfo-Author=%1\n").arg(author);
    outStream1 << QString("X-PublicTransportation-BackendInfo-Email=%1\n").arg(email);
    outStream1 << QString("X-PublicTransportation-BackendInfo-Website=%1\n").arg(website);
    outStream1 << QString("X-PublicTransportation-BackendInfo-Version=%1").arg(version);
    desktopFile1.close();
    BackendInfo backendInfo1 (desktopFile1.fileName());
    QCOMPARE(backendInfo1.isValid(), true);
    QCOMPARE(backendInfo1.name(), name);
    QCOMPARE(backendInfo1.description(), comment);
    QCOMPARE(backendInfo1.icon(), icon);
    QCOMPARE(backendInfo1.executable(), exec);
    QCOMPARE(backendInfo1.backendIdentifier(), id);
    QCOMPARE(backendInfo1.backendAuthor(), author);
    QCOMPARE(backendInfo1.backendEmail(), email);
    QCOMPARE(backendInfo1.backendWebsite(), website);
    QCOMPARE(backendInfo1.backendVersion(), version);

    // Test a bad desktop file
    QTemporaryFile desktopFile2;
    if (!desktopFile2.open()) {
        return;
    }

    QString type = Generator::generateRandomString();

    QTextStream outStream2(&desktopFile2);

    outStream2 << "[Desktop Entry]\n";
    outStream2 << QString("Name=%1\n").arg(name);
    outStream2 << QString("Comment=%1\n").arg(comment);
    outStream2 << QString("Icon=%1\n").arg(icon);
    outStream2 << QString("Type=%1\n").arg(type);
    outStream2 << QString("Exec=%1\n").arg(exec);
    outStream2 << QString("X-PublicTransportation-BackendInfo-Id=%1\n").arg(id);
    outStream2 << QString("X-PublicTransportation-BackendInfo-Author=%1\n").arg(author);
    outStream2 << QString("X-PublicTransportation-BackendInfo-Email=%1\n").arg(email);
    outStream2 << QString("X-PublicTransportation-BackendInfo-Website=%1\n").arg(website);
    outStream2 << QString("X-PublicTransportation-BackendInfo-Version=%1").arg(version);
    desktopFile2.close();
    BackendInfo backendInfo2 (desktopFile2.fileName());
    QCOMPARE(backendInfo2.isValid(), false);

    // Test another bad desktop file
    QTemporaryFile desktopFile3;
    if (!desktopFile3.open()) {
        return;
    }

    QTextStream outStream3(&desktopFile3);

    outStream3 << "[Desktop Entry]\n";
    outStream3 << QString("Name=%1\n").arg(name);
    outStream3 << QString("Comment=%1\n").arg(comment);
    outStream3 << QString("Icon=%1\n").arg(icon);
    outStream3 << QString("Type=Service\n");
    outStream3 << QString("Exec=\n");
    outStream3 << QString("X-PublicTransportation-BackendInfo-Id=%1\n").arg(id);
    outStream3 << QString("X-PublicTransportation-BackendInfo-Author=%1\n").arg(author);
    outStream3 << QString("X-PublicTransportation-BackendInfo-Email=%1\n").arg(email);
    outStream3 << QString("X-PublicTransportation-BackendInfo-Website=%1\n").arg(website);
    outStream3 << QString("X-PublicTransportation-BackendInfo-Version=%1").arg(version);
    desktopFile3.close();
    BackendInfo backendInfo3 (desktopFile3.fileName());
    QCOMPARE(backendInfo3.isValid(), false);
}

void Test::testDBusProvider()
{
    SignalReceiver signalReceiver;

    QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
    DBusBackendWrapper backend ("test", QString("$PROVIDER ") + HELPER_FOLDER
                                        + "/libproviderplugintesthelper.so",
                                QMap<QString, QString>());
    connect(&backend, SIGNAL(suggestedStationsRegistered(int,QList<PublicTransportation::Station>)),
            &signalReceiver, SLOT(saveSuggestedStations(int,QList<PublicTransportation::Station>)));

    backend.launch();
    QTest::qWait(300);

    QString partialStation = Generator::generateRandomString();
    backend.requestSuggestStations(partialStation);
    QTest::qWait(300);

    QList<PublicTransportation::Station> suggestedStations = signalReceiver.suggestedStations();
    QCOMPARE(suggestedStations.count(), 3);
    QCOMPARE(suggestedStations.at(0).name(), partialStation);
    QCOMPARE(suggestedStations.at(1).name(), partialStation.repeated(2));
    QCOMPARE(suggestedStations.at(2).name(), partialStation.repeated(3));

    backend.stop();
    QTest::qWait(300);
    backend.kill();
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
}

void Test::testDBusBackendManager()
{
    SignalReceiver signalReceiver;

    DBusBackendManager::registerDBusService();

    DBusBackendManager manager;
    manager.addBackend("test", QString("$PROVIDER ") + HELPER_FOLDER
                               + "/libproviderplugintesthelper.so",
                       QMap<QString, QString>());

    QCOMPARE(manager.contains("test"), true);

    manager.launchBackend("test");
    QTest::qWait(300);

    AbstractBackendWrapper *backend = manager.backend("test");
    connect(backend, SIGNAL(suggestedStationsRegistered(int,QList<PublicTransportation::Station>)),
            &signalReceiver, SLOT(saveSuggestedStations(int,QList<PublicTransportation::Station>)));

    QString partialStation = Generator::generateRandomString();
    backend->requestSuggestStations(partialStation);
    QTest::qWait(300);

    QList<PublicTransportation::Station> suggestedStations = signalReceiver.suggestedStations();
    QCOMPARE(suggestedStations.count(), 3);
    QCOMPARE(suggestedStations.at(0).name(), partialStation);
    QCOMPARE(suggestedStations.at(1).name(), partialStation.repeated(2));
    QCOMPARE(suggestedStations.at(2).name(), partialStation.repeated(3));

    manager.stopBackend("test");
    QTest::qWait(300);
    manager.killBackend("test");
    manager.removeBackend("test");
    QCOMPARE(manager.contains("test"), false);

    DBusBackendManager::unregisterDBusService();
}

QTEST_MAIN(Test)

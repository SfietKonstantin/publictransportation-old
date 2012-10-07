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
#include "common/dbus/dbushelper.h"
#include "common/dbus/dbusconstants.h"
#include "manager/backendinfo.h"
#include "manager/dbus/dbusbackendwrapper.h"

#include "generator.h"
#include "dbusobject.h"


using namespace PublicTransportation;

void Test::testBaseCommonEntities()
{
    Generator::initRand();

    // Test explicit sharing capabilities of Company
    Company company1;
    Company company2 = company1;
    Company company3 (company1);

    company1.setDisambiguation(Generator::generateRandomVariantMap());
    company1.setName(Generator::generateRandomString());
    company1.setProperties(Generator::generateRandomVariantMap());
    QCOMPARE(company1 == company2, true);
    QCOMPARE(company1 == company3, true);

    Company company4 (company1);
    Company company5 = company1;
    QCOMPARE(company1 == company4, true);
    QCOMPARE(company1 == company5, true);

    // Test explicit sharing capabilities of Line
    Line line1;
    Line line2 = line1;
    Line line3 (line1);

    line1.setDisambiguation(Generator::generateRandomVariantMap());
    line1.setName(Generator::generateRandomString());
    line1.setProperties(Generator::generateRandomVariantMap());

    QCOMPARE(line1 == line2, true);
    QCOMPARE(line1 == line3, true);

    Line line4 (line1);
    Line line5 = line1;
    QCOMPARE(line1 == line4, true);
    QCOMPARE(line1 == line5, true);

    line1.setCompany(company1);
    QCOMPARE(line1 == line2, true);
    QCOMPARE(line1 == line3, true);
    QCOMPARE(line1 == line4, true);
    QCOMPARE(line1 == line5, true);

    Line line6 (line1);
    Line line7 = line1;

    QCOMPARE(line1 == line6, true);
    QCOMPARE(line1 == line7, true);

    // Test autoadd line
    QCOMPARE(company1.lines().contains(line1) == true, true);

    // Test remove line
    company1.removeLine(line1);
    QCOMPARE(company1.lines().contains(line1) == false, true);

    // Test explicit sharing capabilities of Journey
    Journey journey1;
    Journey journey2 = journey1;
    Journey journey3 (journey1);

    journey1.setDisambiguation(Generator::generateRandomVariantMap());
    journey1.setName(Generator::generateRandomString());
    journey1.setProperties(Generator::generateRandomVariantMap());

    QCOMPARE(journey1 == journey2, true);
    QCOMPARE(journey1 == journey3, true);

    Journey journey4 (journey1);
    Journey journey5 = journey1;
    QCOMPARE(journey1 == journey4, true);
    QCOMPARE(journey1 == journey5, true);

    journey1.setLine(line1);
    QCOMPARE(journey1 == journey2, true);
    QCOMPARE(journey1 == journey3, true);
    QCOMPARE(journey1 == journey4, true);
    QCOMPARE(journey1 == journey5, true);

    Journey journey6 (journey1);
    Journey journey7 = journey1;

    QCOMPARE(journey1 == journey6, true);
    QCOMPARE(journey1 == journey7, true);

    // Test autoadd journey
    QCOMPARE(line1.journeys().contains(journey1) == true, true);

    // Test remove journey
    line1.removeJourney(journey1);
    QCOMPARE(line1.journeys().contains(journey1) == false, true);

    // Test explicit sharing capabilities of Station
    Station station1;
    Station station2 = station1;
    Station station3 (station1);

    station1.setDisambiguation(Generator::generateRandomVariantMap());
    station1.setName(Generator::generateRandomString());
    station1.setProperties(Generator::generateRandomVariantMap());

    QCOMPARE(station1 == station2, true);
    QCOMPARE(station1 == station3, true);

    Station station4 (station1);
    Station station5 = station1;
    QCOMPARE(station1 == station4, true);
    QCOMPARE(station1 == station5, true);

    station1.setJourney(journey1);
    QCOMPARE(station1 == station2, true);
    QCOMPARE(station1 == station3, true);
    QCOMPARE(station1 == station4, true);
    QCOMPARE(station1 == station5, true);

    Station station6 (station1);
    Station station7 = station1;

    QCOMPARE(station1 == station6, true);
    QCOMPARE(station1 == station7, true);

    // Test autoadd station
    QCOMPARE(journey1.stations().contains(station1) == true, true);

    // Test remove station
    journey1.removeStation(station1);
    QCOMPARE(journey1.stations().contains(station1) == false, true);

}

void Test::testBaseSharedEntities()
{
    Generator::initRand();

    Company company1;
    company1.setDisambiguation(Generator::generateRandomVariantMap());
    company1.setName(Generator::generateRandomString());
    company1.setProperties(Generator::generateRandomVariantMap());

    Line line1;
    line1.setDisambiguation(Generator::generateRandomVariantMap());
    line1.setName(Generator::generateRandomString());
    line1.setProperties(Generator::generateRandomVariantMap());

    Line line2;
    line2.setDisambiguation(Generator::generateRandomVariantMap());
    line2.setName(Generator::generateRandomString());
    line2.setProperties(Generator::generateRandomVariantMap());

    company1.addLine(line1);
    company1.addLine(line2);

    Company company2 = company1;
    QCOMPARE(company2.lines() == company1.lines(), true);

    Journey journey1;
    journey1.setDisambiguation(Generator::generateRandomVariantMap());
    journey1.setName(Generator::generateRandomString());
    journey1.setProperties(Generator::generateRandomVariantMap());

    Journey journey2;
    journey2.setDisambiguation(Generator::generateRandomVariantMap());
    journey2.setName(Generator::generateRandomString());
    journey2.setProperties(Generator::generateRandomVariantMap());

    line1.addJourney(journey1);
    line1.addJourney(journey2);

    Line line3 = line1;
    QCOMPARE(line1.journeys() == line3.journeys(), true);

    Station station1;
    station1.setDisambiguation(Generator::generateRandomVariantMap());
    station1.setName(Generator::generateRandomString());
    station1.setProperties(Generator::generateRandomVariantMap());

    Station station2;
    station2.setDisambiguation(Generator::generateRandomVariantMap());
    station2.setName(Generator::generateRandomString());
    station2.setProperties(Generator::generateRandomVariantMap());

    journey1.addStation(station1);
    journey1.addStation(station2);

    Journey journey3 = journey1;
    QCOMPARE(journey1.stations() == journey3.stations(), true);
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


void Test::testDBusBackend()
{
    QDBusConnection::sessionBus().registerService(DBUS_SERVICE);

    DBusBackendWrapper wrapper ("test", QString(HELPER_FOLDER) + "/dbuswrappertesthelper",
                                QMap<QString, QString>());
    wrapper.launch();
    QTest::qWait(300);
    wrapper.stop();
    QTest::qWait(300);
    wrapper.kill();
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);

    QList<Company> companies = wrapper.companies();
    QCOMPARE(companies.count(), 1);

    Company company = companies.at(0);
    QCOMPARE(company.name(), QString("testCompany"));
    QCOMPARE(company.copyright(), QString("some copyright"));
    QCOMPARE(company.disambiguation().count(), 2);
    QCOMPARE(company.disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(company.disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(company.properties().count(), 3);
    QCOMPARE(company.properties().value("property1"), QVariant(67890));
    QCOMPARE(company.properties().value("property2"), QVariant("fghij"));

    QList<Line> lines = wrapper.lines(company);
    QCOMPARE(lines.count(), 1);

    Line line = lines.at(0);
    QCOMPARE(line.name(), QString("testLine"));
    QCOMPARE(line.disambiguation().count(), 2);
    QCOMPARE(line.disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(line.disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(line.properties().count(), 2);
    QCOMPARE(line.properties().value("property1"), QVariant(67890));
    QCOMPARE(line.properties().value("property2"), QVariant("fghij"));

    QList<Journey> journeys = wrapper.journeys(company, line);
    QCOMPARE(journeys.count(), 1);

    Journey journey = journeys.at(0);
    QCOMPARE(journey.name(), QString("testJourney"));
    QCOMPARE(journey.disambiguation().count(), 2);
    QCOMPARE(journey.disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(journey.disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(journey.properties().count(), 2);
    QCOMPARE(journey.properties().value("property1"), QVariant(67890));
    QCOMPARE(journey.properties().value("property2"), QVariant("fghij"));

    QList<Station> stations = wrapper.stations(company, line, journey);
    QCOMPARE(stations.count(), 1);

    Station station = stations.at(0);
    QCOMPARE(station.name(), QString("testStation"));
    QCOMPARE(station.disambiguation().count(), 2);
    QCOMPARE(station.disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(station.disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(station.properties().count(), 2);
    QCOMPARE(station.properties().value("property1"), QVariant(67890));
    QCOMPARE(station.properties().value("property2"), QVariant("fghij"));
}

void Test::testDBusProvider()
{
    QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
    DBusBackendWrapper wrapper ("test", QString("$PROVIDER ") + HELPER_FOLDER
                                        + "/libproviderplugintesthelper.so",
                                QMap<QString, QString>());
    wrapper.launch();
    QTest::qWait(300);

    wrapper.requestListCompanies();
    QTest::qWait(300);

    QList<Company> companies = wrapper.companies();
    QCOMPARE(companies.count(), 1);

    Company company = companies.at(0);
    QCOMPARE(company.name(), QString("testCompany"));
    QCOMPARE(company.copyright(), QString("some copyright"));
    QCOMPARE(company.disambiguation().count(), 2);
    QCOMPARE(company.disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(company.disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(company.properties().count(), 3);
    QCOMPARE(company.properties().value("property1"), QVariant(67890));
    QCOMPARE(company.properties().value("property2"), QVariant("fghij"));


    wrapper.requestListLines(company);
    QTest::qWait(300);

    QList<Line> lines = wrapper.lines(company);
    QCOMPARE(lines.count(), 1);

    Line line = lines.at(0);
    QCOMPARE(line.name(), QString("testLine"));
    QCOMPARE(line.disambiguation().count(), 2);
    QCOMPARE(line.disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(line.disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(line.properties().count(), 2);
    QCOMPARE(line.properties().value("property1"), QVariant(67890));
    QCOMPARE(line.properties().value("property2"), QVariant("fghij"));


    wrapper.requestListJourneys(company, line);
    QTest::qWait(300);

    QList<Journey> journeys = wrapper.journeys(company, line);
    QCOMPARE(journeys.count(), 1);

    Journey journey = journeys.at(0);
    QCOMPARE(journey.name(), QString("testJourney"));
    QCOMPARE(journey.disambiguation().count(), 2);
    QCOMPARE(journey.disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(journey.disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(journey.properties().count(), 2);
    QCOMPARE(journey.properties().value("property1"), QVariant(67890));
    QCOMPARE(journey.properties().value("property2"), QVariant("fghij"));


    wrapper.requestListStations(company, line, journey);
    QTest::qWait(300);

    QList<Station> stations = wrapper.stations(company, line, journey);
    QCOMPARE(stations.count(), 1);

    Station station = stations.at(0);
    QCOMPARE(station.name(), QString("testStation"));
    QCOMPARE(station.disambiguation().count(), 2);
    QCOMPARE(station.disambiguation().value("test1"), QVariant(12345));
    QCOMPARE(station.disambiguation().value("test2"), QVariant("abcde"));
    QCOMPARE(station.properties().count(), 2);
    QCOMPARE(station.properties().value("property1"), QVariant(67890));
    QCOMPARE(station.properties().value("property2"), QVariant("fghij"));

    wrapper.stop();
    QTest::qWait(300);
    wrapper.kill();
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
}

QTEST_MAIN(Test)

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

#include "testbase.h"

#include <QtTest/QtTest>

#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"

#include "generator.h"

using namespace PublicTransportation;

void TestBase::testCommonEntities()
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

void TestBase::testSharedEntities()
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

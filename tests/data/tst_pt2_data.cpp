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


#include <QtTest/QtTest>

#include "common/object.h"
#include "common/company.h"
#include "common/line.h"
#include "common/ride.h"
#include "common/station.h"

#include "generator.h"

class TstPt2Data: public QObject
{
    Q_OBJECT

private slots:
    void testBaseCommonEntities()
    {
        Generator::initRand();
        QString identifier = Generator::generateRandomString();
        QVariantMap internal = Generator::generateRandomVariantMap();
        QString name = Generator::generateRandomString();
        QVariantMap properties = Generator::generateRandomVariantMap();

        // Test explicit sharing capabilities of PT2::Object
        PT2::Object o1;
        PT2::Object o2 = o1;
        PT2::Object o3 (o1);

        o1.setIdentifier(identifier);
        o1.setInternal(internal);
        o1.setName(name);
        o1.setProperties(properties);

        QCOMPARE(o1.identifier(), identifier);
        QCOMPARE(o1.internal(), internal);
        QCOMPARE(o1.name(), name);
        QCOMPARE(o1.properties(), properties);

        QCOMPARE(o1, o2);
        QCOMPARE(o1, o3);
        QCOMPARE(o1.identifier(), o2.identifier());
        QCOMPARE(o1.identifier(), o3.identifier());
        QCOMPARE(o1.internal(), o2.internal());
        QCOMPARE(o1.internal(), o3.internal());
        QCOMPARE(o1.name(), o2.name());
        QCOMPARE(o1.name(), o3.name());
        QCOMPARE(o1.properties(), o2.properties());
        QCOMPARE(o1.properties(), o3.properties());



        PT2::Object o4 (o1);
        PT2::Object o5 = o1;
        QCOMPARE(o1, o4);
        QCOMPARE(o1, o5);
        QCOMPARE(o1.identifier(), o4.identifier());
        QCOMPARE(o1.identifier(), o5.identifier());
        QCOMPARE(o1.internal(), o4.internal());
        QCOMPARE(o1.internal(), o5.internal());
        QCOMPARE(o1.name(), o4.name());
        QCOMPARE(o1.name(), o5.name());
        QCOMPARE(o1.properties(), o4.properties());
        QCOMPARE(o1.properties(), o5.properties());

        // Test explicit sharing capabilities of WaitingTime
//        WaitingTime wT1;
//        WaitingTime wT2 = wT1;
//        WaitingTime wT3 (wT1);

//        wT1.setWaitingTime(Generator::generateRandomNumber());
//        o1.setProperties(Generator::generateRandomVariantMap());
//        QCOMPARE(wT1.waitingTime(), wT2.waitingTime());
//        QCOMPARE(wT1.properties(), wT2.properties());
//        QCOMPARE(wT1.waitingTime(), wT3.waitingTime());
//        QCOMPARE(wT1.properties(), wT3.properties());

//        WaitingTime wT4 (wT1);
//        WaitingTime wT5 = wT1;
//        QCOMPARE(wT1.waitingTime(), wT4.waitingTime());
//        QCOMPARE(wT1.properties(), wT4.properties());
//        QCOMPARE(wT1.waitingTime(), wT5.waitingTime());
//        QCOMPARE(wT1.properties(), wT5.properties());
    }
    void testAdvancedEntitiesConstructor()
    {
        QString identifier = Generator::generateRandomString();
        QVariantMap internal = Generator::generateRandomVariantMap();
        QString name = Generator::generateRandomString();
        QVariantMap properties = Generator::generateRandomVariantMap();
        PT2::Company c (identifier, internal, name, properties);
        QCOMPARE(c.identifier(), identifier);
        QCOMPARE(c.internal(), internal);
        QCOMPARE(c.name(), name);
        QCOMPARE(c.properties(), properties);
        PT2::Line l (identifier, internal, name, properties);
        QCOMPARE(l.identifier(), identifier);
        QCOMPARE(l.internal(), internal);
        QCOMPARE(l.name(), name);
        QCOMPARE(l.properties(), properties);
        PT2::Ride r (identifier, internal, name, properties);
        QCOMPARE(r.identifier(), identifier);
        QCOMPARE(r.internal(), internal);
        QCOMPARE(r.name(), name);
        QCOMPARE(r.properties(), properties);
        PT2::Station s (identifier, internal, name, properties);
        QCOMPARE(s.identifier(), identifier);
        QCOMPARE(s.internal(), internal);
        QCOMPARE(s.name(), name);
        QCOMPARE(s.properties(), properties);
    }
};

QTEST_MAIN(TstPt2Data)

#include "tst_pt2_data.moc"

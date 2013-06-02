/*
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * The names of its contributors may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */
/**
 * @file dbushelper.cpp
 * @short Implementation of helper functions used by DBus interface
 */

#include "dbushelper.h"

#include <QtDBus/QtDBus>
#include <QtDBus/QDBusArgument>
#include "common/company.h"
#include "common/line.h"
#include "common/ride.h"
#include "common/station.h"
//#include "common/waitingtime.h"
//#include "common/infojourneys.h"
//#include "common/journeyandwaitingtime.h"
//#include "common/infojourneywaitingtime.h"

namespace PT2
{

QDBusArgument & objectToDBus(QDBusArgument &argument, const Object &object)
{
    argument.beginStructure();

    // Identifier
    argument << object.identifier();

    // Internal
    argument.beginMap(qMetaTypeId<QString>(), qMetaTypeId<QDBusVariant>());
    QVariantMap map = object.internal();
    foreach (QString key, map.keys()) {
        argument.beginMapEntry();
        argument << key << QDBusVariant(map.value(key));
        argument.endMapEntry();
    }
    argument.endMap();

    // Name
    argument << object.name();

    // Properties map
    argument.beginMap(qMetaTypeId<QString>(), qMetaTypeId<QDBusVariant>());
    map = object.properties();
    foreach (QString key, map.keys()) {
        argument.beginMapEntry();
        argument << key << QDBusVariant(map.value(key));
        argument.endMapEntry();
    }
    argument.endMap();
    argument.endStructure();

    return argument;
}

const QDBusArgument & objectFromDBus(const QDBusArgument &argument, Object &object)
{
    argument.beginStructure();

    // Identifier
    QString identifier;
    argument >> identifier;
    object.setIdentifier(identifier);

    // Internal map
    QVariantMap map;
    argument.beginMap();
    while (!argument.atEnd()) {
        argument.beginMapEntry();
        QString key;
        QDBusVariant value;
        argument >> key;
        argument >> value;
        map.insert(key, value.variant());
        argument.endMapEntry();
    }
    argument.endMap();
    object.setInternal(map);

    // Name
    QString name;
    argument >> name;
    object.setName(name);

    // Properties map
    map.clear();
    argument.beginMap();
    while (!argument.atEnd()) {
        argument.beginMapEntry();
        QString key;
        QDBusVariant value;
        argument >> key;
        argument >> value;
        map.insert(key, value.variant());
        argument.endMapEntry();
    }
    argument.endMap();
    object.setProperties(map);
    argument.endStructure();

    return argument;
}

QDBusArgument & operator<<(QDBusArgument &argument, const Company &company)
{
    return objectToDBus(argument, company);
}

const QDBusArgument & operator>>(const QDBusArgument &argument, Company &company)
{
    return objectFromDBus(argument, company);
}

QDBusArgument & operator<<(QDBusArgument &argument, const Line &line)
{
    return objectToDBus(argument, line);
}

const QDBusArgument & operator>>(const QDBusArgument &argument, Line &line)
{
    return objectFromDBus(argument, line);
}

QDBusArgument & operator<<(QDBusArgument &argument, const Ride &ride)
{
    return objectToDBus(argument, ride);
}

const QDBusArgument & operator>>(const QDBusArgument &argument, Ride &ride)
{
    return objectFromDBus(argument, ride);
}

QDBusArgument & operator<<(QDBusArgument &argument, const Station &station)
{
    return objectToDBus(argument, station);
}

const QDBusArgument & operator>>(const QDBusArgument &argument, Station &station)
{
    return objectFromDBus(argument, station);
}

//QDBusArgument & operator<<(QDBusArgument &argument, const WaitingTime &waitingTime)
//{
//    argument.beginStructure();
//    argument << waitingTime.waitingTime();

//    // Properties map
//    argument.beginMap(qMetaTypeId<QString>(), qMetaTypeId<QDBusVariant>());
//    QVariantMap map = waitingTime.properties();
//    foreach (QString key, map.keys()) {
//        argument.beginMapEntry();
//        argument << key << QDBusVariant(map.value(key));
//        argument.endMapEntry();
//    }
//    argument.endMap();
//    argument.endStructure();
//    return argument;
//}

//const QDBusArgument & operator>>(const QDBusArgument &argument, WaitingTime &waitingTime)
//{
//    argument.beginStructure();
//    int time;
//    argument >> time;
//    waitingTime.setWaitingTime(time);

//    // Properties map
//    QVariantMap map;
//    argument.beginMap();
//    while (!argument.atEnd()) {
//        argument.beginMapEntry();
//        QString key;
//        QDBusVariant value;
//        argument >> key;
//        argument >> value;
//        map.insert(key, value.variant());
//        argument.endMapEntry();
//    }
//    argument.endMap();
//    waitingTime.setProperties(map);
//    argument.endStructure();
//    return argument;
//}

//QDBusArgument & operator<<(QDBusArgument &argument, const JourneyAndStation &journeyAndStation)
//{
//    argument.beginStructure();
//    argument << journeyAndStation.first;
//    argument << journeyAndStation.second;
//    argument.endStructure();

//    return argument;
//}

//const QDBusArgument & operator>>(const QDBusArgument &argument,
//                                 JourneyAndStation &journeyAndStation)
//{
//    argument.beginStructure();
//    argument >> journeyAndStation.first;
//    argument >> journeyAndStation.second;
//    argument.endStructure();

//    return argument;
//}

//QDBusArgument & operator<<(QDBusArgument &argument, const InfoJourneys &infoJourneys)
//{
//    argument.beginStructure();
//    argument << infoJourneys.company();
//    argument << infoJourneys.line();

//    argument.beginArray(qMetaTypeId<PublicTransportation::JourneyAndStation>());
//    foreach(JourneyAndStation journeyStation, infoJourneys.journeysAndStations()) {
//        argument << journeyStation;
//    }
//    argument.endArray();
//    argument.endStructure();
//    return argument;
//}

//const QDBusArgument & operator>>(const QDBusArgument &argument, InfoJourneys &infoJourneys)
//{
//    argument.beginStructure();
//    Company company;
//    argument >> company;
//    infoJourneys.setCompany(company);
//    Line line;
//    argument >> line;
//    infoJourneys.setLine(line);

//    argument.beginArray();
//    QList<JourneyAndStation> journeysStations;
//    while (!argument.atEnd()) {
//        JourneyAndStation journeyStation;
//        argument >> journeyStation;
//        journeysStations.append(journeyStation);
//    }
//    argument.endArray();
//    infoJourneys.setJourneysAndStations(journeysStations);

//    argument.endStructure();
//    return argument;
//}

//QDBusArgument & operator<<(QDBusArgument &argument,
//                           const JourneyAndWaitingTime &journeyAndWaitingTime)
//{
//    argument.beginStructure();
//    argument << journeyAndWaitingTime.journey();
//    argument << journeyAndWaitingTime.waitingTime();
//    argument.endStructure();
//    return argument;
//}

//const QDBusArgument & operator>>(const QDBusArgument &argument,
//                                 JourneyAndWaitingTime &journeyAndWaitingTime)
//{
//    argument.beginStructure();
//    Journey journey;
//    argument >> journey;
//    journeyAndWaitingTime.setJourney(journey);
//    WaitingTime waitingTime;
//    argument >> waitingTime;
//    journeyAndWaitingTime.setWaitingTime(waitingTime);
//    argument.endStructure();
//    return argument;
//}


//QDBusArgument & operator<<(QDBusArgument &argument,
//                           const InfoJourneyWaitingTime &infoJourneyWaitingTime)
//{
//    argument.beginStructure();
//    argument << infoJourneyWaitingTime.company();
//    argument << infoJourneyWaitingTime.line();
//    argument << infoJourneyWaitingTime.journey();
//    argument << infoJourneyWaitingTime.station();
//    argument << infoJourneyWaitingTime.waitingTime();
//    argument.endStructure();
//    return argument;
//}

//const QDBusArgument & operator>>(const QDBusArgument &argument,
//                                 InfoJourneyWaitingTime &infoJourneyWaitingTime)
//{
//    argument.beginStructure();
//    Company company;
//    argument >> company;
//    infoJourneyWaitingTime.setCompany(company);
//    Line line;
//    argument >> line;
//    infoJourneyWaitingTime.setLine(line);
//    Journey journey;
//    argument >> journey;
//    infoJourneyWaitingTime.setJourney(journey);
//    Station station;
//    argument >> station;
//    infoJourneyWaitingTime.setStation(station);
//    WaitingTime waitingTime;
//    argument >> waitingTime;
//    infoJourneyWaitingTime.setWaitingTime(waitingTime);
//    argument.endStructure();
//    return argument;
//}

void registerDBusTypes()
{
    qDBusRegisterMetaType<PT2::Company>();
    qDBusRegisterMetaType<QList<PT2::Company> >();
    qDBusRegisterMetaType<PT2::Line>();
    qDBusRegisterMetaType<QList<PT2::Line> >();
    qDBusRegisterMetaType<PT2::Ride>();
    qDBusRegisterMetaType<QList<PT2::Ride> >();
    qDBusRegisterMetaType<PT2::Station>();
    qDBusRegisterMetaType<QList<PT2::Station> >();
//    qDBusRegisterMetaType<PublicTransportation::WaitingTime>();
//    qDBusRegisterMetaType<QList<PublicTransportation::WaitingTime> >();
//    qDBusRegisterMetaType<PublicTransportation::JourneyAndStation>();
//    qDBusRegisterMetaType<QList<PublicTransportation::JourneyAndStation> >();
//    qDBusRegisterMetaType<PublicTransportation::InfoJourneys>();
//    qDBusRegisterMetaType<QList<PublicTransportation::InfoJourneys> >();
//    qDBusRegisterMetaType<PublicTransportation::JourneyAndWaitingTime>();
//    qDBusRegisterMetaType<QList<PublicTransportation::JourneyAndWaitingTime> >();
//    qDBusRegisterMetaType<PublicTransportation::InfoJourneyWaitingTime>();
//    qDBusRegisterMetaType<QList<PublicTransportation::InfoJourneyWaitingTime> >();
}

}

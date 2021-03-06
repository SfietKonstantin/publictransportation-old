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

/**
 * @file dbushelper.cpp
 * @short Implementation of helper functions used by DBus interface
 */

#include "dbushelper.h"

#include <QtDBus/QtDBus>
#include <QtDBus/QDBusArgument>
#include "common/company.h"
#include "common/line.h"
#include "common/waitingtime.h"
#include "common/infojourneys.h"
#include "common/journeyandwaitingtime.h"
#include "common/infojourneywaitingtime.h"

namespace PublicTransportation
{

QDBusArgument & transportationObjectToDBus(QDBusArgument &argument,
                                           const TransportationObject &transportationObject)
{
    argument.beginStructure();

    // Disambiguation map
    argument.beginMap(qMetaTypeId<QString>(), qMetaTypeId<QDBusVariant>());
    QVariantMap map = transportationObject.disambiguation();
    foreach (QString key, map.keys()) {
        argument.beginMapEntry();
        argument << key << QDBusVariant(map.value(key));
        argument.endMapEntry();
    }
    argument.endMap();

    // Name
    argument << transportationObject.name();

    // Properties map
    argument.beginMap(qMetaTypeId<QString>(), qMetaTypeId<QDBusVariant>());
    map = transportationObject.properties();
    foreach (QString key, map.keys()) {
        argument.beginMapEntry();
        argument << key << QDBusVariant(map.value(key));
        argument.endMapEntry();
    }
    argument.endMap();
    argument.endStructure();

    return argument;
}

const QDBusArgument & transportationObjectFromDBus(const QDBusArgument &argument,
                                                   TransportationObject &transportationObject)
{
    argument.beginStructure();

    // Disambiguation map
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
    transportationObject.setDisambiguation(map);

    // Name
    QString name;
    argument >> name;
    transportationObject.setName(name);

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
    transportationObject.setProperties(map);
    argument.endStructure();

    return argument;
}

QDBusArgument & operator<<(QDBusArgument &argument, const Company &company)
{
    return transportationObjectToDBus(argument, company);
}

const QDBusArgument & operator>>(const QDBusArgument &argument, Company &company)
{
    return transportationObjectFromDBus(argument, company);
}

QDBusArgument & operator<<(QDBusArgument &argument, const Line &line)
{
    return transportationObjectToDBus(argument, line);
}

const QDBusArgument & operator>>(const QDBusArgument &argument, Line &line)
{
    return transportationObjectFromDBus(argument, line);
}

QDBusArgument & operator<<(QDBusArgument &argument, const Journey &journey)
{
    return transportationObjectToDBus(argument, journey);
}

const QDBusArgument & operator>>(const QDBusArgument &argument, Journey &journey)
{
    return transportationObjectFromDBus(argument, journey);
}

QDBusArgument & operator<<(QDBusArgument &argument, const Station &station)
{
    return transportationObjectToDBus(argument, station);
}

const QDBusArgument & operator>>(const QDBusArgument &argument, Station &station)
{
    return transportationObjectFromDBus(argument, station);
}

QDBusArgument & operator<<(QDBusArgument &argument, const WaitingTime &waitingTime)
{
    argument.beginStructure();
    argument << waitingTime.waitingTime();

    // Properties map
    argument.beginMap(qMetaTypeId<QString>(), qMetaTypeId<QDBusVariant>());
    QVariantMap map = waitingTime.properties();
    foreach (QString key, map.keys()) {
        argument.beginMapEntry();
        argument << key << QDBusVariant(map.value(key));
        argument.endMapEntry();
    }
    argument.endMap();
    argument.endStructure();
    return argument;
}

const QDBusArgument & operator>>(const QDBusArgument &argument, WaitingTime &waitingTime)
{
    argument.beginStructure();
    int time;
    argument >> time;
    waitingTime.setWaitingTime(time);

    // Properties map
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
    waitingTime.setProperties(map);
    argument.endStructure();
    return argument;
}

QDBusArgument & operator<<(QDBusArgument &argument, const JourneyAndStation &journeyAndStation)
{
    argument.beginStructure();
    argument << journeyAndStation.first;
    argument << journeyAndStation.second;
    argument.endStructure();

    return argument;
}

const QDBusArgument & operator>>(const QDBusArgument &argument,
                                 JourneyAndStation &journeyAndStation)
{
    argument.beginStructure();
    argument >> journeyAndStation.first;
    argument >> journeyAndStation.second;
    argument.endStructure();

    return argument;
}

QDBusArgument & operator<<(QDBusArgument &argument, const InfoJourneys &infoJourneys)
{
    argument.beginStructure();
    argument << infoJourneys.company();
    argument << infoJourneys.line();

    argument.beginArray(qMetaTypeId<PublicTransportation::JourneyAndStation>());
    foreach(JourneyAndStation journeyStation, infoJourneys.journeysAndStations()) {
        argument << journeyStation;
    }
    argument.endArray();
    argument.endStructure();
    return argument;
}

const QDBusArgument & operator>>(const QDBusArgument &argument, InfoJourneys &infoJourneys)
{
    argument.beginStructure();
    Company company;
    argument >> company;
    infoJourneys.setCompany(company);
    Line line;
    argument >> line;
    infoJourneys.setLine(line);

    argument.beginArray();
    QList<JourneyAndStation> journeysStations;
    while (!argument.atEnd()) {
        JourneyAndStation journeyStation;
        argument >> journeyStation;
        journeysStations.append(journeyStation);
    }
    argument.endArray();
    infoJourneys.setJourneysAndStations(journeysStations);

    argument.endStructure();
    return argument;
}

QDBusArgument & operator<<(QDBusArgument &argument,
                           const JourneyAndWaitingTime &journeyAndWaitingTime)
{
    argument.beginStructure();
    argument << journeyAndWaitingTime.journey();
    argument << journeyAndWaitingTime.waitingTime();
    argument.endStructure();
    return argument;
}

const QDBusArgument & operator>>(const QDBusArgument &argument,
                                 JourneyAndWaitingTime &journeyAndWaitingTime)
{
    argument.beginStructure();
    Journey journey;
    argument >> journey;
    journeyAndWaitingTime.setJourney(journey);
    WaitingTime waitingTime;
    argument >> waitingTime;
    journeyAndWaitingTime.setWaitingTime(waitingTime);
    argument.endStructure();
    return argument;
}


QDBusArgument & operator<<(QDBusArgument &argument,
                           const InfoJourneyWaitingTime &infoJourneyWaitingTime)
{
    argument.beginStructure();
    argument << infoJourneyWaitingTime.company();
    argument << infoJourneyWaitingTime.line();
    argument << infoJourneyWaitingTime.journey();
    argument << infoJourneyWaitingTime.station();
    argument << infoJourneyWaitingTime.waitingTime();
    argument.endStructure();
    return argument;
}

const QDBusArgument & operator>>(const QDBusArgument &argument,
                                 InfoJourneyWaitingTime &infoJourneyWaitingTime)
{
    argument.beginStructure();
    Company company;
    argument >> company;
    infoJourneyWaitingTime.setCompany(company);
    Line line;
    argument >> line;
    infoJourneyWaitingTime.setLine(line);
    Journey journey;
    argument >> journey;
    infoJourneyWaitingTime.setJourney(journey);
    Station station;
    argument >> station;
    infoJourneyWaitingTime.setStation(station);
    WaitingTime waitingTime;
    argument >> waitingTime;
    infoJourneyWaitingTime.setWaitingTime(waitingTime);
    argument.endStructure();
    return argument;
}

void registerDBusTypes()
{
    qDBusRegisterMetaType<PublicTransportation::Company>();
    qDBusRegisterMetaType<QList<PublicTransportation::Company> >();
    qDBusRegisterMetaType<PublicTransportation::Line>();
    qDBusRegisterMetaType<QList<PublicTransportation::Line> >();
    qDBusRegisterMetaType<PublicTransportation::Journey>();
    qDBusRegisterMetaType<QList<PublicTransportation::Journey> >();
    qDBusRegisterMetaType<PublicTransportation::Station>();
    qDBusRegisterMetaType<QList<PublicTransportation::Station> >();
    qDBusRegisterMetaType<PublicTransportation::WaitingTime>();
    qDBusRegisterMetaType<QList<PublicTransportation::WaitingTime> >();
    qDBusRegisterMetaType<PublicTransportation::JourneyAndStation>();
    qDBusRegisterMetaType<QList<PublicTransportation::JourneyAndStation> >();
    qDBusRegisterMetaType<PublicTransportation::InfoJourneys>();
    qDBusRegisterMetaType<QList<PublicTransportation::InfoJourneys> >();
    qDBusRegisterMetaType<PublicTransportation::JourneyAndWaitingTime>();
    qDBusRegisterMetaType<QList<PublicTransportation::JourneyAndWaitingTime> >();
    qDBusRegisterMetaType<PublicTransportation::InfoJourneyWaitingTime>();
    qDBusRegisterMetaType<QList<PublicTransportation::InfoJourneyWaitingTime> >();
}

}

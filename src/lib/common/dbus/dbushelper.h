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

#ifndef PUBLICTRANSPORTATION_DBUSHELPER_H
#define PUBLICTRANSPORTATION_DBUSHELPER_H

#include <QtCore/QList>

class QDBusArgument;
namespace PublicTransportation
{

class TransportationObject;
class Company;
class Line;
class Journey;
class Station;

QDBusArgument & transportationObjectToDBus(QDBusArgument &argument,
                                           const TransportationObject &transportationObject);
const QDBusArgument & transportationObjectFromDBus(const QDBusArgument &argument,
                                                   TransportationObject &transportationObject);

QDBusArgument & operator<<(QDBusArgument &argument, const Company &company);
const QDBusArgument & operator>>(const QDBusArgument &argument, Company &company);
QDBusArgument & operator<<(QDBusArgument &argument, const Line &line);
const QDBusArgument & operator>>(const QDBusArgument &argument, Line &line);
QDBusArgument & operator<<(QDBusArgument &argument, const Journey &journey);
const QDBusArgument & operator>>(const QDBusArgument &argument, Journey &journey);
QDBusArgument & operator<<(QDBusArgument &argument, const Station &station);
const QDBusArgument & operator>>(const QDBusArgument &argument, Station &station);

void registerDBusTypes();
}

#endif // PUBLICTRANSPORTATION_DBUSHELPER_H

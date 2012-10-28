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
 * @file dbusbackendmanager.cpp
 * @short Implementation of PublicTransportation::DBusBackendManager
 */

#include "dbusbackendmanager.h"

#include <QtDBus/QDBusConnection>

#include "common/dbus/dbusconstants.h"
#include "dbusbackendwrapper.h"

namespace PublicTransportation
{

DBusBackendManager::DBusBackendManager(QObject *parent) :
    AbstractBackendManager(parent)
{
}

AbstractBackendWrapper * DBusBackendManager::createBackend(const QString &identifier,
                                                           const QString &executable,
                                                           const QMap<QString, QString> &attributes,
                                                           QObject *parent) const
{
    return new DBusBackendWrapper(identifier, executable, attributes, parent);
}

bool DBusBackendManager::registerDBusService()
{
    return QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
}

bool DBusBackendManager::unregisterDBusService()
{
    return QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
}

}

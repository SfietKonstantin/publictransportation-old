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
#include <QtCore/QStringList>
#include <QtDBus/QDBusConnection>

#include "debug.h"
#include "manager/dbus/dbusbackendmanager.h"

#include "dbushandle.h"

using namespace PublicTransportation;

#ifdef Q_OS_UNIX
#include <signal.h>

void signalhandler(int signal)
{
    debug("main") << "Interrupted";
    debug("main") << "Need to do some cleanup";
    if(signal == SIGINT || signal == SIGTERM) {
        QCoreApplication::instance()->quit();
    }
}
#endif

int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);

    // Connect to UNIX signals
#ifdef Q_OS_UNIX
    signal(SIGINT, signalhandler);
    signal(SIGTERM, signalhandler);
#endif

    // Register DBus
    if (!DBusBackendManager::registerDBusService()) {
        debug("main") << "Unable to register the service on DBus";
        debug("main") << "Another instance of publictransportation might be running";
        return 0;
    }

    DBusBackendManager manager;
    DBusHandle handle;
    handle.setBackendManager(&manager);

    QDBusConnection::sessionBus().registerObject("/", &handle, QDBusConnection::ExportAllSlots);

    return app.exec();
}

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
 * @file provider/main.cpp
 * @short Entry point of the provider
 */

#include <iostream>
#include <signal.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>

#include "debug.h"
#include "common/dbus/dbushelper.h"
#include "provider/dbus/providerplugindbuswrapper.h"

using namespace std;
using namespace PublicTransportation;

/**
 * @brief Display help
 */
void displayHelp()
{
    QString version = QString("%1.%2.%3").arg(QString::number(VERSION_MAJOR),
                                              QString::number(VERSION_MINOR),
                                              QString::number(VERSION_PATCH));

    cout << "Public transportation provider backend, version "
         << version.toAscii().constData() << endl;
    cout << endl;
    cout << "Usage: publictransportation-provider --plugin <plugin.so> --object <dbus-object>"
         << endl;
    cout << "    --plugin <plugin.so>             run a provider instance with the provided plugin."
         << endl;
    cout << "    --identifier <dbus-identifier>   \
use the provided DBus identifier to communicate with"
         << endl;
}

/**
 * @brief Get the argument corresponding to the plugin
 * @param arguments argument list.
 * @return plugin.
 */
QString getPlugin(const QStringList &arguments)
{
    if (arguments.at(1) == "--plugin") {
        return arguments.at(2);
    } else if (arguments.at(3) == "--plugin") {
        return arguments.at(4);
    }
    return QString();
}

/**
 * @brief Get the argument corresponding to the DBus identifier
 * @param arguments argument list.
 * @return DBus identifier.
 */
QString getDBusIdentifier(const QStringList &arguments)
{
    if (arguments.at(1) == "--identifier") {
        return arguments.at(2);
    } else if (arguments.at(3) == "--identifier") {
        return arguments.at(4);
    }
    return QString();
}

/**
 * @brief UNIX signal handler
 * @param signal signal.
 */
void signalHandler(int signal)
{
    switch(signal) {
        case SIGTERM:
            debug("provider") << "Provider terminated";
            QCoreApplication::quit();
            break;
    }
}

/**
 * @brief Main
 *
 * Entry point of the provider.
 *
 * @param argc argc.
 * @param argv argv.
 * @return exit code.
 */
int main(int argc, char **argv)
{
    // Check argument count
    QCoreApplication app(argc, argv);
    if (app.arguments().count() != 5) {
        displayHelp();
        return 0;
    }

    // Check arguments
    QString plugin = getPlugin(app.arguments());
    QString identifier = getDBusIdentifier(app.arguments());

    if (plugin.isEmpty() || identifier.isEmpty()) {
        displayHelp();
        return 0;
    }

    // Create the provider plugin wrapper and load it
    ProviderPluginDBusWrapper pluginWrapper (identifier);
    if (!pluginWrapper.load(plugin)) {
        warning("provider") << "The plugin could not be loaded";
        return 0;
    }

    // Handle signals
    signal(SIGTERM, signalHandler);

    return app.exec();
}

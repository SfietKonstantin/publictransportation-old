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
//#include "provider/dbus/providerplugindbuswrapper.h"

using namespace std;
//using namespace PublicTransportation;

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

//    // Check arguments
    QString plugin = getPlugin(app.arguments());
    QString identifier = getDBusIdentifier(app.arguments());

    if (plugin.isEmpty() || identifier.isEmpty()) {
        displayHelp();
        return 0;
    }

    // Create the provider plugin wrapper and load it
//    ProviderPluginDBusWrapper pluginWrapper (identifier);
//    if (!pluginWrapper.load(plugin)) {
//        warning("provider") << "The plugin could not be loaded";
//        return 0;
//    }

    return app.exec();
}

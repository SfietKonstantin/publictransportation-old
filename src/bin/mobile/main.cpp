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
 * @file mobile/main.cpp
 * @short Entry point of the mobile application
 */

#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>

#include "manager/dbus/dbusbackendmanager.h"
#include "backendmodel.h"
#include "searchstationmodel.h"

using namespace PublicTransportation;

/**
 * @brief Main
 *
 * Entry point of the mobile application.
 *
 * @param argc argc.
 * @param argv argv.
 * @return exit code.
 */
int main(int argc, char **argv)
{
    // Setup applications
    QApplication app(argc, argv);
    app.setOrganizationName("SfietKonstantin");
    app.setApplicationName("PublicTransportation");

    // Setup DBus
    DBusBackendManager::registerDBusService();

    // Setup models and manager
    BackendModel backendModel;
    SearchStationModel searchStationModel;

    DBusBackendManager dbusBackendManager;
    backendModel.setBackendManager(&dbusBackendManager);
    searchStationModel.setBackendManager(&dbusBackendManager);

    // Load backend list
    backendModel.reload();

    // Set QML context
    qmlRegisterUncreatableType<BackendModel>("org.SfietKonstantin.publictransportation",
                                             1, 0, "BackendModel",
                                             "BackendModel cannot be created");

    QSettings settings;
    bool backendFirstTime = !settings.contains("backend/firstTime");
    if (backendFirstTime) {
        settings.setValue("backend/firstTime", QVariant(false));
    }

    QDeclarativeView view;
    view.rootContext()->setContextProperty("BACKEND_FIRST_TIME", QVariant(backendFirstTime));
    view.rootContext()->setContextProperty("BackendModelInstance", &backendModel);
    view.rootContext()->setContextProperty("SearchStationModelInstance", &searchStationModel);

    // Launch application
    view.setSource(QUrl(MAIN_QML_FILE));
    view.showFullScreen();

    return app.exec();
}

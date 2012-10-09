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
#include "companiesmodel.h"
#include "linesmodel.h"
#include "journeysmodel.h"
#include "stationsmodel.h"

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
    CompaniesModel companiesModel;
    LinesModel linesModel;
    JourneysModel journeysModel;
    StationsModel stationsModel;

    DBusBackendManager dbusBackendManager;
    backendModel.setBackendManager(&dbusBackendManager);
    companiesModel.setBackendManager(&dbusBackendManager);
    linesModel.setBackendManager(&dbusBackendManager);
    journeysModel.setBackendManager(&dbusBackendManager);
    stationsModel.setBackendManager(&dbusBackendManager);

    QObject::connect(&companiesModel, SIGNAL(linesRequested(QString,PublicTransportation::Company)),
                     &linesModel, SLOT(displayLines(QString,PublicTransportation::Company)));
    QObject::connect(&linesModel, SIGNAL(journeysRequested(QString,PublicTransportation::Company,
                                                           PublicTransportation::Line)),
                     &journeysModel, SLOT(displayJourneys(QString,PublicTransportation::Company,
                                                          PublicTransportation::Line)));
    QObject::connect(&journeysModel, SIGNAL(stationsRequested(QString,PublicTransportation::Company,
                                                              PublicTransportation::Line,
                                                              PublicTransportation::Journey)),
                     &stationsModel, SLOT(displayStations(QString,PublicTransportation::Company,
                                                          PublicTransportation::Line,
                                                          PublicTransportation::Journey)));

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
    view.rootContext()->setContextProperty("CompaniesModelInstance", &companiesModel);
    view.rootContext()->setContextProperty("LinesModelInstance", &linesModel);
    view.rootContext()->setContextProperty("JourneysModelInstance", &journeysModel);
    view.rootContext()->setContextProperty("StationsModelInstance", &stationsModel);

    // Launch application
    view.setSource(QUrl(MAIN_QML_FILE));
    view.showFullScreen();

    return app.exec();
}

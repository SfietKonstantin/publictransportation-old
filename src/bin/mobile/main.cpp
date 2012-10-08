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

#include <QtGui/QApplication>
#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>

#include "manager/dbus/dbusbackendmanager.h"
#include "backendmodel.h"
#include "companiesmodel.h"

#include "manager/backendlistmanager.h"

using namespace PublicTransportation;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    DBusBackendManager::registerDBusService();
    BackendModel backendModel;
    CompaniesModel companiesModel;
    DBusBackendManager dbusBackendManager;
    backendModel.setBackendManager(&dbusBackendManager);
    backendModel.reload();
    companiesModel.setBackendManager(&dbusBackendManager);

    qmlRegisterUncreatableType<BackendModel>("org.SfietKonstantin.publictransportation",
                                             1, 0, "BackendModel",
                                             "BackendModel cannot be created");

    QDeclarativeView view;
    view.rootContext()->setContextProperty("BackendModelInstance", &backendModel);
    view.rootContext()->setContextProperty("CompaniesModelInstance", &companiesModel);
    view.setSource(QUrl(MAIN_QML_FILE));
    view.showFullScreen();

    return app.exec();
}

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

#ifndef DBUSHANDLE_H
#define DBUSHANDLE_H

#include <QtCore/QObject>
#include "manager/abstractbackendmanager.h"
#include "manager/backendlistmanager.h"

class DBusHandle : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.SfietKonstantin.publictransportation")
public:
    explicit DBusHandle(QObject *parent = 0);
    void setBackendManager(PublicTransportation::AbstractBackendManager *manager);
public slots:
    void listBackends();
    void runBackend(int backendIndex);
    void listCapabilities(int backendIndex);
    void requestCompanies(int backendIndex);
//    void requestLines();
//    void requestJourneys(const QString &lineName);
//    void requestStations(const QString &lineName, int journeyIndex);
private:
    PublicTransportation::AbstractBackendManager *m_manager;
    PublicTransportation::BackendListManager *m_list;
};

#endif // DBUSHANDLE_H

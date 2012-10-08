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

#include "dbushandle.h"
#include "debug.h"

#include <QtCore/QDateTime>

using namespace PublicTransportation;

DBusHandle::DBusHandle(QObject *parent) :
    QObject(parent)
{
    m_manager = 0;
    m_list = new BackendListManager(this);
}

void DBusHandle::setBackendManager(PublicTransportation::AbstractBackendManager *manager)
{
    m_manager = manager;
}

void DBusHandle::listBackends()
{
    m_list->reload();
    debug("handle") << "Backends reloaded";
    debug("handle") << "Backend list";
    foreach (BackendInfo backendInfo, m_list->backendList()) {
        debug("handle") << backendInfo.name() << backendInfo.backendIdentifier();
    }
}

void DBusHandle::runBackend(int backendIndex)
{
    QList<BackendInfo> backendList = m_list->backendList();
    if (backendIndex < 0 || backendIndex >= backendList.count()) {
        return;
    }
    debug("handle") << "Running backend" << backendIndex;
    BackendInfo backendInfo = backendList.at(backendIndex);
    m_manager->addBackend(QString::number(backendIndex), backendInfo.executable(),
                          QMap<QString, QString>());
    m_manager->launchBackend(QString::number(backendIndex));
}

void DBusHandle::listCapabilities(int backendIndex)
{
    debug("handle") << m_manager->backend(QString::number(backendIndex))->capabilities();
}

void DBusHandle::requestCompanies(int backendIndex)
{
    m_manager->backend(QString::number(backendIndex))->requestListCompanies();
}

//void DBusHandle::requestLines()
//{
//    QList<Company> companies = m_manager->backend("test")->companies();
//    foreach (Company company, companies) {
//        m_manager->backend("test")->requestListLines(company);
//    }
//}

//void DBusHandle::requestJourneys(const QString &lineName)
//{
//    if (m_manager->backend("test")->companies().count() != 1) {
//        return;
//    }

//    Company company = m_manager->backend("test")->companies().first();
//    QList<Line> lines = m_manager->backend("test")->lines(company);

//    Line foundLine;
//    foreach (Line line, lines) {
//        if (line.name() == lineName) {
//            foundLine = line;
//        }
//    }

//    if (foundLine.name().isEmpty()) {
//        return;
//    }

//    m_manager->backend("test")->requestListJourneys(company, foundLine);
//}

//void DBusHandle::requestStations(const QString &lineName, int journeyIndex)
//{
//    if (m_manager->backend("test")->companies().count() != 1) {
//        return;
//    }

//    Company company = m_manager->backend("test")->companies().first();
//    QList<Line> lines = m_manager->backend("test")->lines(company);
//    Line foundLine;
//    foreach (Line line, lines) {
//        if (line.name() == lineName) {
//            foundLine = line;
//        }
//    }

//    if (foundLine.name().isEmpty()) {
//        return;
//    }

//    QList<Journey> journeys = m_manager->backend("test")->journeys(company, foundLine);
//    if (journeyIndex < 0 || journeyIndex >= journeys.count()) {
//        return;
//    }

//    m_manager->backend("test")->requestListStations(company, foundLine, journeys.at(journeyIndex));
//}

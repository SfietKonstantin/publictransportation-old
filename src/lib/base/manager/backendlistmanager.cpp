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
 * @file backendlistmanager.cpp
 * @short Implementation of PublicTransportation::BackendListManager
 */

#include "backendlistmanager.h"

#include <QtCore/QDir>

#include "backendinfo.h"
#include "debug.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::BackendListManager
 */
struct BackendListManagerPrivate
{
public:
    /**
     * @internal
     * @brief List of backends
     */
    QList<BackendInfo> backendList;
};

////// End of private class //////

BackendListManager::BackendListManager(QObject *parent) :
    QObject(parent), d_ptr(new BackendListManagerPrivate())
{
}

BackendListManager::~BackendListManager()
{
}

QList<BackendInfo> BackendListManager::backendList() const
{
    Q_D(const BackendListManager);
    return d->backendList;
}

void BackendListManager::reload()
{
    Q_D(BackendListManager);
    d->backendList.clear();

    QDir pluginDir = QDir(PLUGIN_FOLDER);
    QStringList nameFilters;
    nameFilters.append("*.desktop");

    foreach (QString file, pluginDir.entryList(nameFilters, QDir::Files)) {
        BackendInfo info (pluginDir.absoluteFilePath(file));
        if (info.isValid()) {
            d->backendList.append(info);
        }
    }

    debug("backend-list-manager") << "Backend list reloaded";
    debug("backend-list-manager") << "Number of backends:" << d->backendList.count();
    emit backendListChanged();
}

}

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

#ifndef PUBLICTRANSPORTATION_BACKENDLISTMANAGER_H
#define PUBLICTRANSPORTATION_BACKENDLISTMANAGER_H

/**
 * @file backendlistmanager.h
 * @short Definition of PublicTransportation::BackendListManager
 */

#include "publictransportation_global.h"

#include <QtCore/QObject>

#include "backendinfo.h"

namespace PublicTransportation
{

class BackendListManagerPrivate;

/**
 * @brief A class to manage available backends
 *
 * This class is used to get a list of the available
 * backends. It reads information from desktop files
 * inside the default folder.
 *
 * Getting the list of backend is done using
 * - reload() that parses the folder containing backends.
 * - backendList() that contains informations about found backends.
 */
class PUBLICTRANSPORTATION_EXPORT BackendListManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit BackendListManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~BackendListManager();
    /**
     * @brief List of backends
     * @return list of backends.
     */
    QList<BackendInfo> backendList() const;
public Q_SLOTS:
    /**
     * @brief Reload
     */
    void reload();
Q_SIGNALS:
    /**
     * @brief Backend list changed
     */
    void backendListChanged();
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<BackendListManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BackendListManager)
};

}

#endif // PUBLICTRANSPORTATION_BACKENDLISTMANAGER_H

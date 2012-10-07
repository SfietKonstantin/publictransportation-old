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

#ifndef PUBLICTRANSPORTATION_DBUSBACKENDMANAGER_H
#define PUBLICTRANSPORTATION_DBUSBACKENDMANAGER_H

/**
 * @file dbusbackendmanager.h
 * @short Definition of PublicTransportation::DBusBackendManager
 */

#include "publictransportation_global.h"
#include "manager/abstractbackendmanager.h"

namespace PublicTransportation
{


/**
 * @brief Backend manager that uses DBus backend wrappers
 *
 * This class simply implements a manager that uses DBus
 * backend wrappers.
 */
class PUBLICTRANSPORTATION_EXPORT DBusBackendManager : public AbstractBackendManager
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit DBusBackendManager(QObject *parent = 0);
    /**
     * @brief Register DBus service
     * @return if the service was successfully registered.
     */
    static bool registerDBusService();
    /**
     * @brief Unregister DBus service
     * @return if the service was successfully unregistered.
     */
    static bool unregisterDBusService();
protected:
    /**
     * @brief Create a backend
     * @param identifier identifier.
     * @param executable executable.
     * @param attributes attributes.
     * @param parent parent.
     * @return created backend.
     */
    virtual AbstractBackendWrapper * createBackend(const QString &identifier,
                                                   const QString &executable,
                                                   const QMap<QString, QString> &attributes,
                                                   QObject *parent = 0) const;
};

}

#endif // PUBLICTRANSPORTATION_DBUSBACKENDMANAGER_H

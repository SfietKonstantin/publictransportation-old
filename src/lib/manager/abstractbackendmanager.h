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

#ifndef PUBLICTRANSPORTATION_ABSTRACTBACKENDMANAGER_H
#define PUBLICTRANSPORTATION_ABSTRACTBACKENDMANAGER_H

/**
 * @file abstractbackendmanager.h
 * @short Definition of PublicTransportation::AbstractBackendManager
 */

#include "publictransportation_global.h"

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include "abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManagerPrivate;

/**
 * @brief Base class for a backend manager
 *
 * This class is used to be a base class for backend management.
 * It can be used to create, launch, stop, kill or remove backends
 * as well as retrieving them.
 *
 * Each backend is identified through an unique identifier. This identifier
 * is typically the identifier that is provided in the backend description
 * desktop file.
 *
 * @section implementation Implementing a backend manager
 *
 * Backend managers are created by implementing createBackend().
 * This method is used to create the correct backend that this
 * class will manage.
 */
class PUBLICTRANSPORTATION_EXPORT AbstractBackendManager: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit AbstractBackendManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~AbstractBackendManager();
    /**
     * @brief Have backend
     *
     * This method is used to check if the backend manager
     * have a backend corresponding to a given identifier.
     *
     * @param identifier identifier.
     * @return if the backend manager have the backend.
     */
    bool haveBackend(const QString &identifier);
    /**
     * @brief Identifiers
     *
     * This method is used to get a list of the identifiers
     * that are associated to backends.
     *
     * @return identifiers.
     */
    QStringList identifiers() const;
    /**
     * @brief Backend
     *
     * This method is used to get the backend associated
     * to a given identifier.
     *
     * @param identifier identifier.
     * @return backend associated to the identifier.
     */
    AbstractBackendWrapper * backend(const QString &identifier) const;
    /**
     * @brief Backends
     *
     * This method is used to get a list of all the backends
     * that are managed.
     *
     * @return a list of all the backends.
     */
    QList<AbstractBackendWrapper *> backends() const;
    /**
     * @brief Add a backend
     *
     * @param identifier identifier.
     * @param executable executable.
     * @param attributes attributes.
     */
    void addBackend(const QString &identifier, const QString &executable,
                    const QMap<QString, QString> &attributes);
    /**
     * @brief Launch a backend
     * @param identifier identifier.
     * @return if the launch is successful.
     */
    bool launchBackend(const QString &identifier);
    /**
     * @brief Stop a backend
     * @param identifier identifier.
     * @return if the stop is successful.
     */
    bool stopBackend(const QString &identifier);
    /**
     * @brief Kill a backend
     * @param identifier identifier.
     * @return if the kill is successful.
     */
    bool killBackend(const QString &identifier);
    /**
     * @brief Remove a backend
     * @param identifier identifier.
     * @return if the remove is successful.
     */
    bool removeBackend(const QString &identifier);
Q_SIGNALS:
    /**
     * @brief Backend added
     * @param identifier identifier.
     * @param backend backend.
     */
    void backendAdded(const QString &identifier, AbstractBackendWrapper *backend);
    /**
     * @brief Backend removed
     * @param identifier identifier.
     */
    void backendRemoved(const QString &identifier);
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
                                                   QObject *parent = 0) const = 0;
    /**
     * @brief D-pointer
     */
    QScopedPointer<AbstractBackendManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractBackendManager)

};

}

#endif // PUBLICTRANSPORTATION_ABSTRACTBACKENDMANAGER_H

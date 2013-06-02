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

#ifndef PT2_ABSTRACTBACKENDMANAGER_H
#define PT2_ABSTRACTBACKENDMANAGER_H

/**
 * @file abstractbackendmanager.h
 * @short Definition of PublicTransportation::AbstractBackendManager
 */

#include "pt2_global.h"

#include <QtCore/QObject>
#include <QtCore/QStringList>

namespace PT2
{

class AbstractBackendWrapper;
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
class PT2_EXPORT AbstractBackendManager: public QObject
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
     * @brief Contains
     *
     * This method is used to check if the backend manager
     * have a backend corresponding to a given identifier.
     *
     * @param identifier identifier.
     * @return if the backend manager have the backend.
     */
    bool contains(const QString &identifier);
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
     */
    void addBackend(const QString &identifier, const QString &executable);
    /**
     * @brief Launch a backend
     * @param identifier identifier.
     * @return if the launch is successful.
     */
    bool launchBackend(const QString &identifier);
    /**
     * @brief Stop a backend
     * @param identifier identifier.
     */
    void stopBackend(const QString &identifier);
    /**
     * @brief Wait for backend to stop
     * @param identifier identifier.
     */
    void waitForBackendToStop(const QString &identifier);
    /**
     * @brief Kill a backend
     * @param identifier identifier.
     */
    void killBackend(const QString &identifier);
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
     * @param parent parent.
     * @return created backend.
     */
    virtual AbstractBackendWrapper * createBackend(const QString &identifier,
                                                   const QString &executable,
                                                   QObject *parent = 0) const = 0;
    /**
     * @brief D-pointer
     */
    QScopedPointer<AbstractBackendManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractBackendManager)

};

}

#endif // PT2_ABSTRACTBACKENDMANAGER_H

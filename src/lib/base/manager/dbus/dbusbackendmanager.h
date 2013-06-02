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

#ifndef PT2_DBUSBACKENDMANAGER_H
#define PT2_DBUSBACKENDMANAGER_H

/**
 * @file dbusbackendmanager.h
 * @short Definition of PT2::DBusBackendManager
 */

#include "pt2_global.h"
#include "manager/abstractbackendmanager.h"

namespace PT2
{


/**
 * @brief Backend manager that uses DBus backend wrappers
 *
 * This class simply implements a manager that uses DBus
 * backend wrappers.
 */
class PT2_EXPORT DBusBackendManager : public AbstractBackendManager
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
     * @param parent parent.
     * @return created backend.
     */
    virtual AbstractBackendWrapper * createBackend(const QString &identifier,
                                                   const QString &executable,
                                                   QObject *parent = 0) const;
};

}

#endif // PT2_DBUSBACKENDMANAGER_H

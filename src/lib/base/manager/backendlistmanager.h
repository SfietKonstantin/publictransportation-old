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

#ifndef PT2_BACKENDLISTMANAGER_H
#define PT2_BACKENDLISTMANAGER_H

/**
 * @file backendlistmanager.h
 * @short Definition of PT2::BackendListManager
 */

#include "pt2_global.h"

#include <QtCore/QObject>

namespace PT2
{

class BackendInfo;
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
class PT2_EXPORT BackendListManager : public QObject
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

#endif // PT2_BACKENDLISTMANAGER_H

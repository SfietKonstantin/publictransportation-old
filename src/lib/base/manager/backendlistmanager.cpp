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

/**
 * @file backendlistmanager.cpp
 * @short Implementation of PT2::BackendListManager
 */

#include "backendlistmanager.h"

#include <QtCore/QDir>

#include "backendinfo.h"
#include "debug.h"

namespace PT2
{

/**
 * @internal
 * @brief Private class for PT2::BackendListManager
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

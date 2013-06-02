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
 * @file abstractbackendmanager.cpp
 * @short Implementation of PT2::AbstractBackendManager
 */

#include "abstractbackendmanager.h"

#include <QtCore/QMap>
#include <QtCore/QDir>

#include "abstractbackendwrapper.h"
#include "debug.h"

namespace PT2
{

/**
 * @internal
 * @brief Private class for PT2::AbstractBackendManager
 */
struct AbstractBackendManagerPrivate
{
    /**
     * @internal
     * @brief Backends
     */
    QMap<QString, AbstractBackendWrapper *> backends;
};

////// End of private class //////

AbstractBackendManager::AbstractBackendManager(QObject *parent):
    QObject(parent), d_ptr(new AbstractBackendManagerPrivate)
{
}

AbstractBackendManager::~AbstractBackendManager()
{
    Q_D(AbstractBackendManager);
    foreach (QString key, d->backends.keys()) {
        stopBackend(key);
        waitForBackendToStop(key);
        killBackend(key);
    }
}

bool AbstractBackendManager::contains(const QString &identifier)
{
    Q_D(const AbstractBackendManager);
    return d->backends.contains(identifier);
}

QStringList AbstractBackendManager::identifiers() const
{
    Q_D(const AbstractBackendManager);
    return d->backends.keys();
}

AbstractBackendWrapper * AbstractBackendManager::backend(const QString &identifier) const
{
    Q_D(const AbstractBackendManager);
    return d->backends.value(identifier, 0);
}

QList<AbstractBackendWrapper *> AbstractBackendManager::backends() const
{
    Q_D(const AbstractBackendManager);
    QList<AbstractBackendWrapper *> wrappers;
    foreach(QString key, d->backends.keys()) {
        if (d->backends.value(key)->status() == AbstractBackendWrapper::Running) {
            wrappers.append(d->backends.value(key));
        }
    }

    return wrappers;
}

void AbstractBackendManager::addBackend(const QString &identifier, const QString &executable)
{
    Q_D(AbstractBackendManager);

    AbstractBackendWrapper *backendWrapper = createBackend(identifier, executable, this);
    d->backends.insert(identifier, backendWrapper);

    emit backendAdded(identifier, backendWrapper);
}

bool AbstractBackendManager::launchBackend(const QString &identifier)
{
    if (!contains(identifier)) {
        return false;
    }

    backend(identifier)->launch();

    return true;
}

void AbstractBackendManager::stopBackend(const QString &identifier)
{
    AbstractBackendWrapper *stoppedBackend = backend(identifier);
    stoppedBackend->stop();
}

void AbstractBackendManager::waitForBackendToStop(const QString &identifier)
{
    AbstractBackendWrapper *stoppedBackend = backend(identifier);
    stoppedBackend->waitForStopped();
}

void AbstractBackendManager::killBackend(const QString &identifier)
{
    AbstractBackendWrapper *killedBackend = backend(identifier);
    killedBackend->kill();
}

bool AbstractBackendManager::removeBackend(const QString &identifier)
{
    Q_D(AbstractBackendManager);
    if (!contains(identifier)) {
        return false;
    }

    AbstractBackendWrapper *removedBackend = backend(identifier);
    if (removedBackend->status() != AbstractBackendWrapper::Stopped) {
        return false;
    }

    d->backends.remove(identifier);
    removedBackend->deleteLater();

    emit backendRemoved(identifier);

    return true;
}

}

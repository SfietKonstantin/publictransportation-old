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
 * @file abstractbackendmanager.cpp
 * @short Implementation of PublicTransportation::AbstractBackendManager
 */

#include "abstractbackendmanager.h"

#include <QtCore/QMap>
#include <QtCore/QDir>

#include "abstractbackendwrapper.h"
#include "debug.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::AbstractBackendManager
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
        if (d->backends.value(key)->status() == AbstractBackendWrapper::Launched) {
            wrappers.append(d->backends.value(key));
        }
    }

    return wrappers;
}

void AbstractBackendManager::addBackend(const QString &identifier, const QString &executable,
                                        const QMap<QString, QString> &attributes)
{
    Q_D(AbstractBackendManager);

    AbstractBackendWrapper *backendWrapper = createBackend(identifier, executable,
                                                           attributes, this);
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

bool AbstractBackendManager::stopBackend(const QString &identifier)
{
    AbstractBackendWrapper *stoppedBackend = backend(identifier);
    stoppedBackend->stop();

    return true;
}

bool AbstractBackendManager::killBackend(const QString &identifier)
{
    AbstractBackendWrapper *killedBackend = backend(identifier);
    killedBackend->kill();

    return true;
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

/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
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
 * @file backendmodel.cpp
 * @short Implementation of PublicTransportation::Gui::BackendModel
 */

#include "backendmodel.h"

#include <QtCore/QSettings>

#include "manager/backendlistmanager.h"
#include "manager/abstractbackendmanager.h"
#include "manager/backendinfo.h"
#include "debug.h"

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @short Private class for PublicTransportation::Gui::BackendModel
 */
class BackendModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    BackendModelPrivate(BackendModel *q);
    /**
     * @internal
     * @brief Status
     * @param backendInfo backend to get the status.
     * @return status of the backend.
     */
    BackendModel::BackendStatus status(const BackendInfo &backendInfo) const;
    /**
     * @internal
     * @brief Slot for status changed
     */
    void slotStatusChanged();
    /**
     * @internal
     * @brief Backend list manager
     */
    BackendListManager *backendListManager;
    /**
     * @internal
     * @brief Backend manager
     */
    AbstractBackendManager *backendManager;
    /**
     * @internal
     * @short Data
     */
    QList<BackendInfo> data;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    BackendModel * const q_ptr;
    Q_DECLARE_PUBLIC(BackendModel)
};

BackendModelPrivate::BackendModelPrivate(BackendModel *q):
    q_ptr(q)
{
    backendManager = 0;
    backendListManager = new BackendListManager(q);
}

BackendModel::BackendStatus BackendModelPrivate::status(const BackendInfo &backendInfo) const
{
    QString identifier = backendInfo.backendIdentifier();

    if (!backendManager->contains(identifier)) {
        return BackendModel::Stopped;
    }

    AbstractBackendWrapper *backendWrapper = backendManager->backend(identifier);
    return (BackendModel::BackendStatus) backendWrapper->status();
}

void BackendModelPrivate::slotStatusChanged()
{
    Q_Q(BackendModel);
    QObject *sender = q->sender();
    AbstractBackendWrapper *backendWrapper = qobject_cast<AbstractBackendWrapper *>(sender);
    if (!backendWrapper) {
        return;
    }

    if (!backendManager) {
        return;
    }

    QString identifier = backendWrapper->identifier();

    int index = -1;
    for (int i = 0; i < data.size(); i++) {
        if (data.at(i).backendIdentifier() == identifier) {
            index = i;
        }
    }

    if (index == -1) {
        return;
    }

    emit q->dataChanged(q->index(index), q->index(index));
}


////// End of private class //////

BackendModel::BackendModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new BackendModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    roles.insert(StatusRole, "status");
    roles.insert(IdentifierRole, "identifier");
    setRoleNames(roles);
}

BackendModel::~BackendModel()
{
}

void BackendModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(BackendModel);
    if (d->backendManager != backendManager) {
        d->backendManager = backendManager;
    }
}

int  BackendModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const BackendModel);
    return d->data.count();
}

int BackendModel::count() const
{
    return rowCount();
}

QVariant BackendModel::data(const QModelIndex &index, int role) const
{
    Q_D(const BackendModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    BackendInfo backendInfo = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return backendInfo.name();
        break;
    case DescriptionRole:
        return backendInfo.description();
        break;
    case StatusRole:
        return d->status(backendInfo);
        break;
    case IdentifierRole:
        return backendInfo.backendIdentifier();
        break;
    default:
        return QVariant();
        break;
    }
}

void BackendModel::reload()
{
    Q_D(BackendModel);
    d->backendListManager->reload();

    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    d->data.clear();
    endRemoveRows();

    QList<BackendInfo> availableBackendList = d->backendListManager->backendList();
    beginInsertRows(QModelIndex(), 0, availableBackendList.count() - 1);
    d->data = availableBackendList;
    endInsertRows();

    debug("backend-model") << "Reloaded information in the model. Number of rows:" << rowCount();

    QSettings settings;
    settings.beginGroup("backend");
    QStringList keys = settings.allKeys();

    foreach (QString key, keys) {
        if (key.startsWith("run-")) {
            QString identifier = key.right(key.size() - 4);
            runBackend(identifier);
        }
    }

    settings.endGroup();
}

void BackendModel::runBackend(const QString &identifier)
{
    Q_D(BackendModel);
    if (!d->backendManager) {
        return;
    }

    if (d->backendManager->contains(identifier)) {
        AbstractBackendWrapper *backend = d->backendManager->backend(identifier);

        if (backend->status() == AbstractBackendWrapper::Stopped) {
            backend->launch();
            return;
        } else {
            backend->kill();
            backend->launch();
            return;
        }
    }

    QMap<QString, BackendInfo> identifierToBackend;
    foreach (BackendInfo backendInfo, d->backendListManager->backendList()) {
        identifierToBackend.insert(backendInfo.backendIdentifier(), backendInfo);
    }

    QSettings settings;
    settings.setValue(QString("backend/run-") + identifier, QVariant(true));

    d->backendManager->addBackend(identifier, identifierToBackend.value(identifier).executable(),
                                  QMap<QString, QString>());

    connect(d->backendManager->backend(identifier), SIGNAL(statusChanged()),
            this, SLOT(slotStatusChanged()));

    d->backendManager->launchBackend(identifier);
}

void BackendModel::stopBackend(const QString &identifier)
{
    Q_D(BackendModel);
    if (!d->backendManager) {
        return;
    }

    if (!d->backendManager->contains(identifier)) {
        return;
    }

    QSettings settings;
    settings.remove(QString("backend/run-") + identifier);
    d->backendManager->stopBackend(identifier);
}

}

}

#include "moc_backendmodel.cpp"

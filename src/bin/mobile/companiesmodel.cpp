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
 * @file companiesmodel.cpp
 * @short Implementation of PublicTransportation::CompaniesModel
 */

#include "companiesmodel.h"

#include <QtCore/QCryptographicHash>

#include "common/capabilitiesconstants.h"
#include "manager/abstractbackendmanager.h"
#include "manager/backendinfo.h"
#include "debug.h"

namespace PublicTransportation
{


/**
 * @internal
 * @short Private class for PublicTransportation::CompaniesModel
 */
class CompaniesModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    CompaniesModelPrivate(CompaniesModel *q);
    void slotBackendAdded(const QString &identifier, AbstractBackendWrapper *backend);
    void slotBackendRemoved(const QString &identifier);
    void slotStatusChanged();
    void slotCompaniesChanged();
    bool needUpdate;
    AbstractBackendManager *backendManager;
    /**
     * @internal
     * @short Data
     */
    QList<Company> data;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    CompaniesModel * const q_ptr;
    Q_DECLARE_PUBLIC(CompaniesModel)
};

CompaniesModelPrivate::CompaniesModelPrivate(CompaniesModel *q):
    q_ptr(q)
{
    backendManager = 0;
    needUpdate = false;
}

void CompaniesModelPrivate::slotBackendAdded(const QString &identifier,
                                             AbstractBackendWrapper *backend)
{
    Q_Q(CompaniesModel);
    Q_UNUSED(identifier)
    QObject::connect(backend, SIGNAL(statusChanged()), q, SLOT(slotStatusChanged()));

    needUpdate = true;
}

void CompaniesModelPrivate::slotBackendRemoved(const QString &identifier)
{
    Q_Q(CompaniesModel);
    Q_UNUSED(identifier)
    needUpdate = true;
}

void CompaniesModelPrivate::slotStatusChanged()
{
    Q_Q(CompaniesModel);
    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(q->sender());
    if (!backend) {
        return;
    }

    if (backend->status() == AbstractBackendWrapper::Launched
        || backend->status() == AbstractBackendWrapper::Stopping) {
        needUpdate = true;
    }
}

void CompaniesModelPrivate::slotCompaniesChanged()
{
    qDebug() << "test";

//    Q_Q(CompaniesModel);
//    QObject *sender = q->sender();
//    AbstractBackendWrapper * backendWrapper = qobject_cast<AbstractBackendWrapper *>(sender);
//    if (!backendWrapper) {
//        return;
//    }

//    if (!loadedBackendWrappers.contains(backendWrapper)) {
//        return;
//    }

//    loadedBackendWrappers.insert(backendWrapper, true);

//    // Everything is loaded
//    if (!loadedBackendWrappers.values().contains(false)) {
//        q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
//        data.clear();
//        q->endRemoveRows();

//        foreach (AbstractBackendWrapper *backendWrapper, loadedBackendWrappers.keys()) {
//            data.append(backendWrapper->companies());
//        }
//        q->beginInsertRows(QModelIndex(), 0, data.count());
//        qSort(data);
//        emit q->countChanged();
//        q->endInsertRows();
//        setLoading(false);
//    }
}

////// End of private class //////

CompaniesModel::CompaniesModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new CompaniesModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    setRoleNames(roles);
}

CompaniesModel::~CompaniesModel()
{
}

void CompaniesModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(CompaniesModel);
    if (d->backendManager != backendManager) {
        if (d->backendManager) {
            d->backendManager->disconnect(this);
        }

        d->backendManager = backendManager;
        connect(d->backendManager, SIGNAL(backendAdded(QString,AbstractBackendWrapper*)),
                this, SLOT(slotBackendAdded(QString,AbstractBackendWrapper*)));
        connect(d->backendManager, SIGNAL(backendRemoved(QString)),
                this, SLOT(slotBackendRemoved(QString)));
    }
}

int  CompaniesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const CompaniesModel);
    return d->data.count();
}

int CompaniesModel::count() const
{
    return rowCount();
}

QVariant CompaniesModel::data(const QModelIndex &index, int role) const
{
    Q_D(const CompaniesModel);
    if (index.row() < 0 or index.row() > rowCount()) {
        return QVariant();
    }
    Company company = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return company .name();
        break;
    default:
        return QVariant();
        break;
    }
}

void CompaniesModel::update()
{
    qDebug() << "update";

    Q_D(CompaniesModel);
    if (!d->backendManager) {
        return;
    }

    foreach (AbstractBackendWrapper *backend, d->backendManager->backends()) {
        if (backend->status() == AbstractBackendWrapper::Launched) {
            if (backend->capabilities().contains(CAPABILITY_LIST_COMPANIES)) {
                disconnect(backend, SIGNAL(capabilitiesChanged()),
                           this, SLOT(slotCompaniesChanged()));
                connect(backend, SIGNAL(companiesChanged()), this, SLOT(slotCompaniesChanged()));
                backend->requestListCompanies();
            }
        }
    }
}

}

#include "moc_companiesmodel.cpp"


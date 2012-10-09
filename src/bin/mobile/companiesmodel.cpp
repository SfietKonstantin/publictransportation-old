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
    enum UpdateStatus {
        NeedUpdate,
        Updating,
        Updated
    };

    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    CompaniesModelPrivate(CompaniesModel *q);
    void checkUpdating();
    void slotBackendAdded(const QString &identifier, AbstractBackendWrapper *backend);
    void slotBackendRemoved(const QString &identifier);
    void slotStatusChanged();
    void slotCompaniesChanged();
    void update();
    AbstractBackendManager *backendManager;
    /**
     * @internal
     * @short Data
     */
    QList<Company> data;
    QMap<Company, QString> backendFromCompany;
    bool updating;
    QMap<QString, UpdateStatus> updateTrackerMap;
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
    updating = false;
}

void CompaniesModelPrivate::checkUpdating()
{
    Q_Q(CompaniesModel);
    bool currentUpdating = false;
    foreach (QString identifier, updateTrackerMap.keys()) {
        if (updateTrackerMap.value(identifier) != Updated) {
            currentUpdating = true;
        }
    }

    if (updating != currentUpdating) {
        updating = currentUpdating;

        update();

        emit q->updatingChanged();
    }
}

void CompaniesModelPrivate::slotBackendAdded(const QString &identifier,
                                             AbstractBackendWrapper *backend)
{
    Q_Q(CompaniesModel);
    Q_UNUSED(identifier)
    QObject::connect(backend, SIGNAL(statusChanged()), q, SLOT(slotStatusChanged()));
    QObject::connect(backend, SIGNAL(companiesChanged()), q, SLOT(slotCompaniesChanged()));

    updateTrackerMap.insert(identifier, NeedUpdate);
    checkUpdating();
}

void CompaniesModelPrivate::slotBackendRemoved(const QString &identifier)
{
    Q_UNUSED(identifier)
    updateTrackerMap.remove(identifier);
    update();
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

        QString identifier = backend->identifier();
        if (updateTrackerMap.value(identifier) == NeedUpdate) {
            backend->requestListCompanies();
            updateTrackerMap.insert(identifier, Updating);
            checkUpdating();
        } else {
            update();
        }
    }
}

void CompaniesModelPrivate::slotCompaniesChanged()
{
    Q_Q(CompaniesModel);
    QObject *sender = q->sender();
    AbstractBackendWrapper * backend = qobject_cast<AbstractBackendWrapper *>(sender);
    if (!backend) {
        return;
    }

    QString identifier = backend->identifier();
    if (!updateTrackerMap.contains(identifier)) {
        return;
    }

    updateTrackerMap.insert(identifier, Updated);
    checkUpdating();
}

void CompaniesModelPrivate::update()
{
    Q_Q(CompaniesModel);

    q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
    data.clear();
    backendFromCompany.clear();
    q->endRemoveRows();

    foreach (AbstractBackendWrapper *backend, backendManager->backends()) {
        if (backend->status() == AbstractBackendWrapper::Launched) {
            data.append(backend->companies());
            foreach(Company company, backend->companies()) {
                backendFromCompany.insert(company, backend->identifier());
            }
        }
    }

    if (data.count() != 0) {
        q->beginInsertRows(QModelIndex(), 0, data.count() - 1);
        qSort(data);
        emit q->countChanged();
        q->endInsertRows();
    }
}

////// End of private class //////

CompaniesModel::CompaniesModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new CompaniesModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
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

bool CompaniesModel::isUpdating() const
{
    Q_D(const CompaniesModel);
    return d->updating;
}

int CompaniesModel::count() const
{
    return rowCount();
}

QVariant CompaniesModel::data(const QModelIndex &index, int role) const
{
    Q_D(const CompaniesModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    Company company = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return company.name();
        break;
    case DescriptionRole:
        return company.properties().value("description").toString();
        break;
    default:
        return QVariant();
        break;
    }
}

void CompaniesModel::requestCompany(int index)
{
    Q_D(const CompaniesModel);
    if (index < 0 or index >= rowCount()) {
        return;
    }
    Company company = d->data.at(index);
    QString identifier = d->backendFromCompany.value(company);

    emit displayLines(identifier, company);
}

}

#include "moc_companiesmodel.cpp"


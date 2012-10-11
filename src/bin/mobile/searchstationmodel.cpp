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
 * @short Implementation of PublicTransportation::BackendModel
 */

#include "searchstationmodel.h"

#include "common/capabilitiesconstants.h"
#include "manager/abstractbackendmanager.h"
#include "debug.h"

namespace PublicTransportation
{


/**
 * @internal
 * @short Private class for PublicTransportation::SearchStationModel
 */
class SearchStationModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    SearchStationModelPrivate(SearchStationModel *q);
    void slotBackendAdded(const QString &identifier, AbstractBackendWrapper *backend);
    void slotStatusChanged();
    void slotErrorRegistered(const QString &request, const QString &errorString);
    void slotSuggestedStationsRegistered(const QString & request,
                                         const QList<PublicTransportation::Station> &stations);
    /**
     * @internal
     * @brief Backend manager
     */
    AbstractBackendManager *backendManager;
    QList<PublicTransportation::Station> data;
    QList<QString> requests;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    SearchStationModel * const q_ptr;
    Q_DECLARE_PUBLIC(SearchStationModel)
};

SearchStationModelPrivate::SearchStationModelPrivate(SearchStationModel *q):
    q_ptr(q)
{
    backendManager = 0;
}

void SearchStationModelPrivate::slotBackendAdded(const QString &identifier,
                                                 AbstractBackendWrapper *backend)
{
    Q_UNUSED(identifier)
    Q_Q(SearchStationModel);
    q->connect(backend, SIGNAL(statusChanged()), q, SLOT(slotStatusChanged()));
}

void SearchStationModelPrivate::slotStatusChanged()
{
    Q_Q(SearchStationModel);
    QObject *sender = q->sender();
    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(sender);
    if (!backend) {
        return;
    }

    if (backend->status() == AbstractBackendWrapper::Launched) {
        q->connect(backend,
                   SIGNAL(suggestedStationsRegistered(QString,
                                                      QList<PublicTransportation::Station>)),
                   q, SLOT(slotSuggestedStationsRegistered(QString,
                                                           QList<PublicTransportation::Station>)));
        q->connect(backend, SIGNAL(errorRegistered(QString,QString)),
                   q, SLOT(slotErrorRegistered(QString,QString)));
    }

    if (backend->status() == AbstractBackendWrapper::Stopping) {
        q->disconnect(backend,
                      SIGNAL(suggestedStationsRegistered(QString,
                                                         QList<PublicTransportation::Station>)),
                      q,
                      SLOT(slotSuggestedStationsRegistered(QString,
                                                           QList<PublicTransportation::Station>)));
        q->disconnect(backend, SIGNAL(errorRegistered(QString,QString)),
                      q, SLOT(slotErrorRegistered(QString,QString)));
    }
}

void SearchStationModelPrivate::slotErrorRegistered(const QString &request,
                                                    const QString &errorString)
{
    Q_UNUSED(errorString)
    Q_Q(SearchStationModel);
    requests.removeAll(request);
    if (requests.isEmpty()) {
        emit q->updatingChanged();
    }
}

void SearchStationModelPrivate::slotSuggestedStationsRegistered(const QString & request,
                                                                const QList<Station> &stations)
{
    Q_Q(SearchStationModel);
    if (!requests.contains(request)) {
        return;
    }

    requests.removeAll(request);
    if (requests.isEmpty()) {
        emit q->updatingChanged();
    }

    QList<Station> addedStations;
    foreach (Station station, stations) {
        if (!data.contains(station)) {
            addedStations.append(station);
        }
    }

    q->beginInsertRows(QModelIndex(), q->rowCount(), q->rowCount() + addedStations.count() - 1);
    data.append(addedStations);
    emit q->countChanged();
    q->endInsertRows();
}


////// End of private class //////

SearchStationModel::SearchStationModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new SearchStationModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(ProviderNameRole, "providerName");
    setRoleNames(roles);
}

SearchStationModel::~SearchStationModel()
{
}

void SearchStationModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(SearchStationModel);
    if (d->backendManager != backendManager) {

        if (d->backendManager) {
            disconnect(d->backendManager, SIGNAL(backendAdded(QString,AbstractBackendWrapper*)),
                       this, SLOT(slotBackendAdded(QString,AbstractBackendWrapper*)));
        }

        connect(backendManager, SIGNAL(backendAdded(QString,AbstractBackendWrapper*)),
                this, SLOT(slotBackendAdded(QString,AbstractBackendWrapper*)));

        d->backendManager = backendManager;
    }
}

int SearchStationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const SearchStationModel);
    return d->data.count();
}

bool SearchStationModel::isUpdating() const
{
    Q_D(const SearchStationModel);
    return !d->requests.isEmpty();
}

int SearchStationModel::count() const
{
    return rowCount();
}

QVariant SearchStationModel::data(const QModelIndex &index, int role) const
{
    Q_D(const SearchStationModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    Station data = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return data.name();
        break;
    case ProviderNameRole:
        return data.properties().value("providerName");
        break;
    default:
        return QVariant();
        break;
    }
}

void SearchStationModel::search(const QString &partialStation)
{
    Q_D(SearchStationModel);

    clear();

    foreach (AbstractBackendWrapper *backend, d->backendManager->backends()) {
        if (!backend->capabilities().contains(SUGGEST_STATIONS)) {
            break;
        }
        QString request = backend->requestSuggestStations(partialStation);
        d->requests.append(request);
    }

    emit updatingChanged();
}

void SearchStationModel::clear()
{
    Q_D(SearchStationModel);

    d->requests.clear();
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

    d->data.clear();

    emit countChanged();
    endRemoveRows();
}

}

#include "moc_searchstationmodel.cpp"

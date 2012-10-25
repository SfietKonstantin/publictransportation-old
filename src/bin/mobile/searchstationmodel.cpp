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
 * @file searchstationmodel.cpp
 * @short Implementation of PublicTransportation::Gui::SearchStationModel
 */

#include "searchstationmodel.h"

#include "common/capabilitiesconstants.h"
#include "common/station.h"
#include "manager/abstractbackendmanager.h"
#include "debug.h"
#include "favouritemanager.h"

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::Gui::SearchStationModel
 */
struct SearchStationModelItem
{
    /**
     * @internal
     * @brief Station
     */
    Station station;
    /**
     * @internal
     * @brief Backend identifier
     */
    QString backendIdentifier;
    /**
     * @internal
     * @brief If the backend support journeys from station
     */
    bool supportJourneysFromStation;
    bool favourite;
};

/**
 * @internal
 * @short Private class for PublicTransportation::Gui::SearchStationModel
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
    void displayFavourites();
    /**
     * @internal
     * @brief Slot backend added
     * @param identifier identifier.
     * @param backend backend.
     */
    void slotBackendAdded(const QString &identifier, AbstractBackendWrapper *backend);
    /**
     * @internal
     * @brief Slot status changed
     */
    void slotStatusChanged();
    /**
     * @internal
     * @brief Slot error registered
     * @param request request identifier.
     * @param errorId error identifier.
     * @param errorString error string.
     */
    void slotErrorRegistered(const QString &request, const QString &errorId,
                             const QString &errorString);
    /**
     * @internal
     * @brief Slot suggested stations registered
     * @param request request identifier.
     * @param stations stations.
     */
    void slotSuggestedStationsRegistered(const QString & request,
                                         const QList<PublicTransportation::Station> &stations);
    /**
     * @internal
     * @brief Backend manager
     */
    AbstractBackendManager *backendManager;
    FavouriteManager *favouriteManager;
    /**
     * @internal
     * @brief Data
     */
    QList<SearchStationModelItem *> data;
    /**
     * @internal
     * @brief Requests
     */
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
    favouriteManager = 0;
}

void SearchStationModelPrivate::displayFavourites()
{
    Q_Q(SearchStationModel);

    if (!favouriteManager) {
        return;
    }

    if (!backendManager) {
        return;
    }

    bool dataOk = true;
    foreach (SearchStationModelItem *item, data) {
        if (!item->favourite) {
            dataOk = false;
            break;
        }
    }

    if (!dataOk) {
        return;
    }

    if (!data.isEmpty()) {
        q->clear();
    }

    QListIterator<QPair<QString, Station> > iterator
            = QListIterator<QPair<QString, Station> >(favouriteManager->favourites());
    while (iterator.hasNext()) {
        QPair<QString, Station> entry = iterator.next();
        QString identifier = entry.first;
        Station station = entry.second;

        if (backendManager->contains(identifier)) {
            AbstractBackendWrapper *backend = backendManager->backend(identifier);

            if (backend->status() == AbstractBackendWrapper::Launched) {
                SearchStationModelItem *item = new SearchStationModelItem;
                item->station = station;
                item->backendIdentifier = identifier;
                item->supportJourneysFromStation
                        = backend->capabilities().contains(JOURNEYS_FROM_STATION);
                item->favourite = true;
                data.append(item);
            }
        }
    }

    q->beginInsertRows(QModelIndex(), 0, data.count() - 1);
    emit q->countChanged();
    q->endInsertRows();
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
        q->connect(backend, SIGNAL(errorRegistered(QString,QString,QString)),
                   q, SLOT(slotErrorRegistered(QString,QString,QString)));
        displayFavourites();
    }

    if (backend->status() == AbstractBackendWrapper::Stopping) {
        q->disconnect(backend,
                      SIGNAL(suggestedStationsRegistered(QString,
                                                         QList<PublicTransportation::Station>)),
                      q,
                      SLOT(slotSuggestedStationsRegistered(QString,
                                                           QList<PublicTransportation::Station>)));
        q->disconnect(backend, SIGNAL(errorRegistered(QString,QString,QString)),
                      q, SLOT(slotErrorRegistered(QString,QString,QString)));
        displayFavourites();
    }
}

void SearchStationModelPrivate::slotErrorRegistered(const QString &request,
                                                    const QString &errorId,
                                                    const QString &errorString)
{
    Q_UNUSED(errorId)
    Q_UNUSED(errorString)
    Q_Q(SearchStationModel);
    requests.removeAll(request);
    if (requests.isEmpty()) {
        emit q->loadingChanged();
    }
}

void SearchStationModelPrivate::slotSuggestedStationsRegistered(const QString & request,
                                                                const QList<Station> &stations)
{
    Q_Q(SearchStationModel);
    if (!requests.contains(request)) {
        return;
    }

    QObject *sender = q->sender();
    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(sender);
    if (!backend) {
        return;
    }

    requests.removeAll(request);
    if (requests.isEmpty()) {
        emit q->loadingChanged();
    }

    QList<SearchStationModelItem *> addedData;
    foreach (Station station, stations) {
        bool found = false;
        foreach(SearchStationModelItem *dataItem, data) {
            if (dataItem->station == station) {
                found = true;
            }
        }

        if (!found) {
            SearchStationModelItem *dataItem = new SearchStationModelItem;
            dataItem->station = station;
            dataItem->backendIdentifier = backend->identifier();
            dataItem->supportJourneysFromStation
                    = backend->capabilities().contains(JOURNEYS_FROM_STATION);
            dataItem->favourite = false;
            addedData.append(dataItem);
        }
    }

    q->beginInsertRows(QModelIndex(), q->rowCount(), q->rowCount() + addedData.count() - 1);
    data.append(addedData);
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
    roles.insert(SupportJourneysFromStationRole, "supportJourneysFromStation");
    roles.insert(ProviderNameRole, "providerName");
    roles.insert(FavouriteRole, "favourite");
    setRoleNames(roles);
}

SearchStationModel::~SearchStationModel()
{
    clear();
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

    d->displayFavourites();
}

void SearchStationModel::setFavouriteManager(FavouriteManager *favouriteManager)
{
    Q_D(SearchStationModel);
    if (d->favouriteManager != favouriteManager) {
        d->favouriteManager = favouriteManager;
        connect(d->favouriteManager, SIGNAL(favouritesChanged()), this, SLOT(displayFavourites()));
    }

    d->displayFavourites();
}

int SearchStationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const SearchStationModel);
    return d->data.count();
}

bool SearchStationModel::isLoading() const
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
    SearchStationModelItem *data = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return data->station.name();
        break;
    case SupportJourneysFromStationRole:
        return data->supportJourneysFromStation;
        break;
    case ProviderNameRole:
        return data->station.properties().value("backendName", QString());
        break;
    case FavouriteRole:
        return data->favourite;
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

    QString partialStationTrimmed = partialStation.trimmed();
    if (partialStationTrimmed.isEmpty()) {
        d->displayFavourites();
        return;
    }

    foreach (AbstractBackendWrapper *backend, d->backendManager->backends()) {
        if (backend->capabilities().contains(SUGGEST_STATIONS)) {
            QString request = backend->requestSuggestStations(partialStationTrimmed);
            d->requests.append(request);
        }
    }

    emit loadingChanged();
}

void SearchStationModel::reset()
{
    Q_D(SearchStationModel);
    clear();
    d->displayFavourites();
}

void SearchStationModel::clear()
{
    Q_D(SearchStationModel);

    d->requests.clear();
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);

    while (!d->data.isEmpty()) {
        delete d->data.takeFirst();
    }

    emit countChanged();
    endRemoveRows();
}

void SearchStationModel::requestJourneysFromStation(int index)
{
    Q_D(SearchStationModel);
    if (index < 0 || index >= rowCount()) {
        return;
    }

    SearchStationModelItem *data = d->data.at(index);

    if (!data->supportJourneysFromStation) {
        return;
    }

    if (!d->backendManager) {
        return;
    }

    QString backendIdentifier = data->backendIdentifier;
    if (!d->backendManager->contains(backendIdentifier)) {
        return;
    }

    AbstractBackendWrapper *backend = d->backendManager->backend(backendIdentifier);

    QString request = backend->requestJourneysFromStation(data->station, 20);
    emit journeysFromStationRequested(backend, request, data->station);
}

}

}

#include "moc_searchstationmodel.cpp"

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
 * @file stationsfromjourneymodel.cpp
 * @short Implementation of PublicTransportation::Gui::StationsFromJourneyModel
 */

#include "stationsfromjourneymodel.h"

#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/waitingtime.h"
#include "manager/abstractbackendmanager.h"
#include "manager/abstractbackendwrapper.h"
#include "debug.h"

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::Gui::StationsFromJourneyModel
 */
struct StationsFromJourneyModelItem
{
    /**
     * @internal
     * @brief Station
     */
    Station station;
};

/**
 * @internal
 * @short Private class for PublicTransportation::StationsFromJourneyModel
 */
class StationsFromJourneyModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    StationsFromJourneyModelPrivate(StationsFromJourneyModel *q);
    /**
     * @brief Slot stations from journey registered
     * @param request request identifier.
     * @param stationList a list of stations.
     */
    void slotStationsFromJourneyRegistered(const QString &request,
                                           const QList<PublicTransportation::Station> &stationList);
    /**
     * @internal
     * @brief Backend list manager
     */
    AbstractBackendManager *backendManager;
    /**
     * @internal
     * @brief Backend identifier
     */
    QString backendIdentifier;
    /**
     * @internal
     * @brief Company
     */
    Company company;
    /**
     * @internal
     * @brief Line
     */
    Line line;
    /**
     * @internal
     * @brief Journey
     */
    Journey journey;
    /**
     * @internal
     * @brief Station
     */
    Station station;
    /**
     * @internal
     * @brief Current request
     */
    QString currentRequest;
    /**
     * @internal
     * @brief Data
     */
    QList<StationsFromJourneyModelItem *> data;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    StationsFromJourneyModel * const q_ptr;
    Q_DECLARE_PUBLIC(StationsFromJourneyModel)
};

StationsFromJourneyModelPrivate::StationsFromJourneyModelPrivate(StationsFromJourneyModel *q):
    q_ptr(q)
{
    backendManager = 0;
}

void StationsFromJourneyModelPrivate::slotStationsFromJourneyRegistered(const QString &request,
                                                                  const QList<Station> &stationList)
{
    Q_Q(StationsFromJourneyModel);
    if (currentRequest != request) {
        return;
    }

    q->clear();

    foreach (Station station, stationList) {
        StationsFromJourneyModelItem * dataItem = new StationsFromJourneyModelItem;
        dataItem->station = station;
        data.append(dataItem);
    }

    q->beginInsertRows(QModelIndex(), 0, data.count() - 1);
    emit q->countChanged();
    q->endInsertRows();

    currentRequest = QString();
    emit q->loadingChanged();
}


////// End of private class //////

StationsFromJourneyModel::StationsFromJourneyModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new StationsFromJourneyModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(StationRole, "station");
    setRoleNames(roles);
}

StationsFromJourneyModel::~StationsFromJourneyModel()
{
}

void StationsFromJourneyModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(StationsFromJourneyModel);
    if (d->backendManager != backendManager) {
        d->backendManager = backendManager;
    }
}

int StationsFromJourneyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const StationsFromJourneyModel);
    return d->data.count();
}

bool StationsFromJourneyModel::isLoading() const
{
    Q_D(const StationsFromJourneyModel);
    return !d->currentRequest.isNull();
}

int StationsFromJourneyModel::count() const
{
    return rowCount();
}

QVariant StationsFromJourneyModel::data(const QModelIndex &index, int role) const
{
    Q_D(const StationsFromJourneyModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    StationsFromJourneyModelItem *data = d->data.at(index.row());

    switch(role) {
    case StationRole:
        return data->station.name();
        break;
    default:
        return QVariant();
        break;
    }
}

void StationsFromJourneyModel::load(AbstractBackendWrapper *backend, const QString &request,
                                    const Company &company, const Line &line,
                                    const Journey &journey, const Station &station)
{
    Q_D(StationsFromJourneyModel);
    connect(backend,
            SIGNAL(stationsFromJourneyRegistered(QString,QList<PublicTransportation::Station>)),
            this,
            SLOT(slotStationsFromJourneyRegistered(QString,QList<PublicTransportation::Station>)));
    d->backendIdentifier = backend->identifier();
    d->company = company;
    d->line = line;
    d->journey = journey;
    d->station = station;
    d->currentRequest = request;
    emit loadingChanged();

    clear();
}

void StationsFromJourneyModel::clear()
{
    Q_D(StationsFromJourneyModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    while (!d->data.isEmpty()) {
        delete d->data.takeFirst();
    }
    emit countChanged();
    endRemoveRows();
}

}

}

#include "moc_stationsfromjourneymodel.cpp"

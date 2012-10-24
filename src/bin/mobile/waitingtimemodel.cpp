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
 * @file waitingtimemodel.cpp
 * @short Implementation of PublicTransportation::Gui::WaitingTimeModel
 */

#include "waitingtimemodel.h"

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
 * @brief Private class used in PublicTransportation::Gui::WaitingTimeModel
 */
struct WaitingTimeModelData
{
    /**
     * @internal
     * @brief Waiting time
     */
    WaitingTime waitingTime;
};

/**
 * @internal
 * @short Private class for PublicTransportation::BackendModel
 */
class WaitingTimeModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    WaitingTimeModelPrivate(WaitingTimeModel *q);
    /**
     * @brief Slot waiting time registered
     * @param request request.
     * @param waitingTimeList waiting time list.
     */
    void slotWaitingTimeRegistered(const QString &request,
                                   const QList<PublicTransportation::WaitingTime> &waitingTimeList);
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
    QList<WaitingTimeModelData *> data;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    WaitingTimeModel * const q_ptr;
    Q_DECLARE_PUBLIC(WaitingTimeModel)
};

WaitingTimeModelPrivate::WaitingTimeModelPrivate(WaitingTimeModel *q):
    q_ptr(q)
{
    backendManager = 0;
}

void WaitingTimeModelPrivate::slotWaitingTimeRegistered(const QString &request,
                                                        const QList<WaitingTime> &waitingTimeList)
{
    Q_Q(WaitingTimeModel);
    if (currentRequest != request) {
        return;
    }

    q->clear();

    foreach (WaitingTime waitingTime, waitingTimeList) {
        WaitingTimeModelData * dataItem = new WaitingTimeModelData;
        dataItem->waitingTime = waitingTime;
        data.append(dataItem);
    }

    q->beginInsertRows(QModelIndex(), 0, data.count() - 1);
    emit q->countChanged();
    q->endInsertRows();

    currentRequest = QString();
    emit q->loadingChanged();
}


////// End of private class //////

WaitingTimeModel::WaitingTimeModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new WaitingTimeModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(WaitingTimeRole, "waitingTime");
    roles.insert(DestinationRole, "destination");
    setRoleNames(roles);
}

WaitingTimeModel::~WaitingTimeModel()
{
}

void WaitingTimeModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(WaitingTimeModel);
    if (d->backendManager != backendManager) {
        d->backendManager = backendManager;
    }
}

int WaitingTimeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const WaitingTimeModel);
    return d->data.count();
}

bool WaitingTimeModel::isLoading() const
{
    Q_D(const WaitingTimeModel);
    return !d->currentRequest.isNull();
}

int WaitingTimeModel::count() const
{
    return rowCount();
}

QVariant WaitingTimeModel::data(const QModelIndex &index, int role) const
{
    Q_D(const WaitingTimeModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    WaitingTimeModelData *data = d->data.at(index.row());

    switch(role) {
    case WaitingTimeRole:
        return data->waitingTime.waitingTime();
        break;
    case DestinationRole:
        return data->waitingTime.properties().value("destination");
        break;
    default:
        return QVariant();
        break;
    }
}

void WaitingTimeModel::load(AbstractBackendWrapper *backend, const QString &request,
                            const Company &company, const Line &line,
                            const Journey &journey, const Station &station)
{
    Q_D(WaitingTimeModel);
    connect(backend,
            SIGNAL(waitingTimeRegistered(QString,QList<PublicTransportation::WaitingTime>)),
            this,
            SLOT(slotWaitingTimeRegistered(QString,QList<PublicTransportation::WaitingTime>)));
    d->backendIdentifier = backend->identifier();
    d->company = company;
    d->line = line;
    d->journey = journey;
    d->station = station;
    d->currentRequest = request;
    emit loadingChanged();

    clear();
}

void WaitingTimeModel::reload()
{
    Q_D(WaitingTimeModel);

    if (d->backendIdentifier.isEmpty()) {
        return;
    }

    if (d->company.isNull() || d->line.isNull() || d->journey.isNull() || d->station.isNull()) {
        return;
    }

    AbstractBackendWrapper *backend = d->backendManager->backend(d->backendIdentifier);

    d->currentRequest = backend->requestWaitingTime(d->company, d->line, d->journey, d->station);
    emit loadingChanged();
}

void WaitingTimeModel::clear()
{
    Q_D(WaitingTimeModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    while (!d->data.isEmpty()) {
        delete d->data.takeFirst();
    }
    emit countChanged();
    endRemoveRows();
}

}

}

#include "moc_waitingtimemodel.cpp"

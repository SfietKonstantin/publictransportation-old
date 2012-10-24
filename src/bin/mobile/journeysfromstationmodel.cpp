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
 * @file journeysfromstationmodel.cpp
 * @short Implementation of PublicTransportation::Gui::JourneysFromStationModel
 */

#include "journeysfromstationmodel.h"

#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/infojourneys.h"
#include "common/capabilitiesconstants.h"
#include "manager/abstractbackendwrapper.h"
#include "manager/abstractbackendmanager.h"
#include "debug.h"

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::Gui::JourneysFromStationModel
 */
struct JourneysFromStationsModelData
{
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
     * @brief If the backend support waiting time
     */
    bool supportWaitingTime;
};

/**
 * @internal
 * @short Private class for PublicTransportation::Gui::JourneysFromStationModel
 */
class JourneysFromStationModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    JourneysFromStationModelPrivate(JourneysFromStationModel *q);
    /**
     * @internal
     * @brief Slot journeys registered
     * @param request request.
     * @param infoJourneys informations about journey.
     */
    void slotJourneysRegistered(const QString &request,
                                const QList<PublicTransportation::InfoJourneys> &infoJourneys);
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
    QList<JourneysFromStationsModelData *> data;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    JourneysFromStationModel * const q_ptr;
    Q_DECLARE_PUBLIC(JourneysFromStationModel)
};

JourneysFromStationModelPrivate::JourneysFromStationModelPrivate(JourneysFromStationModel *q):
    q_ptr(q)
{
    backendManager = 0;
}

void JourneysFromStationModelPrivate::slotJourneysRegistered(const QString &request,
                                                             const QList<InfoJourneys> &infoJourneys)
{
    Q_Q(JourneysFromStationModel);
    if (currentRequest != request) {
        return;
    }

    q->clear();

    QObject *sender = q->sender();
    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(sender);
    if (!backend) {
        return;
    }

    foreach (InfoJourneys info, infoJourneys) {
        Line line = info.line();
        Company company = info.company();
        QPair<Journey, Station> journeyStation;
        foreach (journeyStation, info.journeysAndStations()) {
            JourneysFromStationsModelData * dataItem = new JourneysFromStationsModelData;
            dataItem->company = company;
            dataItem->line = line;
            dataItem->journey = journeyStation.first;
            dataItem->station = journeyStation.second;
            dataItem->supportWaitingTime = backend->capabilities().contains(WAITING_TIME);
            data.append(dataItem);
        }
    }

    q->beginInsertRows(QModelIndex(), 0, data.count() - 1);
    emit q->countChanged();
    q->endInsertRows();

    currentRequest = QString();
    emit q->loadingChanged();
}


////// End of private class //////

JourneysFromStationModel::JourneysFromStationModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new JourneysFromStationModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(LineRole, "line");
    roles.insert(CompanyRole, "company");
    roles.insert(StationRole, "station");
    roles.insert(SupportWaitingTimeRole, "supportWaitingTime");
    setRoleNames(roles);
}

JourneysFromStationModel::~JourneysFromStationModel()
{
}

void JourneysFromStationModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(JourneysFromStationModel);
    if (d->backendManager != backendManager) {
        d->backendManager = backendManager;
    }
}

int JourneysFromStationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const JourneysFromStationModel);
    return d->data.count();
}

bool JourneysFromStationModel::isLoading() const
{
    Q_D(const JourneysFromStationModel);
    return !d->currentRequest.isNull();
}

int JourneysFromStationModel::count() const
{
    return rowCount();
}

QVariant JourneysFromStationModel::data(const QModelIndex &index, int role) const
{
    Q_D(const JourneysFromStationModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    JourneysFromStationsModelData *data = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return data->journey.name();
        break;
    case LineRole:
        return data->line.name();
        break;
    case CompanyRole:
        return data->company.name();
        break;
    case StationRole:
        return data->station.name();
        break;
    case SupportWaitingTimeRole:
        return data->supportWaitingTime;
        break;
    default:
        return QVariant();
        break;
    }
}

void JourneysFromStationModel::load(AbstractBackendWrapper *backend, const QString &request,
                                    const Station &station)
{
    Q_D(JourneysFromStationModel);
    connect(backend,
            SIGNAL(journeysFromStationRegistered(QString,
                                                 QList<PublicTransportation::InfoJourneys>)),
            this, SLOT(slotJourneysRegistered(QString,QList<PublicTransportation::InfoJourneys>)));
    d->backendIdentifier = backend->identifier();
    d->station = station;
    d->currentRequest = request;
    emit loadingChanged();

    clear();
}

void JourneysFromStationModel::reload()
{
    Q_D(JourneysFromStationModel);

    if (d->backendIdentifier.isEmpty()) {
        return;
    }

    if (d->station.isNull()) {
        return;
    }

    AbstractBackendWrapper *backend = d->backendManager->backend(d->backendIdentifier);

    d->currentRequest = backend->requestJourneysFromStation(d->station, 20);
    emit loadingChanged();
}

void JourneysFromStationModel::requestWaitingTime(int index)
{
    Q_D(JourneysFromStationModel);
    if (index < 0 || index >= rowCount()) {
        return;
    }

    JourneysFromStationsModelData *data = d->data.at(index);

    if (!data->supportWaitingTime) {
        return;
    }

    if (!d->backendManager) {
        return;
    }

    QString backendIdentifier = d->backendIdentifier;
    if (!d->backendManager->contains(backendIdentifier)) {
        return;
    }

    AbstractBackendWrapper *backend = d->backendManager->backend(backendIdentifier);

    QString request = backend->requestWaitingTime(data->company, data->line,
                                                  data->journey, data->station);
    emit waitingTimeRequested(backend, request, data->company, data->line, data->journey,
                              data->station);
}

void JourneysFromStationModel::clear()
{
    Q_D(JourneysFromStationModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    while (!d->data.isEmpty()) {
        delete d->data.takeFirst();
    }
    emit countChanged();
    endRemoveRows();
}

}

}

#include "moc_journeysfromstationmodel.cpp"

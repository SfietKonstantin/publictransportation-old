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

#include "favouritemanager.h"

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::Gui::JourneysFromStationModel
 */
struct JourneysFromStationsModelItem
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
    /**
     * @internal
     * @brief If the backend support stations from journey
     */
    bool supportStationsFromJourney;

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
     * @brief Update favourite
     */
    void updateFavourite();
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
     * @brief If this station is favourite
     */
    bool favourite;
    /**
     * @internal
     * @brief Favourite manager
     */
    FavouriteManager *favouriteManager;
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
    QList<JourneysFromStationsModelItem *> data;
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
    favourite = false;
    favouriteManager = 0;
}

void JourneysFromStationModelPrivate::updateFavourite()
{
    Q_Q(JourneysFromStationModel);
    if (!favouriteManager) {
        return;
    }
    bool newFavourite = favouriteManager->isFavourite(backendIdentifier, station);
    if (favourite != newFavourite) {
        favourite = newFavourite;
        emit q->favouriteChanged();
    }
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
            JourneysFromStationsModelItem * dataItem = new JourneysFromStationsModelItem;
            dataItem->company = company;
            dataItem->line = line;
            dataItem->journey = journeyStation.first;
            dataItem->station = journeyStation.second;
            dataItem->supportWaitingTime = backend->capabilities().contains(WAITING_TIME);
            dataItem->supportStationsFromJourney
                    = backend->capabilities().contains(STATIONS_FROM_JOURNEY);
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
    roles.insert(SupportStationsFromJourneyRole, "supportStationsFromJourney");
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

void JourneysFromStationModel::setFavouriteManager(FavouriteManager *favouriteManager)
{
    Q_D(JourneysFromStationModel);
    if (d->favouriteManager != favouriteManager) {
        d->favouriteManager = favouriteManager;
    }
    d->updateFavourite();
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

bool JourneysFromStationModel::isFavourite() const
{
    Q_D(const JourneysFromStationModel);
    return d->favourite;
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
    JourneysFromStationsModelItem *data = d->data.at(index.row());

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
    case SupportStationsFromJourneyRole:
        return data->supportStationsFromJourney;
        break;
    default:
        return QVariant();
        break;
    }
}

void JourneysFromStationModel::setFavourite(bool favourite)
{
    Q_D(JourneysFromStationModel);
    if (!d->favouriteManager) {
        return;
    }

    if (favourite) {
        d->favouriteManager->addStation(d->backendIdentifier, d->station);
    } else {
        d->favouriteManager->removeStation(d->backendIdentifier, d->station);
    }
    d->updateFavourite();
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

    d->updateFavourite();

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

    JourneysFromStationsModelItem *data = d->data.at(index);

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

void JourneysFromStationModel::requestStationsFromJourney(int index)
{
    Q_D(JourneysFromStationModel);
    if (index < 0 || index >= rowCount()) {
        return;
    }

    JourneysFromStationsModelItem *data = d->data.at(index);

    if (!data->supportStationsFromJourney) {
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

    QString request = backend->requestStationsFromJourney(data->company, data->line,
                                                          data->journey, data->station);
    emit stationsFromJourneyRequested(backend, request, data->company, data->line, data->journey,
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

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
 * @file stationsmodel.cpp
 * @short Implementation of PublicTransportation::StationsModel
 */

#include "stationsmodel.h"

#include "manager/abstractbackendmanager.h"

namespace PublicTransportation
{

/**
 * @internal
 * @short Private class for PublicTransportation::StationsModel
 */
class StationsModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    StationsModelPrivate(StationsModel *q);
    /**
     * @internal
     * @brief Slot for stations change
     * @param company company.
     * @param line line.
     * @param journey journey.
     */
    void slotStationsChanged(const PublicTransportation::Company &company,
                             const PublicTransportation::Line &line,
                             const PublicTransportation::Journey &journey);
    /**
     * @internal
     * @brief Update the model
     * @param stations stations to set.
     */
    void update(const QList<Station> &stations);
    /**
     * @internal
     * @brief Backend manager
     */
    AbstractBackendManager *backendManager;
    /**
     * @internal
     * @short Data
     */
    QList<Station> data;
    /**
     * @internal
     * @brief Updating
     */
    bool updating;
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
private:
    /**
     * @internal
     * @brief Q-pointer
     */
    StationsModel * const q_ptr;
    Q_DECLARE_PUBLIC(StationsModel)
};

StationsModelPrivate::StationsModelPrivate(StationsModel *q):
    q_ptr(q)
{
    backendManager = 0;
    updating = false;
}

void StationsModelPrivate::slotStationsChanged(const Company &company, const Line &line,
                                               const Journey &journey)
{
    Q_Q(StationsModel);

    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(q->sender());
    if (!backend) {
        return;
    }

    updating = false;
    emit q->updatingChanged();

    QObject::disconnect(backend, SIGNAL(stationsChanged(PublicTransportation::Company,
                                                        PublicTransportation::Line,
                                                        PublicTransportation::Journey)),
                        q, SLOT(slotStationsChanged(PublicTransportation::Company,
                                                    PublicTransportation::Line,
                                                    PublicTransportation::Journey)));

    update(backend->stations(company, line, journey));
}

void StationsModelPrivate::update(const QList<Station> &stations)
{
    Q_Q(StationsModel);

    q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
    data.clear();
    q->endRemoveRows();


    if (stations.count() != 0) {
        q->beginInsertRows(QModelIndex(), 0, stations.count() - 1);
        data = stations;
        emit q->countChanged();
        q->endInsertRows();
    }
}

////// End of private class //////

StationsModel::StationsModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new StationsModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    setRoleNames(roles);
}

StationsModel::~StationsModel()
{
}

void StationsModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(StationsModel);
    if (d->backendManager != backendManager) {
        if (d->backendManager) {
            d->backendManager->disconnect(this);
        }

        d->backendManager = backendManager;
    }
}

int  StationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const StationsModel);
    return d->data.count();
}

bool StationsModel::isUpdating() const
{
    Q_D(const StationsModel);
    return d->updating;
}

int StationsModel::count() const
{
    return rowCount();
}

QVariant StationsModel::data(const QModelIndex &index, int role) const
{
    Q_D(const StationsModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    Station station = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return station.name();
        break;
    case DescriptionRole:
        return station.properties().value("description").toString();
        break;
    default:
        return QVariant();
        break;
    }
}

void StationsModel::test(int index)
{
    Q_D(const StationsModel);
    if (index < 0 or index >= rowCount()) {
        return;
    }
    Station station = d->data.at(index);

    d->backendManager->backend(d->backendIdentifier)->requestWaitingTime(d->company, d->line, d->journey, station);
}

void StationsModel::displayStations(const QString &backendIdentifier, const Company &company,
                                    const Line &line, const Journey &journey)
{
    Q_D(StationsModel);
    if (!d->backendManager) {
        return;
    }

    if (!d->backendManager->contains(backendIdentifier)) {
        return;
    }

    AbstractBackendWrapper *backend = d->backendManager->backend(backendIdentifier);

    d->backendIdentifier = backendIdentifier;
    d->company = company;
    d->line = line;
    d->journey = journey;
    QList<Station> stations = backend->stations(company, line, journey);


    if (stations.isEmpty()) {
        d->updating = true;
        emit updatingChanged();

        connect(backend, SIGNAL(stationsChanged(PublicTransportation::Company,
                                                PublicTransportation::Line,
                                                PublicTransportation::Journey)),
                this, SLOT(slotStationsChanged(PublicTransportation::Company,
                                               PublicTransportation::Line,
                                               PublicTransportation::Journey)));

        backend->requestListStations(company, line, journey);
    } else {
        d->update(stations);
    }
}

}

#include "moc_stationsmodel.cpp"

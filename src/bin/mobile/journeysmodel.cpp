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
 * @file journeysmodel.cpp
 * @short Implementation of PublicTransportation::JourneysModel
 */

#include "journeysmodel.h"

#include "manager/abstractbackendmanager.h"

namespace PublicTransportation
{

/**
 * @internal
 * @short Private class for PublicTransportation::JourneysModel
 */
class JourneysModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    JourneysModelPrivate(JourneysModel *q);
    /**
     * @internal
     * @brief Slot for journeys change
     * @param company company.
     * @param line line.
     */
    void slotJourneysChanged(const PublicTransportation::Company &company,
                          const PublicTransportation::Line &line);
    /**
     * @internal
     * @brief Update the model
     * @param journeys journeys to set.
     */
    void update(const QList<Journey> &journeys);
    /**
     * @internal
     * @brief Backend manager
     */
    AbstractBackendManager *backendManager;
    /**
     * @internal
     * @short Data
     */
    QList<Journey> data;
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
private:
    /**
     * @internal
     * @brief Q-pointer
     */
    JourneysModel * const q_ptr;
    Q_DECLARE_PUBLIC(JourneysModel)
};

JourneysModelPrivate::JourneysModelPrivate(JourneysModel *q):
    q_ptr(q)
{
    backendManager = 0;
    updating = false;
}

void JourneysModelPrivate::slotJourneysChanged(const Company &company, const Line &line)
{
    Q_Q(JourneysModel);

    AbstractBackendWrapper *backend = qobject_cast<AbstractBackendWrapper *>(q->sender());
    if (!backend) {
        return;
    }

    updating = false;
    emit q->updatingChanged();

    QObject::disconnect(backend, SIGNAL(journeysChanged(PublicTransportation::Company,
                                                        PublicTransportation::Line)),
                        q, SLOT(slotJourneysChanged(PublicTransportation::Company,
                                                    PublicTransportation::Line)));

    update(backend->journeys(company, line));
}

void JourneysModelPrivate::update(const QList<Journey> &journeys)
{
    Q_Q(JourneysModel);

    q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
    data.clear();
    q->endRemoveRows();


    if (journeys.count() != 0) {
        q->beginInsertRows(QModelIndex(), 0, journeys.count() - 1);
        data = journeys;
        emit q->countChanged();
        q->endInsertRows();
    }
}

////// End of private class //////

JourneysModel::JourneysModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new JourneysModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    setRoleNames(roles);
}

JourneysModel::~JourneysModel()
{
}

void JourneysModel::setBackendManager(AbstractBackendManager *backendManager)
{
    Q_D(JourneysModel);
    if (d->backendManager != backendManager) {
        if (d->backendManager) {
            d->backendManager->disconnect(this);
        }

        d->backendManager = backendManager;
    }
}

int  JourneysModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const JourneysModel);
    return d->data.count();
}

bool JourneysModel::isUpdating() const
{
    Q_D(const JourneysModel);
    return d->updating;
}

int JourneysModel::count() const
{
    return rowCount();
}

QVariant JourneysModel::data(const QModelIndex &index, int role) const
{
    Q_D(const JourneysModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    Journey journey = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return journey.name();
        break;
    case DescriptionRole:
        return journey.properties().value("description").toString();
        break;
    default:
        return QVariant();
        break;
    }
}

void JourneysModel::displayJourneys(const QString &backendIdentifier, const Company &company,
                                    const Line &line)
{
    Q_D(JourneysModel);
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
    QList<Journey> journeys = backend->journeys(company, line);


    if (journeys.isEmpty()) {
        d->updating = true;
        emit updatingChanged();

        connect(backend, SIGNAL(journeysChanged(PublicTransportation::Company,
                                                PublicTransportation::Line)),
                this, SLOT(slotJourneysChanged(PublicTransportation::Company,
                                               PublicTransportation::Line)));

        backend->requestListJourneys(company, line);
    } else {
        d->update(journeys);
    }
}

void JourneysModel::requestStations(int index)
{
    Q_D(JourneysModel);
    if (d->company.isNull() || d->line.isNull()) {
        return;
    }

    if (index < 0 or index >= rowCount()) {
        return;
    }
    Journey journey = d->data.at(index);

    emit stationsRequested(d->backendIdentifier, d->company, d->line, journey);
}

}

#include "moc_journeysmodel.cpp"

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

#include "journeysfromstationmodel.h"

#include "manager/abstractbackendmanager.h"
#include "debug.h"

namespace PublicTransportation
{

struct JourneysFromStationsModelData
{
    Line line;
    Journey journey;
};

/**
 * @internal
 * @short Private class for PublicTransportation::BackendModel
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
    void slotJourneysRegistered(const QString &request,
                                const QList<PublicTransportation::LineJourneys> &journeys);
    /**
     * @internal
     * @brief Backend list manager
     */
    AbstractBackendManager *backendManager;
    QString currentRequest;
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
                                                              const QList<LineJourneys> &journeys)
{
    Q_Q(JourneysFromStationModel);
    if (currentRequest != request) {
        return;
    }

    q->clear();


    foreach (LineJourneys lineJourneys, journeys) {
        Line line = lineJourneys.line();
        foreach (Journey journey, lineJourneys.journeys()) {
            JourneysFromStationsModelData * dataItem = new JourneysFromStationsModelData;
            dataItem->line = line;
            dataItem->journey = journey;
            data.append(dataItem);
        }
    }

    q->beginInsertRows(QModelIndex(), 0, data.count() - 1);
    emit q->countChanged();
    q->endInsertRows();

    currentRequest = QString();
    emit q->updatingChanged();
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

bool JourneysFromStationModel::isUpdating() const
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
    default:
        return QVariant();
        break;
    }
}

void JourneysFromStationModel::load(AbstractBackendWrapper *backend, const QString &request)
{
    Q_D(JourneysFromStationModel);
    connect(backend,
            SIGNAL(journeysFromStationRegistered(QString,
                                                 QList<PublicTransportation::LineJourneys>)),
            this, SLOT(slotJourneysRegistered(QString,QList<PublicTransportation::LineJourneys>)));
    d->currentRequest = request;
    emit updatingChanged();
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

#include "moc_journeysfromstationmodel.cpp"

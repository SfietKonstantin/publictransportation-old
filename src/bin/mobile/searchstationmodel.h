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
 * @file backendmodel.h
 * @short Definition of PublicTransportation::BackendModel
 */

#ifndef PUBLICTRANSPORTATION_SEARCHSTATIONMODEL_H
#define PUBLICTRANSPORTATION_SEARCHSTATIONMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QSettings>
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManager;

class SearchStationModelPrivate;
class SearchStationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool updating READ isUpdating NOTIFY updatingChanged)
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum SearchStationModelRole {
        /**
         * @short Name role
         */
        NameRole = Qt::UserRole + 1,
        SupportGetJourneysRole,
        /**
         * @short Company role
         */
        ProviderNameRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit SearchStationModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~SearchStationModel();
    /**
     * @brief Set backend manager
     * @param backendManager backend manager to set.
     */
    void setBackendManager(AbstractBackendManager *backendManager);
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return the number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool isUpdating() const;
    /**
     * @short Count
     * @return count.
     */
    int count() const;
    /**
     * @short Reimplementation of data
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
public Q_SLOTS:
    /**
     * @brief Search
     */
    void search(const QString &partialStation);
    void clear();
    void requestJourneysFromStation(int index);
Q_SIGNALS:
    void updatingChanged();
    /**
     * @short Count changed
     */
    void countChanged();
    void journeysFromStationRequested(AbstractBackendWrapper *backend, const QString &request);
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<SearchStationModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(SearchStationModel)
    Q_PRIVATE_SLOT(d_func(), void slotBackendAdded(QString,AbstractBackendWrapper*))
    Q_PRIVATE_SLOT(d_func(), void slotStatusChanged())
    Q_PRIVATE_SLOT(d_func(), void slotErrorRegistered(QString,QString))
    Q_PRIVATE_SLOT(d_func(),
                   void slotSuggestedStationsRegistered(QString,
                                                        QList<PublicTransportation::Station>))

};

}

#endif // PUBLICTRANSPORTATION_SEARCHSTATIONMODEL_H
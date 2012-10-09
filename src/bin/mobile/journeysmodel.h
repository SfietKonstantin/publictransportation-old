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

#ifndef PUBLICTRANSPORTATION_JOURNEYSMODEL_H
#define PUBLICTRANSPORTATION_JOURNEYSMODEL_H

#include <QtCore/QAbstractListModel>
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManager;
class JourneysModelPrivate;
class JourneysModel: public QAbstractListModel
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
    enum JourneysModelRole {
        /**
         * @short Name role
         */
        NameRole = Qt::UserRole + 1,
        DescriptionRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit JourneysModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~JourneysModel();
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
    void displayJourneys(const QString &backendIdentifier,
                         const PublicTransportation::Company &company,
                         const PublicTransportation::Line &line);
    void requestJourney(int index);
Q_SIGNALS:
    void updatingChanged();
    /**
     * @short Count changed
     */
    void countChanged();
    void displayStations(const QString &backendIdentifier,
                         const PublicTransportation::Company &company,
                         const PublicTransportation::Line &line,
                         const PublicTransportation::Journey &journey);
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<JourneysModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(JourneysModel)
    Q_PRIVATE_SLOT(d_func(), void slotJourneysChanged(PublicTransportation::Company,
                                                      PublicTransportation::Line))

};

}

#endif // PUBLICTRANSPORTATION_JOURNEYSMODEL_H

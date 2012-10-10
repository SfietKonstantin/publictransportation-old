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

#ifndef PUBLICTRANSPORTATION_STATIONSMODEL_H
#define PUBLICTRANSPORTATION_STATIONSMODEL_H

/**
 * @file stationsmodel.h
 * @short Definition of PublicTransportation::StationsModel
 */

#include <QtCore/QAbstractListModel>
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManager;
class StationsModelPrivate;

/**
 * @brief A model for stations
 *
 * This class provides a model for QML that contains
 * a list of stations. It lists all the lines of
 * a given journey.
 *
 * This class is populated by calling
 * displayStations().
 */
class StationsModel: public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short If the model is updating
     */
    Q_PROPERTY(bool updating READ isUpdating NOTIFY updatingChanged)
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum StationsModelRole {
        /**
         * @short Name role
         */
        NameRole = Qt::UserRole + 1,
        /**
         * @short Description role
         */
        DescriptionRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit StationsModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~StationsModel();
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
    /**
     * @brief If the model is updating
     * @return if the model is updating.
     */
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
    void test(int index);
    /**
     * @brief Display stations
     * @param backendIdentifier backend identifier.
     * @param company company for which the stations is requested.
     * @param line line for which the stations is requested.
     * @param journey journey for which the stations is requested.
     */
    void displayStations(const QString &backendIdentifier,
                         const PublicTransportation::Company &company,
                         const PublicTransportation::Line &line,
                         const PublicTransportation::Journey &journey);
Q_SIGNALS:
    /**
     * @brief Updating changed
     */
    void updatingChanged();
    /**
     * @short Count changed
     */
    void countChanged();
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<StationsModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(StationsModel)
    Q_PRIVATE_SLOT(d_func(), void slotStationsChanged(PublicTransportation::Company,
                                                      PublicTransportation::Line,
                                                      PublicTransportation::Journey))

};

}

#endif // PUBLICTRANSPORTATION_STATIONSMODEL_H

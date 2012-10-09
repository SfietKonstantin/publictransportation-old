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

/**
 * @file journeysmodel.h
 * @short Definition of PublicTransportation::JourneysModel
 */

#include <QtCore/QAbstractListModel>
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManager;
class JourneysModelPrivate;

/**
 * @brief A model for journeys
 *
 * This class provides a model for QML that contains
 * a list of journeys. It lists all the journeys of
 * a given line.
 *
 * This class is populated by calling
 * displayJourneys().
 *
 * This class also provides a method for QML context,
 * that is requestStations(), and that is used to ask for
 * getting informations on stations. This method is used to
 * emit stationsRequested() signal.
 */
class JourneysModel: public QAbstractListModel
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
    enum JourneysModelRole {
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
    /**
     * @brief Display journeys
     * @param backendIdentifier backend identifier.
     * @param company company for which the journey is requested.
     * @param line line for which the journey is requested.
     */
    void displayJourneys(const QString &backendIdentifier,
                         const PublicTransportation::Company &company,
                         const PublicTransportation::Line &line);
    /**
     * @brief Request stations of a given journey
     * @param index index of the journey.
     */
    void requestStations(int index);
Q_SIGNALS:
    /**
     * @brief Updating changed
     */
    void updatingChanged();
    /**
     * @short Count changed
     */
    void countChanged();
    /**
     * @brief Stations requested
     * @param backendIdentifier backend identifier.
     * @param company company for which the stations are requested.
     * @param line line for which the stations are requested.
     * @param journey journey for which the stations are requested.
     */
    void stationsRequested(const QString &backendIdentifier,
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

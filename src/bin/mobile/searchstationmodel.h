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

#ifndef PUBLICTRANSPORTATION_GUI_SEARCHSTATIONMODEL_H
#define PUBLICTRANSPORTATION_GUI_SEARCHSTATIONMODEL_H

/**
 * @file searchstationmodel.h
 * @short Definition of PublicTransportation::Gui::SearchStationModel
 */

#include <QtCore/QAbstractListModel>
#include <QtCore/QSettings>
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManager;

namespace Gui
{

class FavouriteManager;
class SearchStationModelPrivate;
/**
 * @brief A model for stations being searched
 *
 * This class provides a model for QML that contains
 * a list of stations that were searched. It also provides
 * a method to interact with the station, and query the
 * journeys from the station.
 */
class SearchStationModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Loading
     */
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)
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
        /**
         * @short Company role
         */
        ProviderNameRole,
        /**
         * @short If the backend support getting journeys from station
         */
        SupportJourneysFromStationRole,
        FavouriteRole
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
     * @brief Set favourite manager
     * @param favouriteManager favourite manager to set.
     */
    void setFavouriteManager(FavouriteManager *favouriteManager);
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return the number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @brief Is loading
     * @return if this model is loading.
     */
    bool isLoading() const;
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
     * @param partialStation partial station name.
     */
    void search(const QString &partialStation);
    /**
     * @brief Reset the view
     *
     * Resetting the view displays the favourites.
     */
    void reset();
    /**
     * @brief Clear
     */
    void clear();
    /**
     * @brief Request journeys from station
     * @param index index of the station.
     */
    void requestJourneysFromStation(int index);
Q_SIGNALS:
    /**
     * @brief Loading changed
     */
    void loadingChanged();
    /**
     * @short Count changed
     */
    void countChanged();
    /**
     * @brief Journeys from station requested
     * @param backend backend answering the request.
     * @param request request id.
     * @param station station.
     */
    void journeysFromStationRequested(AbstractBackendWrapper *backend,
                                      const QString &request,
                                      const PublicTransportation::Station &station);
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<SearchStationModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(SearchStationModel)
    /// \cond buggy-doxygen-doc
    Q_PRIVATE_SLOT(d_func(), void slotBackendAdded(QString,AbstractBackendWrapper*))
    Q_PRIVATE_SLOT(d_func(), void slotStatusChanged())
    Q_PRIVATE_SLOT(d_func(), void slotErrorRegistered(QString,QString,QString))
    Q_PRIVATE_SLOT(d_func(),
                   void slotSuggestedStationsRegistered(QString,
                                                        QList<PublicTransportation::Station>))
    Q_PRIVATE_SLOT(d_func(), void displayFavourites())
    /// \endcond

};

}

}

#endif // PUBLICTRANSPORTATION_GUI_SEARCHSTATIONMODEL_H

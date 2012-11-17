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

#ifndef PUBLICTRANSPORTATION_GUI_STATIONSFROMJOUNREYMODEL_H
#define PUBLICTRANSPORTATION_GUI_STATIONSFROMJOUNREYMODEL_H

/**
 * @file stationsfromjourneymodel.h
 * @short Definition of PublicTransportation::Gui::StationsFromJourneyModel
 */

#include <QtCore/QAbstractListModel>

namespace PublicTransportation
{

class AbstractBackendManager;
class AbstractBackendWrapper;
class Company;
class Line;
class Journey;
class Station;

namespace Gui
{

class StationsFromJourneyModelPrivate;

/**
 * @brief A model for stations from a journey
 *
 * This model displays all the stations from a journey, most
 * of the time as a scheme indicating the different stations
 * that this journey goes through.
 */
class StationsFromJourneyModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(ConnectorType)
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
     * @brief Connector types
     */
    enum ConnectorType {
        /**
         * @short The connector is visible
         */
        ConnectorVisible,
        /**
         * @short The connector is fading
         */
        ConnectorFading,
        /**
         * @short The connector is not visible
         */
        ConnectorInvisible
    };

    /**
     * @short Model roles
     */
    enum StationsFromJourneyRole {
        /**
         * @short Station role
         */
        StationRole = Qt::UserRole + 1,
        /**
         * @short Terminus role
         */
        TerminusRole,
        /**
         * @short Previous connector role
         */
        PreviousConnectorType,
        /**
         * @short Next connector role
         */
        NextConnectorType
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit StationsFromJourneyModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~StationsFromJourneyModel();
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
     * @brief A request for journeys from waiting time has been sent
     * @param backend backend answering the request.
     * @param request request identifier.
     * @param company company.
     * @param line line.
     * @param journey journey.
     * @param station station.
     */
    void load(AbstractBackendWrapper *backend, const QString &request,
              const PublicTransportation::Company &company,
              const PublicTransportation::Line &line,
              const PublicTransportation::Journey &journey,
              const PublicTransportation::Station &station);
    /**
     * @brief Clear
     */
    void clear();
Q_SIGNALS:
    /**
     * @brief Loading changed
     */
    void loadingChanged();
    /**
     * @short Count changed
     */
    void countChanged();
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<StationsFromJourneyModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(StationsFromJourneyModel)
    Q_PRIVATE_SLOT(d_func(),
               void slotStationsFromJourneyRegistered(QString,QList<PublicTransportation::Station>))
};

}

}

#endif // PUBLICTRANSPORTATION_GUI_STATIONSFROMJOUNREYMODEL_H

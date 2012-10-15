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
 * @file journeysfromstationmodel.h
 * @short Definition of PublicTransportation::Gui::JourneysFromStationModel
 */

#ifndef PUBLICTRANSPORTATION_GUI_JOURNEYSFROMSTATIONSMODEL_H
#define PUBLICTRANSPORTATION_GUI_JOURNEYSFROMSTATIONSMODEL_H

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

class JourneysFromStationModelPrivate;
/**
 * @brief A model for journeys going from a station
 *
 * This class provides a model for QML that contains
 * a list of journeys for a given station. It also provides
 * a method to interact with the journey, and query the
 * waiting time for the given journey.
 */
class JourneysFromStationModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    /**
     * @short Loading
     */
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)
public:
    /**
     * @short Model roles
     */
    enum JourneysFromStationsModelRole {
        /**
         * @short Name role
         */
        NameRole = Qt::UserRole + 1,
        /**
         * @short Line role
         */
        LineRole,
        /**
         * @short Company role
         */
        CompanyRole,
        /**
         * @short Station role
         */
        StationRole,
        /**
         * @short If the backend support waiting time
         */
        SupportWaitingTimeRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit JourneysFromStationModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~JourneysFromStationModel();
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
     * @brief A request for journeys from station has been sent
     * @param backend backend answering the request.
     * @param request request identifier.
     * @param station station to query.
     */
    void load(AbstractBackendWrapper *backend, const QString &request,
              const PublicTransportation::Station &station);
    /**
     * @brief Request waiting time
     * @param index index of the journey.
     */
    void requestWaitingTime(int index);
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
    /**
     * @brief Waiting time requested
     * @param backend backend answering the request.
     * @param request request id.
     * @param company company.
     * @param line line.
     * @param journey journey.
     * @param station station.
     */
    void waitingTimeRequested(AbstractBackendWrapper *backend, const QString &request,
                              const PublicTransportation::Company &company,
                              const PublicTransportation::Line &line,
                              const PublicTransportation::Journey &journey,
                              const PublicTransportation::Station &station);
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<JourneysFromStationModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(JourneysFromStationModel)
    Q_PRIVATE_SLOT(d_func(),
                   void slotJourneysRegistered(QString,QList<PublicTransportation::InfoJourneys>))
};

}

}

#endif // PUBLICTRANSPORTATION_GUI_JOURNEYSFROMSTATIONSMODEL_H

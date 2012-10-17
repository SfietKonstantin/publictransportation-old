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
 * @file waitingtimemodel.h
 * @short Definition of PublicTransportation::Gui::WaitingTimeModel
 */

#ifndef PUBLICTRANSPORTATION_GUI_WAITINGTIMEMODEL_H
#define PUBLICTRANSPORTATION_GUI_WAITINGTIMEMODEL_H

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

class WaitingTimeModelPrivate;
/**
 * @brief A model for waiting time
 *
 * This class provides a model for QML that contains
 * a list of waiting time.
 */
class WaitingTimeModel : public QAbstractListModel
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
    enum WaitingTimeModelRole {
        /**
         * @short Name role
         */
        WaitingTimeRole = Qt::UserRole + 1,
        /**
         * @short Direction role
         */
        DestinationRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit WaitingTimeModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~WaitingTimeModel();
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
     * @brief Reload
     */
    void reload();
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
    const QScopedPointer<WaitingTimeModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(WaitingTimeModel)
    Q_PRIVATE_SLOT(d_func(),
                   void slotWaitingTimeRegistered(QString,QList<PublicTransportation::WaitingTime>))
};

}

}

#endif // PUBLICTRANSPORTATION_GUI_WAITINGTIMEMODEL_H

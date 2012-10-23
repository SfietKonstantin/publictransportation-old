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
 * @short Definition of PublicTransportation::Gui::BackendModel
 */

#ifndef PUBLICTRANSPORTATION_GUI_BACKENDMODEL_H
#define PUBLICTRANSPORTATION_GUI_BACKENDMODEL_H

#include <QtCore/QAbstractListModel>
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManager;

namespace Gui
{

class BackendModelPrivate;

/**
 * @brief A model for available backends
 *
 * This class provides a model for QML that contains
 * the available backends. It also provides control
 * over the backends, as well as feedback on backend
 * status.
 *
 * It mostly mirrors PublicTransportation::AbstractBackendManager,
 * adding only a feature, that is starting previously started
 * backend when reloading the backend list.
 *
 * When a backend have been previously started, and not
 * stopped, it is considered as useful, and should be
 * restart. When the list of backends are reloaded, these
 * backends are then restarted automatically (that happen,
 * for example, while the application is launched again).
 *
 * This model can also be filtered, using the filter() property.
 * This filter takes a country code, or an empty string for all countries,
 * and will filter the list by countries.
 */
class BackendModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(BackendStatus)
    /**
     * @short Filter
     */
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @brief Enumeration describing backend status
     */
    enum BackendStatus {
        /**
         * @short The backend is stopped
         */
        Stopped = AbstractBackendWrapper::Stopped,
        /**
         * @short The backend is launching
         */
        Launching = AbstractBackendWrapper::Launching,
        /**
         * @short The backend is launched
         */
        Launched = AbstractBackendWrapper::Launched,
        /**
         * @short The backend is stopping
         */
        Stopping = AbstractBackendWrapper::Stopping,
        /**
         * @short The backend is in an invalid state
         */
        Invalid = AbstractBackendWrapper::Invalid
    };

    /**
     * @short Model roles
     */
    enum BackendModelRole {
        /**
         * @short Name role
         */
        NameRole = Qt::UserRole + 1,
        /**
         * @short Description role
         */
        DescriptionRole,
        /**
         * @short Status role
         */
        StatusRole,
        /**
         * @short Identifier role
         */
        IdentifierRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit BackendModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~BackendModel();
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
     * @brief Filter
     * @return filter.
     */
    QString filter() const;
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
     * @brief Set filter
     * @param filter filter to set.
     */
    void setFilter(const QString &filter);
    /**
     * @brief Reload
     *
     * Reload the backend list.
     */
    void reload();
    /**
     * @brief Run a backend
     * @param identifier backend identifier.
     */
    void runBackend(const QString &identifier);
    /**
     * @brief Stop a backend.
     * @param identifier backend identifier.
     */
    void stopBackend(const QString &identifier);
Q_SIGNALS:
    /**
     * @brief Filter changed
     */
    void filterChanged();
    /**
     * @short Count changed
     */
    void countChanged();
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<BackendModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BackendModel)
    Q_PRIVATE_SLOT(d_func(), void slotStatusChanged())

};

}

}

#endif // PUBLICTRANSPORTATION_GUI_BACKENDMODEL_H

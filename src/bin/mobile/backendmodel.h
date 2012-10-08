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

#ifndef PUBLICTRANSPORTATION_BACKENDMODEL_H
#define PUBLICTRANSPORTATION_BACKENDMODEL_H

#include <QtCore/QAbstractListModel>
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManager;
class BackendModelPrivate;
class BackendModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(BackendStatus)
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum BackendStatus {
        Stopped = AbstractBackendWrapper::Stopped,
        Launching = AbstractBackendWrapper::Launching,
        Launched = AbstractBackendWrapper::Launched,
        Stopping = AbstractBackendWrapper::Stopping,
        Invalid = AbstractBackendWrapper::Invalid
    };

    /**
     * @short Model roles
     */
    enum BackendModelRole {
        /**
         * @short Widget role
         */
        NameRole = Qt::UserRole + 1,
        DescriptionRole,
        StatusRole,
        IdentifierRole,
        ExecutableRole
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
    void reload();
    void runBackend(const QString &identifier, const QString &executable);
    void stopBackend(const QString &identifier);
Q_SIGNALS:
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

#endif // PUBLICTRANSPORTATION_BACKENDMODEL_H

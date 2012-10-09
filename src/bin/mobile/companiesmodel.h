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
 * @file companiesmodel.h
 * @short Definition of PublicTransportation::CompaniesModel
 */

#ifndef PUBLICTRANSPORTATION_COMPANIESMODEL_H
#define PUBLICTRANSPORTATION_COMPANIESMODEL_H

#include <QtCore/QAbstractListModel>
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class AbstractBackendManager;
class CompaniesModelPrivate;

class CompaniesModel: public QAbstractListModel
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
    enum CompaniesModelRole {
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
    explicit CompaniesModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~CompaniesModel();
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
    void requestCompany(int index);
Q_SIGNALS:
    void updatingChanged();
    /**
     * @short Count changed
     */
    void countChanged();
    void displayLines(const QString &backendIdentifier,
                      const PublicTransportation::Company &company);
protected:
    /**
     * @short D-pointer
     */
    const QScopedPointer<CompaniesModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(CompaniesModel)
    /// \cond buggy-doxygen-doc
    Q_PRIVATE_SLOT(d_func(), void slotBackendAdded(QString,AbstractBackendWrapper*))
    Q_PRIVATE_SLOT(d_func(), void slotBackendRemoved(QString))
    Q_PRIVATE_SLOT(d_func(), void slotStatusChanged())
    Q_PRIVATE_SLOT(d_func(), void slotCompaniesChanged())
    /// \endcond

};

}

#endif // PUBLICTRANSPORTATION_COMPANIESMODEL_H

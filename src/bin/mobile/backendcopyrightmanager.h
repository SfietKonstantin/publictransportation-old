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

#ifndef PUBLICTRANSPORTATION_GUI_BACKENDCOPYRIGHTMANAGER_H
#define PUBLICTRANSPORTATION_GUI_BACKENDCOPYRIGHTMANAGER_H

/**
 * @file backendcopyrightmanager.h
 * @short Definition of PublicTransportation::Gui::BackendCopyrightManager
 */

#include <QtCore/QObject>

namespace PublicTransportation
{

class AbstractBackendManager;

namespace Gui
{

class BackendCopyrightManagerPrivate;

/**
 * @brief Backend copyright manager
 *
 * This class provides access to the copyright notice
 * of a given backend, as well as the list of capabilities,
 * in a human readable way.
 *
 * Querying the copyright notice is done with
 * - setBackend()
 *
 * Accessing data is done with the properties
 * - copyright()
 * - capabilities()
 */
class BackendCopyrightManager : public QObject
{
    Q_OBJECT
    /**
     * @short Loading
     */
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)
    /**
     * @short Copyright
     */
    Q_PROPERTY(QString copyright READ copyright NOTIFY copyrightChanged)
    /**
     * @short Capabilities
     */
    Q_PROPERTY(QString capabilities READ capabilities NOTIFY capabilitiesChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit BackendCopyrightManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~BackendCopyrightManager();
    /**
     * @brief Is loading
     * @return if this manager is loading.
     */
    bool isLoading() const;
    /**
     * @brief Copyright
     * @return copyright.
     */
    QString copyright() const;
    /**
     * @brief Capabilities
     * @return capabilities.
     */
    QString capabilities() const;
    /**
     * @brief Set backend manager
     * @param backendManager backend manager to set.
     */
    void setBackendManager(AbstractBackendManager *backendManager);
public Q_SLOTS:
    /**
     * @brief Set the backend to query
     * @param identifier backend identifier.
     */
    void setBackend(const QString &identifier);
Q_SIGNALS:
    /**
     * @brief Loading changed
     */
    void loadingChanged();
    /**
     * @brief Copyright changed
     */
    void copyrightChanged();
    /**
     * @brief Capabilities changed
     */
    void capabilitiesChanged();
protected:
    /**
     * @short D-pointer
     */
    QScopedPointer<BackendCopyrightManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BackendCopyrightManager)
    /// \cond buggy-doxygen-doc
    Q_PRIVATE_SLOT(d_func(), void slotStatusChanged())
    Q_PRIVATE_SLOT(d_func(), void slotCopyrightRegistered(QString,QString))
    /// \endcond

};

}

}

#endif // PUBLICTRANSPORTATION_GUI_BACKENDCOPYRIGHTMANAGER_H

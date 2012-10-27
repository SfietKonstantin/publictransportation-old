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

#include <QtCore/QObject>

namespace PublicTransportation
{

class AbstractBackendManager;

namespace Gui
{

class BackendCopyrightManagerPrivate;
class BackendCopyrightManager : public QObject
{
    Q_OBJECT
    /**
     * @short Loading
     */
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)
    Q_PROPERTY(QString copyright READ copyright NOTIFY copyrightChanged)
    Q_PROPERTY(QString capabilities READ capabilities NOTIFY capabilitiesChanged)
public:
    explicit BackendCopyrightManager(QObject *parent = 0);
    virtual ~BackendCopyrightManager();
    bool isLoading() const;
    QString copyright() const;
    QString capabilities() const;
    /**
     * @brief Set backend manager
     * @param backendManager backend manager to set.
     */
    void setBackendManager(AbstractBackendManager *backendManager);
public Q_SLOTS:
    void setBackend(const QString &identifier);
Q_SIGNALS:
    void loadingChanged();
    void copyrightChanged();
    void capabilitiesChanged();
protected:
    QScopedPointer<BackendCopyrightManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BackendCopyrightManager)
    Q_PRIVATE_SLOT(d_func(), void slotStatusChanged())
    Q_PRIVATE_SLOT(d_func(), void slotCopyrightRegistered(QString,QString))

};

}

}

#endif // PUBLICTRANSPORTATION_GUI_BACKENDCOPYRIGHTMANAGER_H

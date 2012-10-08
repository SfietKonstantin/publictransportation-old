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

#ifndef PUBLICTRANSPORTATION_BACKENDLISTMANAGER_H
#define PUBLICTRANSPORTATION_BACKENDLISTMANAGER_H

#include "publictransportation_global.h"

#include <QtCore/QObject>

#include "backendinfo.h"

namespace PublicTransportation
{

class BackendListManagerPrivate;
class PUBLICTRANSPORTATION_EXPORT BackendListManager : public QObject
{
    Q_OBJECT
public:
    explicit BackendListManager(QObject *parent = 0);
    virtual ~BackendListManager();
    QList<BackendInfo> backendList() const;
public Q_SLOTS:
    void reload();
Q_SIGNALS:
    void backendListChanged();
protected:
    QScopedPointer<BackendListManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BackendListManager)
};

}

#endif // PUBLICTRANSPORTATION_BACKENDLISTMANAGER_H

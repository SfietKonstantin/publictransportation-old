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

#ifndef PUBLICTRANSPORTATION_PROVIDER_OPENDATACH_H
#define PUBLICTRANSPORTATION_PROVIDER_OPENDATACH_H

#include <QtCore/QObject>
#include "provider/providerpluginobject.h"

namespace PublicTransportation
{

namespace Provider
{

class OpenDataChPrivate;
class OpenDataCh : public ProviderPluginObject
{
    Q_OBJECT
    Q_INTERFACES(PublicTransportation::ProviderPluginInterface)
public:
    explicit OpenDataCh(QObject *parent = 0);
    virtual QStringList capabilities() const;
public Q_SLOTS:
    virtual void retrieveSuggestedStations(const QString &request, const QString &partialStation);
protected:
    QScopedPointer<OpenDataChPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(OpenDataCh)
    Q_PRIVATE_SLOT(d_func(), void slotSuggestedStationsFinished())
};

}

}

#endif // PUBLICTRANSPORTATION_PROVIDER_OPENDATACH_H

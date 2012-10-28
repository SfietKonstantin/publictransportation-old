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

#ifndef PUBLICTRANSPORTATION_PROVIDER_SIBRA_H
#define PUBLICTRANSPORTATION_PROVIDER_SIBRA_H

#include <QtCore/QObject>
#include "provider/providerpluginobject.h"

namespace PublicTransportation
{

namespace Provider
{

class SibraPrivate;
class Sibra : public ProviderPluginObject
{
    Q_OBJECT
    Q_INTERFACES(PublicTransportation::ProviderPluginInterface)
public:
    explicit Sibra(QObject *parent = 0);
    virtual QStringList capabilities() const;
public Q_SLOTS:
    virtual void retrieveCopyright(const QString &request);
    virtual void retrieveSuggestedStations(const QString &request, const QString &partialStation);
    virtual void retrieveJourneysFromStation(const QString &request, const Station &station,
                                             int limit);
    virtual void retrieveWaitingTime(const QString &request, const Company &company,
                                     const Line &line, const Journey &journey,
                                     const Station &station);
protected:
    QScopedPointer<SibraPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(Sibra)
    Q_PRIVATE_SLOT(d_func(), void slotJourneysOrWaitingTimeFinished())
};

}

}

#endif // PUBLICTRANSPORTATION_PROVIDER_SIBRA_H

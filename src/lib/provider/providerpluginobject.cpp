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

#include "providerpluginobject.h"

namespace PublicTransportation
{

ProviderPluginObject::ProviderPluginObject(QObject *parent):
    QObject(parent)
{
}

ProviderPluginObject::~ProviderPluginObject()
{
}

void ProviderPluginObject::retrieveSuggestedStations(const QString &request,
                                                     const QString &partialStation)
{
    Q_UNUSED(partialStation)
    emit errorRetrieved(request, tr("SUGGEST_STATIONS capability is not implemented"));
}

void ProviderPluginObject::retrieveJourneysFromStation(const QString &request,
                                                       const Station &station, int limit)
{
    Q_UNUSED(station)
    Q_UNUSED(limit)
    emit errorRetrieved(request, tr("JOURNEYS_FROM_STATION capability is not implemented"));
}


}
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

#include "providerplugintesthelper.h"

#include <QtCore/QtPlugin>

#include "debug.h"
#include "common/capabilitiesconstants.h"
#include "common/company.h"

using namespace PublicTransportation;

ProviderPluginTestHelper::ProviderPluginTestHelper(QObject *parent) :
    ProviderPluginObject(parent)
{

}

QStringList ProviderPluginTestHelper::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    return capabilities;
}

void ProviderPluginTestHelper::retrieveSuggestedStations(const QString &request,
                                                         const QString &partialStation)
{
    QList<Station> data;
    data.append(Station(QVariantMap(), partialStation, QVariantMap()));
    data.append(Station(QVariantMap(), partialStation.repeated(2), QVariantMap()));
    data.append(Station(QVariantMap(), partialStation.repeated(3), QVariantMap()));

    emit suggestedStationsRetrieved(request, data);
}

Q_EXPORT_PLUGIN2(providerplugintesthelper, ProviderPluginTestHelper)

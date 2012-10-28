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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_OFFLINEXMLJOURNEYSFROMSTATIONHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_OFFLINEXMLJOURNEYSFROMSTATIONHELPER_H

#include "publictransportationpluginhelper_global.h"

#include <QtCore/QList>
#include <QtCore/QVariantMap>

namespace PublicTransportation
{

class Company;
class Line;
class Station;
class InfoJourneys;
namespace PluginHelper
{

class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT OfflineXmlJourneysFromStationHelper
{
public:
    static QList<InfoJourneys> journeysFromStation(const QString &xmlFile,
                                                   const Station &station,
                                                   const QVariantMap &disambiguation,
                                                   const Company &company,
                                                   bool *ok = 0,
                                                   QString *errorMessage = 0);
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_OFFLINEXMLJOURNEYSFROMSTATIONHELPER_H

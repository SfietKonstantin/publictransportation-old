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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_OFFLINESUGGESTEDSTATIONSHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_OFFLINESUGGESTEDSTATIONSHELPER_H

/**
 * @file offlinesuggestedstationshelper.h
 * @short Definition of PublicTransportation::PluginHelper::OfflineSuggestedStationsHelper
 */

#include "publictransportationpluginhelper_global.h"

#include <QtCore/QList>
#include <QtCore/QVariantMap>

class QString;
namespace PublicTransportation
{

class Station;
namespace PluginHelper
{

/**
 * @brief Offline suggested stations helper
 *
 * This class provide a method to make the creation
 * of suggested stations easy.
 */
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT OfflineSuggestedStationsHelper
{
public:
    /**
     * @brief Generate a list of suggested stations
     *
     * This method is used to create a list of suggested
     * stations, based on a list of name of these stations,
     * and disambiguation parameters and properties that
     * are shared between those stations, as well as a
     * partial station to match.
     *
     * @param partialStation partial station.
     * @param stations list of station names.
     * @param disambiguation disambiguation.
     * @param properties properties.
     * @return a list of suggested stations.
     */
    static QList<Station> suggestedStations(const QString &partialStation,
                                            const QList<QString> &stations,
                                            const QVariantMap &disambiguation,
                                            const QVariantMap &properties);
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_OFFLINESUGGESTEDSTATIONSHELPER_H

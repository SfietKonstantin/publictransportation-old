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

#include "publictransportationpluginhelper_global.h"

#include <QtCore/QList>
#include <QtCore/QVariantMap>

class QString;
namespace PublicTransportation
{

class Station;
namespace PluginHelper
{

class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT OfflineSuggestedStationsHelper
{
public:
    static QList<Station> suggestedStations(const QString &partialStation,
                                            const QList<QString> &stations,
                                            const QVariantMap &disambiguation,
                                            const QVariantMap &properties);
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_OFFLINESUGGESTEDSTATIONSHELPER_H

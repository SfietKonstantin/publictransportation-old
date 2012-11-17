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

/**
 * @file offlinesuggestedstationshelper.cpp
 * @short Implementation of PublicTransportation::PluginHelper::OfflineSuggestedStationsHelper
 */

#include "offlinesuggestedstationshelper.h"

#include <QtCore/QString>

#include "common/station.h"
#include "languagehelper.h"

namespace PublicTransportation
{

namespace PluginHelper
{

QList<Station> OfflineSuggestedStationsHelper::suggestedStations(const QString &partialStation,
                                                      const QList<QString> &stations,
                                                      const QVariantMap &disambiguation,
                                                      const QVariantMap &properties)
{
    QList<Station> suggestedStations;
    QString unaccentPartialStation = PluginHelper::LanguageHelper::unaccent(partialStation);


    foreach (QString stationName, stations) {
        QString unaccentStationName = PluginHelper::LanguageHelper::unaccent(stationName);

        if (unaccentStationName.startsWith(unaccentPartialStation)) {
            Station station (disambiguation, stationName, properties);
            suggestedStations.append(station);
        }
    }
    foreach (QString stationName, stations) {
        QString unaccentStationName = PluginHelper::LanguageHelper::unaccent(stationName);

        if (unaccentStationName.contains(unaccentPartialStation)) {
            bool added = false;
            foreach (Station station, suggestedStations) {
                if (station.name() == stationName) {
                    added = true;
                }
            }

            if (!added) {
                Station station (disambiguation, stationName, properties);
                suggestedStations.append(station);
            }
        }
    }

    return suggestedStations;
}

}

}

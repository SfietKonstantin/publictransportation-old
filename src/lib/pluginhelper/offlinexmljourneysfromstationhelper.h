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

/**
 * @file offlinexmljourneysfromstationhelper.h
 * @short Definition of PublicTransportation::PluginHelper::OfflineXmlJourneysFromStationHelper
 */


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

/**
 * @brief Offline journeys from station helper using XML
 *
 * This class provide a method to make the creation
 * of journeys from station easy, if the journeys from station
 * are provided using a specific format.
 *
 * The format is as follow:
 * \code{xml}
<stations>
    <station name="Name of a station">
        <line name="Name of the line" property1="Some property" property2="Some other property">
            <journey name="Name of the journey" property1="Some property"
                     property2="Some other property"/>
            <journey name="Name of another journey" property1="Some property"
                     property2="Some other property"/>
        </line>
    </station>
    ...
</stations>
 * \endcode
 */
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT OfflineXmlJourneysFromStationHelper
{
public:
    /**
     * @brief Generate a list of informations about a journey
     *
     * This method is used to create a list of journeys
     * from station based on an XML file, the station, and
     * a set of parameters, like the company, and the
     * disambiguation parameter.
     *
     * @param xmlFile XML file.
     * @param station station.
     * @param disambiguation disambiguation.
     * @param company company.
     * @param ok if the file were correctly processed.
     * @param errorMessage an error message.
     * @return a list of informations about a journey.
     */
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

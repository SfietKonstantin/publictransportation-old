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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_H

/**
 * @file abstractjourneysfromstationhelper.h
 * @short Definition of PublicTransportation::PluginHelper::AbstractJourneysFromStationHelper
 */

#include "publictransportationpluginhelper_global.h"

#include "abstractonlinehelper.h"

class QIODevice;
class QNetworkAccessManager;
class QNetworkRequest;
namespace PublicTransportation
{

class Station;
class InfoJourneys;
namespace PluginHelper
{

class AbstractJourneysFromStationHelperPrivate;

/**
 * @brief A class used to support journeys from station
 *
 * This class provides an interface for getting journeys
 * from station. In order to use that class you need to reimplement
 * processData(), and send the journeysFromStationRetrieved() signal.
 *
 * When implementing this class, you can call station()
 * to know what is the station that is used in the queries,
 * and limit() to know the limit to use. These data are set by
 * calling setData().
 */
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractJourneysFromStationHelper:
        public AbstractOnlineHelper
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit AbstractJourneysFromStationHelper(QNetworkAccessManager *networkAccessManager,
                                               QObject *parent = 0);
    /**
     * @brief setData
     * @param station station.
     * @param limit limit.
     */
    void setData(const Station &station, int limit);
Q_SIGNALS:
    /**
     * @brief Journeys from station retrieved
     * @param request request.
     * @param infoJourneysList info journeys list.
     */
    void journeysFromStationRetrieved(const QString &request,
                                 const QList<PublicTransportation::InfoJourneys> &infoJourneysList);
protected:
    /**
     * @brief D-pointer based constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractJourneysFromStationHelper(AbstractJourneysFromStationHelperPrivate &dd,
                                               QObject *parent);
    /**
     * @brief Station
     * @return station.
     */
    Station station() const;
    /**
     * @brief Limit
     * @return limit.
     */
    int limit() const;
    /**
     * @brief Process data
     * @param input input.
     * @param ok if the data were correctly processed.
     * @param errorMessage an error message.
     * @return a list of info journeys.
     */
    virtual QList<InfoJourneys> processData(QIODevice *input, bool *ok = 0,
                                            QString *errorMessage = 0) = 0;
private:
    Q_DECLARE_PRIVATE(AbstractJourneysFromStationHelper)

};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_H

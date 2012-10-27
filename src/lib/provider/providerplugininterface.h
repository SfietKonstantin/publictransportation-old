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

#ifndef PUBLICTRANSPORTATION_PROVIDERPLUGININTERFACE_H
#define PUBLICTRANSPORTATION_PROVIDERPLUGININTERFACE_H

/**
 * @file providerplugininterface.h
 * @short Definition of PublicTransportation::ProviderPluginInterface
 */

#include <QtCore/QStringList>

namespace PublicTransportation
{

class Company;
class Line;
class Journey;
class Station;
/**
 * @brief Interface for a provider plugin
 *
 * A provider plugin is a Qt / C++ plugin that can
 * be load using a helper program. A provider that
 * is loaded behave exactly like any other backend.
 *
 * Creating a provider plugin have advantages, that
 * are a very simple interface, but also draw-backs,
 * like the need to compiling and linking against
 * libpublictransportation.
 *
 * For more information about creating a provider plugin,
 * see \ref PublicTransportation::ProviderPluginObject.
 *
 */
class ProviderPluginInterface
{
public:
    /**
     * @brief ~ProviderPluginInterface
     */
    virtual ~ProviderPluginInterface() {}
    /**
     * @brief Capabilities
     * @return capabilities.
     */
    virtual QStringList capabilities() const = 0;
    /**
     * @brief Retrieve copyright
     * @param request request identifier.
     */
    virtual void retrieveCopyright(const QString &request) = 0;
    /**
     * @brief Retrieve suggested stations
     * @param request request identifier.
     * @param partialStation partial station name.
     */
    virtual void retrieveSuggestedStations(const QString &request,
                                           const QString &partialStation) = 0;
    /**
     * @brief Retrieve journeys from station
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
    virtual void retrieveJourneysFromStation(const QString &request,
                                             const PublicTransportation::Station &station,
                                             int limit) = 0;
    /**
     * @brief Retrieve journeys and waiting time from station
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
    virtual void retrieveJourneysAndWaitingTimesFromStation(const QString &request,
                                                       const PublicTransportation::Station &station,
                                                            int limit) = 0;
    /**
     * @brief Retrieve waiting time
     * @param request request identifier.
     * @param company company.
     * @param line line for which the waiting time should be queried.
     * @param journey journey for which the waiting time should be queried.
     * @param station station for which the waiting time should be queried.
     */
    virtual void retrieveWaitingTime(const QString &request,
                                     const PublicTransportation::Company &company,
                                     const PublicTransportation::Line &line,
                                     const PublicTransportation::Journey &journey,
                                     const PublicTransportation::Station &station) = 0;
    /**
     * @brief Retrieve stations from journey
     * @param request request identifier.
     * @param company company.
     * @param line line for which the stations should be queried.
     * @param journey journey for which the stations should be queried.
     * @param station station for which the stations should be queried.
     */
    virtual void retrieveStationsFromJourney(const QString &request,
                                             const PublicTransportation::Company &company,
                                             const PublicTransportation::Line &line,
                                             const PublicTransportation::Journey &journey,
                                             const PublicTransportation::Station &station) = 0;
};

}

Q_DECLARE_INTERFACE(PublicTransportation::ProviderPluginInterface,
                    "org.SfietKonstantin.publictransportation.Plugin.ProviderPluginInterface/1.0")

#endif // PUBLICTRANSPORTATION_PROVIDERPLUGININTERFACE_H

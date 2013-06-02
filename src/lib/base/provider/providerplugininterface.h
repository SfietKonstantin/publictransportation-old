/*
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * The names of its contributors may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef PT2_PROVIDERPLUGININTERFACE_H
#define PT2_PROVIDERPLUGININTERFACE_H

/**
 * @file providerplugininterface.h
 * @short Definition of PT2::ProviderPluginInterface
 */

#include <QtCore/QStringList>

namespace PT2
{

class Company;
class Line;
class Ride;
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
 * libpt2.
 *
 * For more information about creating a provider plugin,
 * see \ref PT2::ProviderPluginObject.
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
    virtual QString copyright() const = 0;
    /**
     * @brief Retrieve copyright
     * @param request request identifier.
     */
//    virtual void retrieveCopyright(const QString &request) = 0;
    /**
     * @brief Retrieve suggested stations
     * @param request request identifier.
     * @param partialStation partial station name.
     */
//    virtual void retrieveSuggestedStations(const QString &request,
//                                           const QString &partialStation) = 0;
    /**
     * @brief Retrieve journeys from station
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
//    virtual void retrieveJourneysFromStation(const QString &request,
//                                             const PublicTransportation::Station &station,
//                                             int limit) = 0;
    /**
     * @brief Retrieve journeys and waiting time from station
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
//    virtual void retrieveJourneysAndWaitingTimesFromStation(const QString &request,
//                                                       const PublicTransportation::Station &station,
//                                                            int limit) = 0;
    /**
     * @brief Retrieve waiting time
     * @param request request identifier.
     * @param company company.
     * @param line line for which the waiting time should be queried.
     * @param journey journey for which the waiting time should be queried.
     * @param station station for which the waiting time should be queried.
     */
//    virtual void retrieveWaitingTime(const QString &request,
//                                     const PublicTransportation::Company &company,
//                                     const PublicTransportation::Line &line,
//                                     const PublicTransportation::Journey &journey,
//                                     const PublicTransportation::Station &station) = 0;
    /**
     * @brief Retrieve stations from journey
     * @param request request identifier.
     * @param company company.
     * @param line line for which the stations should be queried.
     * @param journey journey for which the stations should be queried.
     * @param station station for which the stations should be queried.
     */
//    virtual void retrieveStationsFromJourney(const QString &request,
//                                             const PublicTransportation::Company &company,
//                                             const PublicTransportation::Line &line,
//                                             const PublicTransportation::Journey &journey,
//                                             const PublicTransportation::Station &station) = 0;
};

}

Q_DECLARE_INTERFACE(PT2::ProviderPluginInterface,
                    "org.SfietKonstantin.publictransportation.Plugin.ProviderPluginInterface/1.0")

#endif // PT2_PROVIDERPLUGININTERFACE_H

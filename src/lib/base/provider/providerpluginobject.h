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

#ifndef PT2_PROVIDERPLUGINOBJECT_H
#define PT2_PROVIDERPLUGINOBJECT_H

/**
 * @file providerpluginobject.h
 * @short Definition of PublicTransportation::ProviderPluginObject
 */

#include "pt2_global.h"

#include <QtCore/QObject>

#include "providerplugininterface.h"

namespace PT2
{

//class InfoJourneys;
//class JourneyAndWaitingTime;
//class InfoJourneyWaitingTime;
//class WaitingTime;
/**
 * @brief Base for a provider plugin
 *
 * A provider plugin is a Qt / C++ plugin that can
 * be load using a helper program. A provider that
 * is loaded behave exactly like any other backend.
 *
 * Creating a provider plugin have advantages, that
 * are a very simple interface, but also draw-backs,
 * like the need to compiling and linking against
 * pt2.
 *
 * This class is the recommended base for a provider
 * plugin. It provides all the interfaces declared
 * in PT2::ProviderPluginInterface,
 * but also offers a QObject as a base.
 *
 * @section implementing Implementing a provider plugin
 *
 * capabilities() list the capabilities of the provider,
 * and must be implemented properly. Capabilities can be found in
 * file \ref capabilitiesconstants.h. Other methods are
 * used to perform tasks that backends perform. These methods
 * are
 * - retrieveCopyright()
 * - retrieveSuggestedStations()
 * - retrieveJourneysFromStation()
 * - retrieveJourneysAndWaitingTimesFromStation()
 * - retrieveWaitingTime()
 * - retrieveStationsFromJourney()
 *
 * These methods are already implemented by default, but do nothing.
 * In order to perform a task, a backend should implement some
 * of these methods.
 *
 * Please pay attention that retrieveJourneysFromStation(),
 * retrieveJourneysAndWaitingTimesFromStation() and retrieveWaitingTime() can be
 * refreshed by the user, therefore, this signal can be emitted several times. Be sure not
 * to abusively cache data, and provide outdated information.
 *
 * All calls are done asynchronously, and replies to called methods
 * are done though signals. The corresponding signals to the previously
 * listed methods are
 * - copyrightRetrieved()
 * - suggestedStationsRetrieved()
 * - journeysFromStationRetrieved()
 * - journeysAndWaitingTimesFromStationRetrieved()
 * - waitingTimeRetrieved()
 * - stationsFromJourneyRetrieved()
 *
 * A specific signal, errorRetrieved() can also be sent in order
 * to inform that there were an error. Error categories can be found
 * in file @ref errorid.h
 */
class PT2_EXPORT ProviderPluginObject:
        public QObject, public ProviderPluginInterface
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit ProviderPluginObject(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~ProviderPluginObject();
public Q_SLOTS:
    /**
     * @brief Retrieve copyright
     * @param request request identifier.
     */
//    virtual void retrieveCopyright(const QString &request);
    /**
     * @brief Retrieve suggested stations
     * @param request request identifier.
     * @param partialStation partial station name.
     */
//    virtual void retrieveSuggestedStations(const QString &request, const QString &partialStation);
    /**
     * @brief Retrieve journeys from station
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
//    virtual void retrieveJourneysFromStation(const QString &request,
//                                             const PublicTransportation::Station &station,
//                                             int limit);
    /**
     * @brief Retrieve journeys and waiting time from station
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
//    virtual void retrieveJourneysAndWaitingTimesFromStation(const QString &request,
//                                                       const PublicTransportation::Station &station,
//                                                            int limit);
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
//                                     const PublicTransportation::Station &station);
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
//                                             const PublicTransportation::Station &station);
Q_SIGNALS:
    /**
     * @brief Error retrieved
     * @param request request identifier.
     * @param errorId a predefined string that provides the error category.
     * @param error a human-readable string describing the error.
     */
    void errorRetrieved(const QString &request, const QString &errorId, const QString &error);
    /**
     * @brief Copyright retrieved
     * @param request request identifier.
     * @param copyright copyright and other legal informations.
     */
//    void copyrightRetrieved(const QString &request, const QString &copyright);
    /**
     * @brief Suggested stations retrieved
     * @param request request identifier.
     * @param suggestedStationList suggested stations, as a list of stations.
     */
//    void suggestedStationsRetrieved(const QString &request,
//                                  const QList<PublicTransportation::Station> &suggestedStationList);
    /**
     * @brief Journeys from station retrieved
     * @param request request identifier.
     * @param infoJourneysList a list of informations about journeys.
     */
//    void journeysFromStationRetrieved(const QString &request,
//                                 const QList<PublicTransportation::InfoJourneys> &infoJourneysList);
    /**
     * @brief Journeys and waiting times from station retrieved
     * @param request request identifier.
     * @param infoJourneyWaitingTimeList a list of informations about journeys and waiting times.
     */
//    void journeysAndWaitingTimesFromStationRetrieved(const QString &request,
//             const QList<PublicTransportation::InfoJourneyWaitingTime> &infoJourneyWaitingTimeList);
    /**
     * @brief Waiting time retrieved
     * @param request request identifier.
     * @param journeyAndWaitingTimeList a list of journeys and waiting time.
     */
//    void waitingTimeRetrieved(const QString &request,
//               const QList<PublicTransportation::JourneyAndWaitingTime> &journeyAndWaitingTimeList);
    /**
     * @brief Stations from journey
     * @param request request identifier.
     * @param stationList a list of stations.
     */
//    void stationsFromJourneyRetrieved(const QString &request,
//                                      const QList<PublicTransportation::Station> &stationList);
};

}

#endif // PT2_PROVIDERPLUGINOBJECT_H

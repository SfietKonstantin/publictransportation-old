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

#ifndef PT2_ABSTRACTBACKENDWRAPPER_H
#define PT2_ABSTRACTBACKENDWRAPPER_H

/**
 * @file abstractbackendwrapper.h
 * @short Definition of PT2::AbstractBackendWrapper
 */


#include "pt2_global.h"

#include <QtCore/QObject>
#include <QtCore/QStringList>

namespace PT2
{

class Company;
class Line;
class Ride;
class Station;
//class WaitingTime;
//class InfoJourneys;
//class JourneyAndWaitingTime;
//class InfoJourneyWaitingTime;
class AbstractBackendWrapperPrivate;

class PT2_EXPORT AbstractBackendWrapper: public QObject
{
    Q_OBJECT
    /**
     * @short Status
     */
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
public:
    /**
     * @brief Enumeration describing backend status
     */
    enum Status {
        /**
         * @short The backend is stopped
         *
         * The backend is not running.
         */
        Stopped,
        /**
         * @short The backend is launching
         *
         * The backend is launching. The process associated
         * to the backend is starting, and the backend did not
         * notified that it has started
         */
        Launching,
        /**
         * @short The backend is loading
         *
         * The backend has notified that it is started, but
         * it is loading information. It cannot be used yet.
         */
        Loading,
        /**
         * @short The backend is running
         *
         * The backend is ready to be used.
         */
        Running,
        /**
         * @short The backend is stopping
         *
         * The backend is stopping. The stop signal has been
         * sent, but the process is not yet finished.
         */
        Stopping,
        /**
         * @short The backend is in an invalid state
         */
        Invalid
    };

    /**
     * @brief Enumeration describing request types
     */
    enum RequestType {
//        /**
//         * @short Request copyright
//         */
//        CopyrightType,
//        /**
//         * @short Request suggested stations
//         */
//        SuggestStationType,
//        /**
//         * @short Request journeys from a station
//         */
//        JourneysFromStationType,
//        /**
//         * @short Request journeys and waiting times from a station
//         */
//        JourneysAndWaitingTimesFromStationType,
//        /**
//         * @short Request waiting time
//         */
//        WaitingTimeType,
//        /**
//         * @short Request stations from a journey
//         */
//        StationsFromJourneyType
    };

    /**
     * @brief Default constructor
     *
     * A set of properties can be passed to the constructor.
     * Those arguments can be used in the implementation to
     * provide, for example, additional command line arguments,
     * to the backend that controlled by this wrapper.
     *
     * @param identifier identifier for this backend wrapper.
     * @param executable command line that launch the backend.
     * @param arguments list of arguments.
     * @param parent parent object.
     */
    explicit AbstractBackendWrapper(const QString &identifier, const QString &executable,
                                    QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~AbstractBackendWrapper();
    /**
     * @brief Identifier
     * @return identifier.
     */
    QString identifier() const;
    /**
     * @brief Status
     * @return status.
     */
    Status status() const;
    /**
     * @brief Last error
     * @return last error.
     */
    QString lastError() const;
    /**
     * @brief Capabilities
     * @return capabilities.
     */
    QStringList capabilities() const;
    /**
     * @brief Copyright
     * @return copyright
     */
    QString copyright() const;
    /**
     * @brief Request copyright
     * @return request identifier.
     */
//    virtual QString requestCopyright() = 0;
    /**
     * @brief Request suggested stations
     * @param partialStation partial station name.
     * @return request identifier.
     */
//    virtual QString requestSuggestStations(const QString &partialStation) = 0;
    /**
     * @brief Request journeys from a given station
     * @param station station to query.
     * @param limit limit of the number of journeys.
     * @return request identifier.
     */
//    virtual QString requestJourneysFromStation(const Station &station, int limit) = 0;
    /**
     * @brief Request journeys and waiting times from a given station
     * @param station station to query.
     * @param limit limit of the number of journeys.
     * @return request identifier.
     */
//    virtual QString requestJourneysAndWaitingTimesFromStation(const Station &station,
//                                                              int limit) = 0;
    /**
     * @brief Request waiting time
     * @param company company.
     * @param line line for which the waiting time should be queried.
     * @param journey journey for which the waiting time should be queried.
     * @param station station for which the waiting time should be queried.
     * @return request identifier.
     */
//    virtual QString requestWaitingTime(const Company &company, const Line &line,
//                                       const Journey &journey, const Station &station) = 0;
    /**
     * @brief Request stations from journey
     * @param company company.
     * @param line line for which the stations should be queried.
     * @param journey journey for which the stations should be queried.
     * @param station station for which the stations should be queried.
     * @return request identifier.
     */
//    virtual QString requestStationsFromJourney(const Company &company, const Line &line,
//                                               const Journey &journey, const Station &station) = 0;
public Q_SLOTS:
    /**
     * @brief Launch the backend
     *
     * Launch the backend. Implementation can use the
     * executable and the arguments that are passed
     * while an instance of the backend wrapper is created
     * to perform custom launches.
     */
    virtual void launch() = 0;
    /**
     * @brief Stop the backend
     *
     * Stops the backend. The stop is asynchronous, and can
     * occur a bit after.
     */
    virtual void stop() = 0;
    /**
     * @brief Wait for stopped
     *
     * This method can be reimplemented to wait for the backend
     * to finish cleanly.
     */
    virtual void waitForStopped();
    /**
     * @brief Kill the backend
     *
     * Kills the backend. The backend should be immediately
     * stopped, as this method is called either in emergency
     * situations.
     */
    virtual void kill() = 0;
    /**
     * @brief Register error
     *
     * This method is used to reply to any request and to note that there were an
     * error during the request. Error categories can be found in file @ref errorid.h
     *
     * @param request request identifier.
     * @param errorId a predefined string that provides the error category.
     * @param error a human-readable string describing the error.
     */
    void registerError(const QString &request, const QString &errorId, const QString &error);
    /**
     * @brief Register copyright
     *
     * This method is used to register the copyright information that belongs to this backend.
     * Copyright informations should be provided by all the providers, because most of the online
     * public transportation websites requires that the copyright and other legal informations
     * should be provided.
     *
     * @param request request identifier.
     * @param copyright copyright and other legal informations.
     */
//    void registerCopyright(const QString &request, const QString &copyright);
    /**
     * @brief Register suggested stations
     *
     * This method is used to register a list of suggested stations. Returned stations are used in
     * other signals, so these stations can store additional properties. An interesting property
     * to also set is "backendName", that provides to the GUI an information about the backend
     * used for getting this station. It can be used by the user to distinguish between two
     * stations that have the same name, but are provided by different backends.
     *
     * @param request request request identifier.
     * @param suggestedStationList suggested stations, as a list of stations.
     */
//    void registerSuggestedStations(const QString &request,
//                                  const QList<PublicTransportation::Station> &suggestedStationList);
    /**
     * @brief Register journeys from station
     *
     * This method is used to register the list of companies, lines and journeys. This reply should
     * send a list of PublicTransportation::InfoJourneys. Each information about journeys contains
     * the journeys for a given company and a given line, but in a station, there might be several
     * journeys for the same line heading to different directions, so an information about journeys
     * contains a list of journey-station pairs. Adding a station to the journey help giving
     * more accurate results, since the station might contain some station-specific properties
     * that might help for other methods. All the components, that are the company, the line, the
     * journey and the station are used by other signals.
     *
     * @param request request request identifier.
     * @param infoJourneyList a list of informations about journeys.
     */
//    void registerJourneysFromStation(const QString &request,
//                                  const QList<PublicTransportation::InfoJourneys> &infoJourneyList);
    /**
     * @brief Register journeys and waiting times from station
     *
     * This method is used to register the list of companies, lines and journeys. This reply should
     * send a list of PublicTransportation::InfoJourneyWaitingTime. Each information about journeys
     * contains a company, line, journey and station. Contrary to registerJourneysFromStation(),
     * this method register different journeys for the same line in different entries, that might
     * be more suited for some providers (especially for planes and trains). All the components,
     * that are the company, the line, the journey and the station are used by other signals.
     *
     * @param request request request identifier.
     * @param infoJourneyWaitingTimeList a list of informations about journeys and waiting times.
     */
//    void registerJourneysAndWaitingTimesFromStation(const QString &request,
//             const QList<PublicTransportation::InfoJourneyWaitingTime> &infoJourneyWaitingTimeList);
    /**
     * @brief Register waiting time
     *
     * This method is used to register the list of waiting time,as a list of
     * PublicTransportation::JourneyAndWaitingTime.
     *
     * @param request request request identifier.
     * @param journeyAndWaitingTimeList a list of journeys and waiting time.
     */
//    void registerWaitingTime(const QString &request,
//                             const QList<JourneyAndWaitingTime> &journeyAndWaitingTimeList);
    /**
     * @brief Register stations from journey
     *
     * This method is used to register the list stations for the requested journey.
     *
     * @param request request request identifier.
     * @param stationList a list of stations.
     */
//    void registerStationsFromJourney(const QString &request,
//                                     const QList<PublicTransportation::Station> &stationList);
Q_SIGNALS:
    /**
     * @brief Status changed
     */
    void statusChanged();
    /**
     * @brief Capabilities changed
     */
    void capabilitiesChanged();
    /**
     * @brief Copyright changed
     */
    void copyrightChanged();
    /**
     * @brief Error registered
     *
     * This signal is used to relay registered errors.
     *
     * @param request request identifier.
     * @param errorId a predefined string that provides the error category.
     * @param error a human-readable string describing the error.
     */
    void errorRegistered(const QString &request, const QString &errorId, const QString &error);
    /**
     * @brief Copyright registered
     *
     * This signal is used to relay registered copyright.
     *
     * @param request request identifier.
     * @param copyright copyright and other legal informations.
     */
//    void copyrightRegistered(const QString &request, const QString &copyright);
    /**
     * @brief Suggested stations registered
     *
     * This signal is used to relay registered suggested stations.
     *
     * @param request request identifier.
     * @param suggestedStations suggested stations, as a list of stations.
     */
//    void suggestedStationsRegistered(const QString & request,
//                                     const QList<PublicTransportation::Station> &suggestedStations);
    /**
     * @brief Journeys from station registered
     *
     * This signal is used to relay registered journeys from station.
     *
     * @param request request identifier.
     * @param infoJourneys a list of informations about journeys.
     */
//    void journeysFromStationRegistered(const QString &request,
//                                     const QList<PublicTransportation::InfoJourneys> &infoJourneys);
    /**
     * @brief Journeys and waiting times from station registered
     *
     * This signal is used to relay registered journeys and waiting times
     * from station.
     *
     * @param request request identifier.
     * @param infoJourneyAndWaitingTimes a list of informations about journeys and waiting times.
     */
//    void journeysAndWaitingTimesFromStationRegistered(const QString &request,
//             const QList<PublicTransportation::InfoJourneyWaitingTime> &infoJourneyAndWaitingTimes);
    /**
     * @brief Waiting time registered
     *
     * This signal is used to relay registered waiting time.
     *
     * @param request request identifier.
     * @param journeyAndWaitingTimeList a list of journeys and waiting time.
     */
//    void waitingTimeRegistered(const QString &request,
//               const QList<PublicTransportation::JourneyAndWaitingTime> &journeyAndWaitingTimeList);
    /**
     * @brief Stations from journey registered
     *
     * This signal is used to relay registered stations.
     *
     * @param request request identifier.
     * @param stationList a list of stations.
     */
//    void stationsFromJourneyRegistered(const QString &request,
//                                       const QList<PublicTransportation::Station> &stationList);
protected:
    /**
     * @brief D-pointer based constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractBackendWrapper(AbstractBackendWrapperPrivate &dd, QObject *parent);
    /**
     * @brief Executable
     * @return executable.
     */
    QString executable() const;
    /**
     * @brief Set status
     * @param status status to set.
     */
    void setStatus(Status status);
    /**
     * @brief Set last error
     * @param lastError error to set.
     */
    void setLastError(const QString &lastError);
    /**
     * @brief Set capabilities
     * @param capabilities capabilities to set.
     */
    void setCapabilities(const QStringList &capabilities);
    /**
     * @brief Set copyright
     * @param copyright copyright to set.
     */
    void setCopyright(const QString &copyright);
    /**
     * @brief Create request
     *
     * This method is used to create a request, and register it in the
     * backend wrapper. This method is useful whenever a request is
     * performed, in order to get a request identifier.
     *
     * @param requestType request type.
     * @return request identifier.
     */
    QString createRequest(RequestType requestType);

    /**
     * @brief D-pointer
     */
    QScopedPointer<AbstractBackendWrapperPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractBackendWrapper)
};

}

#endif // PT2_ABSTRACTBACKENDWRAPPER_H

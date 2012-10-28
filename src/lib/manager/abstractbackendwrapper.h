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

#ifndef PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_H
#define PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_H

/**
 * @file abstractbackendwrapper.h
 * @short Definition of PublicTransportation::AbstractBackendWrapper
 */


#include "publictransportation_global.h"

#include <QtCore/QObject>
#include <QtCore/QStringList>

namespace PublicTransportation
{

class Company;
class Line;
class Journey;
class Station;
class WaitingTime;
class InfoJourneys;
class JourneyAndWaitingTime;
class InfoJourneyWaitingTime;
class AbstractBackendWrapperPrivate;

/**
 * @brief Base class for a backend wrapper
 *
 * This class provides a base for any backend wrapper.
 * A backend wrapper is an interface between a backend
 * that is usually a process that is spawned, and that is
 * used to perform specific tasks in an asynchronous ways.
 *
 * This class is used to perform the interface between the
 * spawned backend and the applications that is used to
 * display informations.
 *
 * In order to do that, the backend wrapper provides methods
 * like launch(), stop() and kill() that should be implemented,
 * as well as a set of properties, like status(), that is used
 * to get the current backend status.
 *
 * In order to be managed more easily, all backend wrappers have
 * an identifier, that is passed in the constructor, and that
 * should be unique for each backend. This identifier can also
 * be passed to the backend if needed.
 *
 * @section capabilities Capabilities
 *
 * A backend have capabilities that might vary from backend to
 * backend. Those capabilities provides what the backend can
 * deliver. A sane application should never call methods that
 * are related to a capability that is not provided by the backend,
 * as the behaviour might be unknown.
 *
 * @section managingBackend Managing backend
 *
 * The backend wrapper is used to manage backend and provide
 * a neat interface of the backend to the application. When
 * a backend is launched, the status should be set to
 * AbstractBackendWrapper::Launching. When it is being stopped,
 * it should be set to AbstractBackendWrapper::Stopping. While the
 * backend ping the wrapper back, it should also register its
 * capabilities. While an error occur in the backend (like failing
 * to register a DBus service, for example), the
 * AbstractBackendWrapper::Invalid status should be set.
 *
 * Three helper methods are used to help implementing backend wrapper:
 * - setStatus()
 * - setCapabilities()
 * - setLastError()
 *
 * @section relayingReplies Relaying replies
 *
 * This class is also used to relay replies from the backend,
 * using specific combinaison of signals and slots. When the
 * backend replied, a slot like \b registerAbc should be called.
 * This signal will emit \b abcRegistered. Here is the list of
 * signals / slots used for the relay
 * - registerError()
 * - registerCopyright()
 * - registerSuggestedStations()
 * - registerJourneysFromStation()
 * - registerWaitingTime()
 * - registerStationsFromJourney()
 *
 * - errorRegistered()
 * - copyrightRegistered()
 * - suggestedStationsRegistered()
 * - journeysFromStationRegistered()
 * - waitingTimeRegistered()
 * - stationsFromJourneyRegistered()
 *
 * This class also provides interfaces for implementing some capabilities
 * of the providers, that should be implemented in subclasses. They are all
 * of the form \b requestAbc.
 * - requestCopyright()
 * - requestSuggestStations()
 * - requestJourneysFromStation()
 * - requestWaitingTime()
 * - requestStationsFromJourney()
 *
 * All these requests returns a request identifier, and all responses will
 * provide the same identifier, in order to identify the request more easily.
 *
 * Implementing requests can be done by calling createRequest(). This method
 * provides a request identifier, and register the request as pending. When
 * requests are answered, they are removed. The abstract backend wrapper can
 * then takes care of request tracking.
 *
 * Remark that there is no request for capabilities. It is because
 * registering capabilities is something that backends should do
 * automatically, in order to be validated. Subclasses should implement
 * a method to perform this registration (that should use setCapabilities())
 * and that should set the status to AbstractBackendWrapper::Launched.
 *
 */
class PUBLICTRANSPORTATION_EXPORT AbstractBackendWrapper: public QObject
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
         */
        Stopped,
        /**
         * @short The backend is launching
         */
        Launching,
        /**
         * @short The backend is launched
         */
        Launched,
        /**
         * @short The backend is stopping
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
        /**
         * @short Request copyright
         */
        CopyrightType,
        /**
         * @short Request suggested stations
         */
        SuggestStationType,
        /**
         * @short Request journeys from a station
         */
        JourneysFromStationType,
        /**
         * @short Request journeys and waiting times from a station
         */
        JourneysAndWaitingTimesFromStationType,
        /**
         * @short Request waiting time
         */
        WaitingTimeType,
        /**
         * @short Request stations from a journey
         */
        StationsFromJourneyType
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
                                    const QMap<QString, QString> &arguments, QObject *parent = 0);
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
     * @brief Request copyright
     * @return request identifier.
     */
    virtual QString requestCopyright() = 0;
    /**
     * @brief Request suggested stations
     * @param partialStation partial station name.
     * @return request identifier.
     */
    virtual QString requestSuggestStations(const QString &partialStation) = 0;
    /**
     * @brief Request journeys from a given station
     * @param station station to query.
     * @param limit limit of the number of journeys.
     * @return request identifier.
     */
    virtual QString requestJourneysFromStation(const Station &station, int limit) = 0;
    /**
     * @brief Request journeys and waiting times from a given station
     * @param station station to query.
     * @param limit limit of the number of journeys.
     * @return request identifier.
     */
    virtual QString requestJourneysAndWaitingTimesFromStation(const Station &station,
                                                              int limit) = 0;
    /**
     * @brief Request waiting time
     * @param company company.
     * @param line line for which the waiting time should be queried.
     * @param journey journey for which the waiting time should be queried.
     * @param station station for which the waiting time should be queried.
     * @return request identifier.
     */
    virtual QString requestWaitingTime(const Company &company, const Line &line,
                                       const Journey &journey, const Station &station) = 0;
    /**
     * @brief Request stations from journey
     * @param company company.
     * @param line line for which the stations should be queried.
     * @param journey journey for which the stations should be queried.
     * @param station station for which the stations should be queried.
     * @return request identifier.
     */
    virtual QString requestStationsFromJourney(const Company &company, const Line &line,
                                               const Journey &journey, const Station &station) = 0;
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
    void registerCopyright(const QString &request, const QString &copyright);
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
    void registerSuggestedStations(const QString &request,
                                  const QList<PublicTransportation::Station> &suggestedStationList);
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
    void registerJourneysFromStation(const QString &request,
                                  const QList<PublicTransportation::InfoJourneys> &infoJourneyList);
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
    void registerJourneysAndWaitingTimesFromStation(const QString &request,
             const QList<PublicTransportation::InfoJourneyWaitingTime> &infoJourneyWaitingTimeList);
    /**
     * @brief Register waiting time
     *
     * This method is used to register the list of waiting time,as a list of
     * PublicTransportation::JourneyAndWaitingTime.
     *
     * @param request request request identifier.
     * @param journeyAndWaitingTimeList a list of journeys and waiting time.
     */
    void registerWaitingTime(const QString &request,
                             const QList<JourneyAndWaitingTime> &journeyAndWaitingTimeList);
    /**
     * @brief Register stations from journey
     *
     * This method is used to register the list stations for the requested journey.
     *
     * @param request request request identifier.
     * @param stationList a list of stations.
     */
    void registerStationsFromJourney(const QString &request,
                                     const QList<PublicTransportation::Station> &stationList);
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
    void copyrightRegistered(const QString &request, const QString &copyright);
    /**
     * @brief Suggested stations registered
     *
     * This signal is used to relay registered suggested stations.
     *
     * @param request request identifier.
     * @param suggestedStations suggested stations, as a list of stations.
     */
    void suggestedStationsRegistered(const QString & request,
                                     const QList<PublicTransportation::Station> &suggestedStations);
    /**
     * @brief Journeys from station registered
     *
     * This signal is used to relay registered journeys from station.
     *
     * @param request request identifier.
     * @param infoJourneys a list of informations about journeys.
     */
    void journeysFromStationRegistered(const QString &request,
                                     const QList<PublicTransportation::InfoJourneys> &infoJourneys);
    /**
     * @brief Journeys and waiting times from station registered
     *
     * This signal is used to relay registered journeys and waiting times
     * from station.
     *
     * @param request request identifier.
     * @param infoJourneyAndWaitingTimes a list of informations about journeys and waiting times.
     */
    void journeysAndWaitingTimesFromStationRegistered(const QString &request,
             const QList<PublicTransportation::InfoJourneyWaitingTime> &infoJourneyAndWaitingTimes);
    /**
     * @brief Waiting time registered
     *
     * This signal is used to relay registered waiting time.
     *
     * @param request request identifier.
     * @param journeyAndWaitingTimeList a list of journeys and waiting time.
     */
    void waitingTimeRegistered(const QString &request,
               const QList<PublicTransportation::JourneyAndWaitingTime> &journeyAndWaitingTimeList);
    /**
     * @brief Stations from journey registered
     *
     * This signal is used to relay registered stations.
     *
     * @param request request identifier.
     * @param stationList a list of stations.
     */
    void stationsFromJourneyRegistered(const QString &request,
                                       const QList<PublicTransportation::Station> &stationList);
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
     * @brief Arguments
     * @return arguments.
     */
    QMap<QString, QString> arguments() const;
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

#endif // PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_H

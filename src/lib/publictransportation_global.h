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

#ifndef PUBLICTRANSPORTATION_GLOBAL_H
#define PUBLICTRANSPORTATION_GLOBAL_H

/**
 * @file publictransportation_global.h
 * @short Global publictransportation library header
 */

#include <QtCore/qglobal.h>

/**
 * \mainpage publictransportation
 *
 * publictransportation is an application that
 * deals with public transportation, providing
 * realtime information, timetable and other
 * features.
 *
 * Instead of being yet another monolitic public
 * transportation app, publictransportation is
 * splitted into a library that is designed to
 * be extensible, an application that is only a
 * frontend of the library, and several plugins
 * or even helper scripts, that are used to provide
 * information about public transportation companies.
 *
 * \section sectionDesign Design
 *
 * libpublictransportation is designed to be flexible
 * and to load information from several sources. It
 * provides a   API that allows interfacing with
 * nearly all programming languages. It also provides
 * a helper app, that is called a provider, and that can
 * load C++/Qt plugin to retrieve information.
 *
 * Extending libpublictransportation can be done
 * in two ways
 * - write a program or a script that profits from the \ref dbusApi
 * - write a provider plugin and profit from the \ref cppApi.
 *
 * publictransportation manages providers and scripts and
 * launch them when needed, and communicate with DBus to them.
 * This have several advantages, notably a fully asynchronous
 * process and a very simple architecture.
 *
 * \section futureWorks Future works
 *
 * Due to the hard dependency on DBus, it is impossible
 * to make publictransportation on non-Linux systems.
 * However, the DBus part is separated from the logic
 * and it might be possible to extend publictransportation
 * to work using sockets, and then, on other platforms. However
 * scripts using the DBus API won't work.
 */
/**
 * \page glossary Glossary
 *
 * \section company Company
 *
 * A company provides a transportation service. A company can
 * use buses, trains, planes, boats to provide this service, and
 * can use different ways.
 *
 * Companies are usually described by a name. They can also have a
 * logo or other features.
 *
 * \section line Line
 *
 * A transportation line is a way that companies uses to classify
 * their transportation offer. A line often serve fixed destinations
 * or at least, fixed areas.
 *
 * Lines are usually described by a code, sometimes a name. They can
 * also have a more verbose description, a color and other features.
 *
 * \section journey Journey
 *
 * A direction describes a particular travel. If a line serves city
 * A and B, a direction might be from A to B and another is from B to A.
 *
 * Journeys are usually described by a name, that is often the name
 * of the destination city / area. They can also have some other features.
 *
 * For some cases, there is no difference between a line and a journey.
 * For example, plane travels may have a code, that is the code of the
 * line, and this line might only have one direction, that is from the
 * initial city to the destination.
 *
 * \section station Station
 *
 * A station describes a stopping point on the journey. For a given line and
 * different journeys, there might be difference in stopping points (like express
 * trains compared to local trains).
 *
 * Station are usually described by a name. They can also have some other
 * features.
 */
/**
 * \page api API
 *
 * \section Design
 *
 * publictransportation uses a fully asynchronous API. Requests
 * are done calling methods that immediately returns, and responses
 * are carried using signals.
 *
 * publictransportation runs several helper programs or scripts, called
 * \e backends, that uses DBus to react to user input and return replies.
 * These backends are represented using the PublicTransportation::AbstractBackendWrapper class.
 * This class provides a bridge between the DBus API and the GUI.
 *
 * A typical call is described as follow
 * -# Replying to user input, a request is sent. It is done using by calling
 *    \b requestFoo method on the backend wrapper.
 * -# The backend wrapper send a DBus signal, \b fooRequested
 * -# The backend respond to the signal, and transmit data using the DBus
 *    method \b registerFoo
 * -# The backend wrapper get the data and send \b fooRegistered to notify the
 *    GUI that information is available.
 *
**
 * @section dBusTypes DBus types
 *
 * Several structures are used in publictransportation, and send through
 * DBus. This section describes the content of those structures.
 *
 * @subsection transportationObject Transportation object
 *
 * A transportation object contains the properties describing an entity
 * related to public transportation. The following entities are
 * transportation objects.
 * - A transportation company
 * - A line
 * - A journey
 * - A station
 *
 * All these entities are stored the same way, using
 * - A disambiguation parameter, that is a dictionnary of variant
 * - A name, that is a string
 * - Some properties, that is another dictionnary of variant.
 *
 * The signature of a transportation object is
 * \code
 * (a{sv}sa{sv})
 * \endcode
 *
 * @subsection waitingTime Waiting time
 *
 * Waiting time contains the time to wait before a transportation mode
 * arrives. Those entities are stored using
 * - The time before arrival, in minutes
 * - Some properties, that are a dictionnary of variant.
 *
 * The signature of a waiting time entity is
 * \code
 * (ia{sv})
 * \endcode
 *
 *
 * @subsection infoJourneys Informations about journeys
 *
 * Information about journeys are stored as a complex structure, that
 * takes in account the company that provide the journey, the line
 * on which the journey is performed, and additional information about
 * the departure station (if needed). It then stores
 * - A company
 * - A line
 * - A list of journey-station pair
 *
 * The signature for an information about journeys is
 * \code
 * ((a{sv}sa{sv})(a{sv}sa{sv})a((a{sv}sa{sv})(a{sv}sa{sv})))
 * \endcode
 *
 * @subsection infoJourneyWaitingTime Informations about a journey and waiting time
 *
 * Information about a journey and waiting time are stored as a complex
 * structure, that takes in account the company that provide the journey,
 * the line on which the journey is performed, additional information
 * about the departure station (if needed) and the waiting time. It then stores
 * - A company
 * - A line
 * - A journey
 * - A station
 * - A waiting time
 *
 * The signature for an information about journeys is
 * \code
 * ((a{sv}sa{sv})(a{sv}sa{sv})(a{sv}sa{sv})(a{sv}sa{sv})(ia{sv}))
 * \endcode
 *
 *
 * \section dbusApi DBus API
 *
 * publictransportation uses \e org.SfietKonstantin.publictransportation as
 * service name, and all backends have a specific path (\e /backend/somepath) that
 * should be used to communicate. The path is provided as an argument while the
 * backend is launched, using --identifier \<somepath\>.
 *
 * \subsection registerBackend registerBackend
 *
 * This method is used to register the backend. It should be called when the backend
 * is launched in order or publictransportation to know about it's capabilities.
 * Capabilities can be found in file \ref capabilitiesconstants.h
 *
 * \b Parameters
 * - as \e capabilities Backend capabilities, that are send as a list of strings.
 *
 * \subsection registerError registerError
 *
 * This method is used to reply to any request and to note that there were an
 * error during the request. Error categories can be found in file @ref errorid.h
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - s \e errorId A predefined string that provides the error category.
 * - s \e error A human-readable string describing the error.
 *
 * \subsection copyrightRequested copyrightRequested [signal]
 *
 * This signal is used to notify that copyright informations are requested. Copyright
 * informations should be provided by all the providers, because most of the online
 * public transportation websites requires that the copyright and other legal informations
 * should be provided.
 *
 * \b Parameters
 * - s \e request Request identifier.
 *
 * \subsection registerCopyright registerCopyright
 *
 * This method is used to register the copyright information that belongs to this backend.
 * It should be used to reply to \ref copyrightRequested. Copyright
 * informations should be provided by all the providers, because most of the online
 * public transportation websites requires that the copyright and other legal informations
 * should be provided.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - s \e copyright Copyright and other legal informations.
 *
 * \subsection suggestStationsRequested suggestStationsRequested [signal]
 *
 * This signal is used to notify that the backend should suggest stations based on a partial
 * station name. This method is used for searching and autocompletion.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - s \e partialStation Partial station name.
 *
 * \subsection registerSuggestedStations registerSuggestedStations
 *
 * This method is used to register a list of suggested stations. It should reply to
 * \ref suggestStationsRequested. Returned stations are used in \ref journeysFromStationRequested,
 * so these stations can store additional properties. An interesting property to also set is
 * "backendName", that provides to the GUI an information about the backend used for getting
 * this station. It can be used by the user to distinguish between two stations that have
 * the same name, but are provided by different backends.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - a\ref transportationObject "(a{sv}sa{sv})" \e suggestedStationList Suggested stations,
 *   as a list of stations.
 *
 * \subsection journeysFromStationRequested journeysFromStationRequested [signal]
 *
 * This signal is used to notify that the backend should provide a list of informations,
 * combining a company, a line, and several journeys from the same line, like the following
 *
 * \code
 * Company 1 & Line 1
 *   Journey 1
 *   Journey 2
 * Company 2 & Line 3
 *   Journey 1
 *   Journey 2
 *   Journey 3
 * \endcode
 *
 * A limit of the number of journeys that should be listed is provided, but it is not a
 * hard limit. It can be used for some information sources that, otherwise, might download
 * a lot of data.
 *
 * Please pay attention that the list of journeys can be refreshed by the user, therefore,
 * this signal can be emitted several times. Be sure not to abusively cache data, and provide
 * outdated information.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - \ref transportationObject "(a{sv}sa{sv})" \e station Station to query.
 * - i \e limit Limit of the number of journeys.
 *
 * \subsection registerJourneysFromStation registerJourneysFromStation
 *
 * This method is used to register the list of companies, lines and journeys, in order to
 * respond to \ref journeysFromStationRequested. This reply should send a list of
 * \ref infoJourneys "informations about journeys". Each information about journeys contains
 * the journeys for a given company and a given line, but in a station, there might be several
 * journeys for the same line heading to different directions, so an information about journeys
 * contains a list of journey-station pairs. Adding a station to the journey help giving
 * more accurate results, since the station might contain some station-specific properties
 * that might help for other methods. All the components, that are the company, the line, the
 * journey and the station are used by \ref waitingTimeRequested.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - a\ref infoJourneys "((a{sv}sa{sv})(a{sv}sa{sv})a((a{sv}sa{sv})(a{sv}sa{sv})))"
 *   \e infoJourneysList A list of informations about journeys.
 *
 * \subsection journeysAndWaitingTimesFromStationRequested journeysAndWaitingTimesFromStationRequested [signal]
 *
 * This signal is used to notify that the backend should provide a list of informations,
 * combining a company, a line, a journey and a station, as well as a waiting time. This
 * list of information have the same role as \ref journeysFromStationRequested, but might be
 * more suited for some backends that lists results for planes or trains.
 *
 * A limit of the number of journeys that should be listed is provided, but it is not a
 * hard limit. It can be used for some information sources that, otherwise, might download
 * a lot of data.
 *
 * Please pay attention that the list of journeys can be refreshed by the user, therefore,
 * this signal can be emitted several times. Be sure not to abusively cache data, and provide
 * outdated information.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - \ref transportationObject "(a{sv}sa{sv})" \e station Station to query.
 * - i \e limit Limit of the number of journeys.
 *
 * \subsection registerJourneysAndWaitingTimesFromStation registerJourneysAndWaitingTimesFromStation
 *
 * This method is used to register the list of companies, lines and journeys, in order to
 * respond to \ref journeysAndWaitingTimesFromStationRequested. This reply should send a list of
 * \ref infoJourneyWaitingTime "informations about journeys and waiting times". Each information
 * about journeys and waiting times contains a journey for a given company and a given line as well
 * as the waiting time. Adding a station to the journey help giving more accurate results, since
 * the station might contain some station-specific properties that might help for other methods.
 * All the components, that are the company, the line, the journey and the station are used by
 * \ref waitingTimeRequested.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - a\ref infoJourneyWaitingTime "(a{sv}sa{sv})(a{sv}sa{sv})(a{sv}sa{sv})(a{sv}sa{sv})(ia{sv}))"
 *   \e infoJourneyWaitingTimeList A list of informations about journeys and waiting times.
 *
 * \subsection waitingTimeRequested waitingTimeRequested
 *
 * This signal is used to notify that the backend should provide a list of waiting time at
 * a given station, providing also a given company, line and journey.
 *
 * Please pay attention that the list of waiting time can be refreshed by the user, therefore,
 * this signal can be emitted several times. Be sure not to abusively cache data, and provide
 * outdated information.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - \ref transportationObject "(a{sv}sa{sv})" \e company Company.
 * - \ref transportationObject "(a{sv}sa{sv})" \e line Line for which the waiting time should
 *   be queried.
 * - \ref transportationObject "(a{sv}sa{sv})" \e journey Journey for which the waiting time should
 *   be queried.
 * - \ref transportationObject "(a{sv}sa{sv})" \e station Station for which the waiting time should
 *   be queried.
 *
 * \subsection registerWaitingTime registerWaitingTime
 *
 * This method is used to register the list of waiting time, in order to respond to
 * \ref waitingTimeRequested.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - a\ref waitingTime "(ia{sv})" \e waitingTimeList A list of waiting time.
 *
 * \subsection stationsFromJourneyRequested stationsFromJourneyRequested
 *
 * This signal is used to notify that the backend should provide a list of station for a given
 * journey, providing a station from which the journey starts as well as a company and a line.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - \ref transportationObject "(a{sv}sa{sv})" \e company Company.
 * - \ref transportationObject "(a{sv}sa{sv})" \e line Line for which the stations should
 *   be queried.
 * - \ref transportationObject "(a{sv}sa{sv})" \e journey Journey for which stations should
 *   be queried.
 * - \ref transportationObject "(a{sv}sa{sv})" \e station Station for which the stations should
 *   be queried.
 *
 * \subsection registerStationsFromJourney registerStationsFromJourney
 *
 * This method is used to register the list of stations, in order to respond to
 * \ref stationsFromJourneyRequested.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - a\ref transportationObject "(a{sv}sa{sv})" \e stationList A list of stations.
 *
 *
 * \section cppApi C++ API
 *
 * The C++ API is basically an interface (actually a QObject) that should be subclassed and
 * compiled as a plugin. This interface provides all the methods that allows to interact in a
 * way that is similar to the DBus API.
 *
 * However, methods in this interface have different names, and are the antagonist of those
 * used in the DBus API.
 *
 * The previous typical call is now completed with calls to the plugin methods:
 * -# Replying to user input, a request is sent. It is done using by calling
 *    requestFoo method on the backend wrapper.
 * -# The backend wrapper send a DBus signal, fooRequested
 * -# The plugin, loaded in a backend, reply to the signal with \b retrieveFoo,
 *    a virtual method that is subclassed in order to retrieve the information.
 * -# When the information is retrieved, the plugin emit \b fooRetrieved, that
 *    automatically trigger registerFoo.
 * -# The backend wrapper get the data and send fooRegistered to notify the
 *    GUI that information is available.
 *
 * All DBus signals will then correspond to a Qt slot in the interface, with the
 * same signature, and all DBus methods will correspond to a Qt signal.
 *
 * See PublicTransportation::ProviderPluginObject for more information.
 */

/**
 * @namespace PublicTransportation
 * @short Namespace for libpublictransportation
 */

/**
 * \def PUBLICTRANSPORTATION_EXPORT
 * @short Library export or import
 */

#if defined(PUBLICTRANSPORTATION_LIBRARY)
#  define PUBLICTRANSPORTATION_EXPORT Q_DECL_EXPORT
#else
#  define PUBLICTRANSPORTATION_EXPORT Q_DECL_IMPORT
#endif

#endif // PUBLICTRANSPORTATION_GLOBAL_H

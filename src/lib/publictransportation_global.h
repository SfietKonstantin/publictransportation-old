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
 * provides a DBus API that allows interfacing with
 * nearly all programming languages. It also provides
 * a helper app, that is called a provider, and that can
 * load C++/Qt plugin to retrieve information.
 *
 * Extending libpublictransportation can be done
 * in two ways
 * - write a program or a script that profits from the DBus API
 * - write a provider plugin and profit from the C++ API.
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
 * These backends are represented using the AbstractBackendWrapper class.
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
 * \section DBus API
 *
 * publictransportation uses \e org.SfietKonstantin.publictransportation as
 * service name, and all backends have a specific path (\e /backend/somepath) that
 * should be used to communicate. The path is provided as an argument while the
 * backend is launched, using --identifier <somepath>.
 *
 * \subsection registerBackend org.SfietKonstantin.publictransportation.registerBackend
 *
 * This method is used to register the backend. It should be called when the backend
 * is launched in order or publictransportation to know about it's capabilities.
 *
 * \b Parameters
 * - as \e capabilities Backend capabilities, that are send as a list of strings.
 *
 * \subsection registerError org.SfietKonstantin.publictransportation.registerError
 *
 * This method is used to reply to any request and to note that there were an
 * error during the request.
 *
 * @todo this method is still WIP
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - s \e error A string describing the error.
 *
 * \subsection copyrightRequested org.SfietKonstantin.publictransportation.copyrightRequested
 *
 * This signal is used to notify that copyright informations are requested. Copyright
 * informations should be provided by all the providers, because most of the online
 * public transportation websites requires that the copyright and other legal informations
 * should be provided.
 *
 * \b Parameters
 * - s \e request Request identifier.
 * - s \e copyright Copyright and other legal informations.
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

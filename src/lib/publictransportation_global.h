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
 * libpublictransportation manages providers and scripts and
 * launch them when needed, and communicate with DBus to them.
 * This have several advantages, notably a fully asynchronous
 * process and a very simple architecture.
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

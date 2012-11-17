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

#ifndef PUBLICTRANSPORTATIONPLUGINHELPER_GLOBAL_H
#define PUBLICTRANSPORTATIONPLUGINHELPER_GLOBAL_H

/**
 * @file publictransportationpluginhelper_global.h
 * @short Global header for publictransportation helper library for plugins
 */

/**
 * @page Helper library for plugins
 *
 * publictransportation ships a library that provides a lot of classes
 * dealing with asynchronous methods, such as network retrieving.
 *
 * These classes can be used to hide the network reply management, and
 * provide conveinent ways to deal with asynchronous data.
 *
 * A list of these classes:
 * - PublicTransportation::PluginHelper::AbstractOnlineHelper
 * - PublicTransportation::PluginHelper::AbstractSuggestedStationsHelper
 * - PublicTransportation::PluginHelper::AbstractCachedSuggestedStationsHelper
 * - PublicTransportation::PluginHelper::AbstractJourneysFromStationHelper
 * - PublicTransportation::PluginHelper::AbstractWaitingTimeHelper
 * - PublicTransportation::PluginHelper::OfflineSuggestedStationsHelper
 * - PublicTransportation::PluginHelper::OfflineXmlJourneysFromStationHelper
 */

/**
 * @namespace PublicTransportation::PluginHelper
 * @short Namespace for publictransportation helper library for plugins
 */


#include <QtCore/qglobal.h>

/**
 * \def PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT
 * @short Library export or import
 */

#if defined(PUBLICTRANSPORTATIONPLUGINHELPER_LIBRARY)
#  define PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT Q_DECL_EXPORT
#else
#  define PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT Q_DECL_IMPORT
#endif

#endif // PUBLICTRANSPORTATIONPLUGINHELPER_GLOBAL_H

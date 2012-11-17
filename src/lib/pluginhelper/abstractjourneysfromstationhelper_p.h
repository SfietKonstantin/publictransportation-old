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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_P_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_P_H

// Warning
//
// This file exists for the convenience
// of other publictransportation classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file abstractjourneysfromstationhelper_p.h
 * @short Definition of PublicTransportation::PluginHelper::AbstractJourneysFromStationHelperPrivate
 */

#include "abstractjourneysfromstationhelper.h"
#include "abstractonlinehelper_p.h"

#include "common/station.h"

class QNetworkReply;
namespace PublicTransportation
{

namespace PluginHelper
{

/**
 * @internal
 * @brief Private class used in
 * PublicTransportation::PluginHelper::AbstractJourneysFromStationHelper
 */
class AbstractJourneysFromStationHelperPrivate: public AbstractOnlineHelperPrivate
{
public:
    /**
     * @internal
     * @brief Constructor
     * @param q Q-pointer
     */
    AbstractJourneysFromStationHelperPrivate(AbstractJourneysFromStationHelper *q);
    /**
     * @internal
     * @brief Implementation of AbstractOnlineHelperPrivate::processReply()
     *
     * @param reply Network reply.
     */
    virtual void processReply(QNetworkReply *reply);
    /**
     * @internal
     * @brief Implementation of AbstractOnlineHelperPrivate::cleanup()
     */
    virtual void cleanup();
    /**
     * @internal
     * @brief Station
     */
    Station station;
    /**
     * @internal
     * @brief Limit
     */
    int limit;
private:
    Q_DECLARE_PUBLIC(AbstractJourneysFromStationHelper)
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_P_H

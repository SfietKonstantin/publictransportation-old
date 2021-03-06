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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_P_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_P_H

// Warning
//
// This file exists for the convenience
// of other publictransportation classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file abstractwaitingtimehelper_p.h
 * @short Definition of PublicTransportation::PluginHelper::AbstractWaitingTimeHelperPrivate
 */

#include "abstractwaitingtimehelper.h"
#include "abstractonlinehelper_p.h"

#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"

namespace PublicTransportation
{

namespace PluginHelper
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::PluginHelper::AbstractWaitingTimeHelper
 */
class AbstractWaitingTimeHelperPrivate: public AbstractOnlineHelperPrivate
{
public:
    /**
     * @internal
     * @brief Constructor
     * @param q Q-pointer
     */
    AbstractWaitingTimeHelperPrivate(AbstractWaitingTimeHelper *q);
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
     * @brief Company
     */
    Company company;
    /**
     * @internal
     * @brief Line
     */
    Line line;
    /**
     * @internal
     * @brief Journey
     */
    Journey journey;
    /**
     * @internal
     * @brief Station
     */
    Station station;
private:
    Q_DECLARE_PUBLIC(AbstractWaitingTimeHelper)
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_P_H

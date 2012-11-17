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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTONLINEHELPER_P_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTONLINEHELPER_P_H


// Warning
//
// This file exists for the convenience
// of other publictransportation classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file abstractonlinehelper_p.h
 * @short Definition of PublicTransportation::PluginHelper::AbstractOnlineHelperPrivate
 */

#include "abstractonlinehelper.h"
#include <QtNetwork/QNetworkReply>

class QIODevice;
class QNetworkReply;
namespace PublicTransportation
{

namespace PluginHelper
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::PluginHelper::AbstractOnlineHelper
 */
class AbstractOnlineHelperPrivate
{
public:
    /**
     * @internal
     * @brief Constructor
     * @param q Q-pointer
     */
    AbstractOnlineHelperPrivate(AbstractOnlineHelper *q);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~AbstractOnlineHelperPrivate();
    /**
     * @internal
     * @brief Slot finished
     */
    void slotFinished();
    /**
     * @internal
     * @brief Slot error
     */
    void slotError(QNetworkReply::NetworkError networkError);
    /**
     * @internal
     * @brief Process reply
     *
     * This method is used to process a network reply.
     * It should be reimplemented in order to perform
     * tasks like retrieving downloaded information.
     *
     * @param reply Network reply.
     */
    virtual void processReply(QNetworkReply *reply) = 0;
    /**
     * @internal
     * @brief Cleanup
     *
     * This method is used to perform a cleanup when
     * the process is finished. It cleans the network
     * reply by default.
     */
    virtual void cleanup();
    /**
     * @internal
     * @brief Network access manager
     */
    QNetworkAccessManager *networkAccessManager;
    /**
     * @internal
     * @brief Replies and requests
     */
    QMap<QNetworkReply *, QString> repliesAndRequests;
protected:
    /**
     * @internal
     * @brief Q-pointer
     */
    AbstractOnlineHelper * const q_ptr;
private:
    Q_DECLARE_PUBLIC(AbstractOnlineHelper)
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTONLINEHELPER_P_H

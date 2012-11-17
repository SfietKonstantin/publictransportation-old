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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTCACHEDSUGGESTEDSTATIONSHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTCACHEDSUGGESTEDSTATIONSHELPER_H

/**
 * @file abstractcachedsuggestedstationshelper.h
 * @short Definition of PublicTransportation::PluginHelper::AbstractCachedSuggestedStationsHelper
 */

#include "publictransportationpluginhelper_global.h"
#include "abstractsuggestedstationshelper.h"

namespace PublicTransportation
{

namespace PluginHelper
{

class AbstractCachedSuggestedStationsHelperPrivate;

/**
 * @brief A class used to support suggested stations that can be cached
 *
 * This class provides an interface for suggesting stations, that can
 * be retrived at the first time and cached. In order to use that class
 * you need to reimplement processData(), and send the
 * suggestedStationsRetrieved() signal.
 *
 * Instead of calling AbstractOnlineHelper::get() or AbstractOnlineHelper::post(),
 * you should call a wrapper around these methods, that are suggestGet() and
 * suggestPost(), that will either perform the network operation, or
 * directly get the information from the cache if they are available.
 * These methods also perform the AbstractSuggestedStationsHelper::setData() for you
 * if needed.
 */
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractCachedSuggestedStationsHelper:
        public AbstractSuggestedStationsHelper
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit AbstractCachedSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager,
                                                   QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~AbstractCachedSuggestedStationsHelper();
    /**
     * @brief GET request with a suggest feature
     * @param request request.
     * @param networkRequest network request.
     * @param partialStation partial station.
     */
    void suggestGet(const QString &request, const QNetworkRequest &networkRequest,
                    const QString &partialStation);
    /**
     * @brief POST request with a suggest feature
     * @param request request.
     * @param networkRequest network request.
     * @param data data used for the POST request.
     * @param partialStation partial station.
     */
    void suggestPost(const QString &request, const QNetworkRequest &networkRequest,
                     const QByteArray &data, const QString &partialStation);
private:
    Q_DECLARE_PRIVATE(AbstractCachedSuggestedStationsHelper)

};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTCACHEDSUGGESTEDSTATIONSHELPER_H

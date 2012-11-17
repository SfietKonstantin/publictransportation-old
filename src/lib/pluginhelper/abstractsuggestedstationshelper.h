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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTSUGGESTEDSTATIONSHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTSUGGESTEDSTATIONSHELPER_H

/**
 * @file abstractsuggestedstationshelper.h
 * @short Definition of PublicTransportation::PluginHelper::AbstractSuggestedStationsHelper
 */

#include "publictransportationpluginhelper_global.h"
#include "abstractonlinehelper.h"

class QIODevice;
namespace PublicTransportation
{

class Station;
namespace PluginHelper
{

class AbstractSuggestedStationsHelperPrivate;

/**
 * @brief A class used to support suggested stations
 *
 * This class provides an interface for suggesting stations.
 * In order to use that class you need to reimplement
 * processData(), and send the suggestedStationsRetrieved() signal.
 *
 * When implementing this class, you can call partialStation()
 * to know what is the station that is asked. The partial station
 * is set calling setData().
 */
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractSuggestedStationsHelper:
        public AbstractOnlineHelper
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit AbstractSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager,
                                             QObject *parent = 0);
    /**
     * @brief setData
     * @param partialStation partial station.
     */
    void setData(const QString &partialStation);
Q_SIGNALS:
    /**
     * @brief Suggested stations retrieved
     * @param request request.
     * @param suggestedStationList suggested station list.
     */
    void suggestedStationsRetrieved(const QString &request,
                                   const QList<PublicTransportation::Station> suggestedStationList);
protected:
    /**
     * @brief D-pointer based constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractSuggestedStationsHelper(AbstractSuggestedStationsHelperPrivate &dd,
                                             QObject *parent);
    /**
     * @brief Partial station
     * @return partial station.
     */
    QString partialStation() const;
    /**
     * @brief Process data
     * @param input input.
     * @param ok if the data were correctly processed.
     * @param errorMessage an error message.
     * @return a list of suggested stations.
     */
    virtual QList<Station> processData(QIODevice *input, bool *ok = 0,
                                       QString *errorMessage = 0) = 0;
private:
    Q_DECLARE_PRIVATE(AbstractSuggestedStationsHelper)

};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTSUGGESTEDSTATIONSHELPER_H

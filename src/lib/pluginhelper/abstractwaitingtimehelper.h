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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_H

/**
 * @file abstractwaitingtimehelper.h
 * @short Definition of PublicTransportation::PluginHelper::AbstractWaitingTimeHelper
 */

#include "publictransportationpluginhelper_global.h"
#include "abstractonlinehelper.h"

class QIODevice;
class QNetworkAccessManager;
namespace PublicTransportation
{

class Company;
class Line;
class Journey;
class Station;
class JourneyAndWaitingTime;
namespace PluginHelper
{

class AbstractWaitingTimeHelperPrivate;

/**
 * @brief A class used to support waiting time
 *
 * This class provides an interface for waiting time.
 * In order to use that class you need to reimplement
 * processData(), and send the waitingTimeRetrieved() signal.
 *
 * When implementing this class, you can call company(), line(),
 * journey() and station() to know what are the different data
 * used in this request. These data are set calling setData().
 */
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractWaitingTimeHelper:
        public AbstractOnlineHelper
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit AbstractWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                       QObject *parent = 0);
    /**
     * @brief setData
     * @param company company.
     * @param line line.
     * @param journey journey.
     * @param station station.
     */
    void setData(const Company &company, const Line &line,
                 const Journey &journey, const Station &station);
Q_SIGNALS:
    /**
     * @brief Waiting time retrieved
     * @param request request.
     * @param journeysAndWaitingList list of journeys and waiting time.
     */
    void waitingTimeRetrieved(const QString &request,
                   const QList<PublicTransportation::JourneyAndWaitingTime> journeysAndWaitingList);
protected:
    /**
     * @brief D-pointer based constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractWaitingTimeHelper(AbstractWaitingTimeHelperPrivate &dd, QObject *parent);
    /**
     * @brief Company
     * @return company.
     */
    Company company() const;
    /**
     * @brief Line
     * @return line.
     */
    Line line() const;
    /**
     * @brief Journey
     * @return journey.
     */
    Journey journey() const;
    /**
     * @brief Station
     * @return station.
     */
    Station station() const;
    /**
     * @brief Process data
     * @param input input.
     * @param ok if the data were correctly processed.
     * @param errorMessage an error message.
     * @return a list of suggested stations.
     */
    virtual QList<JourneyAndWaitingTime> processData(QIODevice *input, bool *ok = 0,
                                                     QString *errorMessage = 0) = 0;
private:
    Q_DECLARE_PRIVATE(AbstractWaitingTimeHelper)
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_H

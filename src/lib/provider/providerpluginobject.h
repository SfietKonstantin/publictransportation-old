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

#ifndef PUBLICTRANSPORTATION_PROVIDERPLUGINOBJECT_H
#define PUBLICTRANSPORTATION_PROVIDERPLUGINOBJECT_H

/**
 * @file providerpluginobject.h
 * @short Definition of PublicTransportation::ProviderPluginObject
 */

#include "publictransportation_global.h"
#include <QtCore/QObject>
#include "providerplugininterface.h"

namespace PublicTransportation
{

class InfoJourneys;
class WaitingTime;
/**
 * @brief Base for a provider plugin
 *
 * A provider plugin is a Qt / C++ plugin that can
 * be load using a helper program. A provider that
 * is loaded behave exactly like any other backend.
 *
 * Creating a provider plugin have advantages, that
 * are a very simple interface, but also draw-backs,
 * like the need to compiling and linking against
 * libpublictransportation.
 *
 * This class is the recommended base for a provider
 * plugin. It provides all the interfaces declared
 * in PublicTransportation::ProviderPluginInterface,
 * but also offers a QObject as a base.
 *
 * @section implementing Implementing a provider plugin
 *
 * capabilities() list the capabilities of the provider,
 * and must be implemented properly. Capabilities can be found in
 * file \ref capabilitiesconstants.h. Other methods are
 * used to perform tasks that backends perform. These methods
 * are
 * - retrieveCopyright()
 * - retrieveSuggestedStations()
 * - retrieveJourneysFromStation()
 * - retrieveWaitingTime()
 *
 * These methods are already implemented by default, but do nothing.
 * In order to perform a task, a backend should implement some
 * of these methods.
 *
 * Please pay attention that retrieveJourneysFromStation() and retrieveWaitingTime() can be
 * refreshed by the user, therefore, this signal can be emitted several times. Be sure not
 * to abusively cache data, and provide outdated information.
 *
 * All calls are done asynchronously, and replies to called methods
 * are done though signals. The corresponding signals to the previously
 * listed methods are
 * - copyrightRetrieved()
 * - suggestedStationsRetrieved()
 * - journeysFromStationRetrieved()
 * - waitingTimeRetrieved()
 *
 * A specific signal, errorRetrieved() can also be sent in order
 * to inform that there were an error. Error categories can be found
 * in file @ref errorid.h
 */
class PUBLICTRANSPORTATION_EXPORT ProviderPluginObject:
        public QObject, public ProviderPluginInterface
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit ProviderPluginObject(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~ProviderPluginObject();
public Q_SLOTS:
    /**
     * @brief Retrieve copyright
     * @param request request identifier.
     */
    virtual void retrieveCopyright(const QString &request);
    /**
     * @brief Retrieve suggested stations
     * @param request request identifier.
     * @param partialStation partial station name.
     */
    virtual void retrieveSuggestedStations(const QString &request, const QString &partialStation);
    /**
     * @brief Retrieve journeys from station
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
    virtual void retrieveJourneysFromStation(const QString &request,
                                             const PublicTransportation::Station &station,
                                             int limit);
    /**
     * @brief Retrieve waiting time
     * @param request request identifier.
     * @param company company.
     * @param line line for which the waiting time should be queried.
     * @param journey journey for which the waiting time should be queried.
     * @param station station for which the waiting time should be queried.
     */
    virtual void retrieveWaitingTime(const QString &request,
                                     const PublicTransportation::Company &company,
                                     const PublicTransportation::Line &line,
                                     const PublicTransportation::Journey &journey,
                                     const PublicTransportation::Station &station);
Q_SIGNALS:
    /**
     * @brief Error retrieved
     * @param request request identifier.
     * @param errorId a predefined string that provides the error category.
     * @param error a human-readable string describing the error.
     */
    void errorRetrieved(const QString &request, const QString &errorId, const QString &error);
    /**
     * @brief Copyright retrieved
     * @param request request identifier.
     * @param copyright copyright and other legal informations.
     */
    void copyrightRetrieved(const QString &request, const QString &copyright);
    /**
     * @brief Suggested stations retrieved
     * @param request request identifier.
     * @param suggestedStations suggested stations, as a list of stations.
     */
    void suggestedStationsRetrieved(const QString &request,
                                    const QList<PublicTransportation::Station> &suggestedStations);
    /**
     * @brief Journeys from station retrieved
     * @param request request identifier.
     * @param infoJourneys a list of informations about journeys.
     */
    void journeysFromStationRetrieved(const QString &request,
                                      const QList<PublicTransportation::InfoJourneys> &infoJourneys);
    /**
     * @brief Waiting time retrieved
     * @param request request identifier.
     * @param waitingTimeList a list of waiting time.
     */
    void waitingTimeRetrieved(const QString &request,
                              const QList<PublicTransportation::WaitingTime> &waitingTimeList);
};

}

#endif // PUBLICTRANSPORTATION_PROVIDERPLUGINOBJECT_H

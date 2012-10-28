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

#ifndef PUBLICTRANSPORTATION_BACKENDDBUSWRAPPER_H
#define PUBLICTRANSPORTATION_BACKENDDBUSWRAPPER_H

/**
 * @file dbusbackendwrapper.h
 * @short Definition of PublicTransportation::DBusBackendWrapper
 */

#include "publictransportation_global.h"
#include "manager/abstractbackendwrapper.h"

namespace PublicTransportation
{

class DBusBackendWrapperPrivate;

/**
 * @brief Backend wrapper that uses DBus to communicate
 *
 * This class simply implements a wrapper that uses DBus
 * to communicate between the backend and the wrapper.
 */
class PUBLICTRANSPORTATION_EXPORT DBusBackendWrapper : public AbstractBackendWrapper
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     *
     * @param identifier identifier for this backend wrapper.
     * @param executable command line that launch the backend.
     * @param arguments list of arguments.
     * @param parent parent object.
     */
    explicit DBusBackendWrapper(const QString &identifier, const QString &executable,
                                const QMap<QString, QString> &arguments, QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DBusBackendWrapper();
    virtual QString requestCopyright();
    virtual QString requestSuggestStations(const QString &partialStation);
    virtual QString requestJourneysFromStation(const Station &station, int limit);
    virtual QString requestJourneysAndWaitingTimesFromStation(const Station &station, int limit);
    virtual QString requestWaitingTime(const Company &company, const Line &line,
                                       const Journey &journey, const Station &station);
    virtual QString requestStationsFromJourney(const Company &company, const Line &line,
                                               const Journey &journey, const Station &station);
public Q_SLOTS:
    /**
     * @brief Launch the backend
     */
    virtual void launch();
    /**
     * @brief Stop the backend
     */
    virtual void stop();
    /**
     * @brief Wait for stopped
     */
    virtual void waitForStopped();
    /**
     * @brief Kill the backend
     */
    virtual void kill();
    /**
     * @brief Register backend
     *
     * This method is used to register the backend. It should be called when the backend
     * is launched in order or publictransportation to know about it's capabilities.
     * Capabilities can be found in file \ref capabilitiesconstants.h
     *
     * @param capabilities backend capabilities, that are send as a list of strings.
     */
    void registerBackend(const QStringList &capabilities);
Q_SIGNALS:
    /**
     * @brief Copyright requested
     * @param request request identifier.
     */
    void copyrightRequested(const QString &request);
    /**
     * @brief Suggested stations requested
     *
     * This is a DBus proxy signal.
     *
     * @param request request identifier.
     * @param partialStation partial station name.
     */
    void suggestStationsRequested(const QString &request, const QString &partialStation);
    /**
     * @brief Journeys from station requested
     *
     * This is a DBus proxy signal.
     *
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
    void journeysFromStationRequested(const QString &request,
                                      const PublicTransportation::Station &station,
                                      int limit);
    /**
     * @brief Journeys and waiting times from station requested
     *
     * This is a DBus proxy signal.
     *
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
    void journeysAndWaitingTimesFromStationRequested(const QString &request,
                                                     const PublicTransportation::Station &station,
                                                     int limit);
    /**
     * @brief Waiting time
     *
     * This is a DBus proxy signal.
     *
     * @param request request identifier.
     * @param company company.
     * @param line line for which the waiting time should be queried.
     * @param journey journey for which the waiting time should be queried.
     * @param station station for which the waiting time should be queried.
     */
    void waitingTimeRequested(const QString &request, const PublicTransportation::Company &company,
                              const PublicTransportation::Line &line,
                              const PublicTransportation::Journey &journey,
                              const PublicTransportation::Station &station);
    /**
     * @brief Stations from journey requested
     *
     * This is a DBus proxy signal.
     *
     * @param request request identifier.
     * @param company company.
     * @param line line for which the waiting time should be queried.
     * @param journey journey for which the waiting time should be queried.
     * @param station station for which the waiting time should be queried.
     */
    void stationsFromJourneyRequested(const QString &request,
                                      const PublicTransportation::Company &company,
                                      const PublicTransportation::Line &line,
                                      const PublicTransportation::Journey &journey,
                                      const PublicTransportation::Station &station);
private:
    Q_DECLARE_PRIVATE(DBusBackendWrapper)
    /// \cond buggy-doxygen-doc
    Q_PRIVATE_SLOT(d_func(), void slotReadStandardOutput())
    Q_PRIVATE_SLOT(d_func(), void slotReadStandardError())
    Q_PRIVATE_SLOT(d_func(), void slotProcessError(QProcess::ProcessError))
    Q_PRIVATE_SLOT(d_func(), void slotFinished(int))
    /// \endcond
};



}

#endif // PUBLICTRANSPORTATION_BACKENDDBUSWRAPPER_H

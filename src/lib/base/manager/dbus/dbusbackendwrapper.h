/*
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * The names of its contributors may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef PT2_BACKENDDBUSWRAPPER_H
#define PT2_BACKENDDBUSWRAPPER_H

/**
 * @file dbusbackendwrapper.h
 * @short Definition of PublicTransportation::DBusBackendWrapper
 */

#include "pt2_global.h"
#include "manager/abstractbackendwrapper.h"

namespace PT2
{

class DBusBackendWrapperPrivate;

/**
 * @brief Backend wrapper that uses DBus to communicate
 *
 * This class simply implements a wrapper that uses DBus
 * to communicate between the backend and the wrapper.
 */
class PT2_EXPORT DBusBackendWrapper : public AbstractBackendWrapper
{
    Q_OBJECT
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
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
                                QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DBusBackendWrapper();
    int progress() const;
//    virtual QString requestCopyright();
//    virtual QString requestSuggestStations(const QString &partialStation);
//    virtual QString requestJourneysFromStation(const Station &station, int limit);
//    virtual QString requestJourneysAndWaitingTimesFromStation(const Station &station, int limit);
//    virtual QString requestWaitingTime(const Company &company, const Line &line,
//                                       const Journey &journey, const Station &station);
//    virtual QString requestStationsFromJourney(const Company &company, const Line &line,
//                                               const Journey &journey, const Station &station);
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

    void registerBackendStart();
    void registerBackendProgress(int progress);
    void registerBackendReady(const QStringList &capabilities, const QString &copyright);
    /**
     * @brief Register backend
     *
     * This method is used to register the backend. It should be called when the backend
     * is launched in order or publictransportation to know about it's capabilities.
     * Capabilities can be found in file \ref capabilitiesconstants.h
     *
     * @param capabilities backend capabilities, that are send as a list of strings.
     */
//    void registerBackend(const QStringList &capabilities);
Q_SIGNALS:
    void progressChanged();
    /**
     * @brief Copyright requested
     * @param request request identifier.
     */
//    void copyrightRequested(const QString &request);
    /**
     * @brief Suggested stations requested
     *
     * This is a DBus proxy signal.
     *
     * @param request request identifier.
     * @param partialStation partial station name.
     */
//    void suggestStationsRequested(const QString &request, const QString &partialStation);
    /**
     * @brief Journeys from station requested
     *
     * This is a DBus proxy signal.
     *
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
//    void journeysFromStationRequested(const QString &request,
//                                      const PublicTransportation::Station &station,
//                                      int limit);
    /**
     * @brief Journeys and waiting times from station requested
     *
     * This is a DBus proxy signal.
     *
     * @param request request identifier.
     * @param station station to query.
     * @param limit limit of the number of journeys.
     */
//    void journeysAndWaitingTimesFromStationRequested(const QString &request,
//                                                     const PublicTransportation::Station &station,
//                                                     int limit);
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
//    void waitingTimeRequested(const QString &request, const PublicTransportation::Company &company,
//                              const PublicTransportation::Line &line,
//                              const PublicTransportation::Journey &journey,
//                              const PublicTransportation::Station &station);
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
//    void stationsFromJourneyRequested(const QString &request,
//                                      const PublicTransportation::Company &company,
//                                      const PublicTransportation::Line &line,
//                                      const PublicTransportation::Journey &journey,
//                                      const PublicTransportation::Station &station);
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

#endif // PT2_BACKENDDBUSWRAPPER_H

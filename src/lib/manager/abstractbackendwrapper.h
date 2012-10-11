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

#ifndef PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_H
#define PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_H

/**
 * @file abstractbackendwrapper.h
 * @short Definition of PublicTransportation::AbstractBackendWrapper
 */


#include "publictransportation_global.h"
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/waitingtime.h"
#include "common/linejourneys.h"

namespace PublicTransportation
{

class AbstractBackendWrapperPrivate;

/**
 * @brief Base class for a backend wrapper
 *
 * This class provides a base for any backend wrapper.
 * A backend wrapper is an interface between a backend
 * that is usually a process that is spawned, and that is
 * used to perform specific tasks in an asynchronous ways.
 *
 * This class is used to perform the interface between the
 * spawned backend and the applications that is used to
 * display informations.
 *
 * In order to do that, the backend wrapper provides methods
 * like launch(), stop() and kill() that should be implemented,
 * as well as a set of properties, like status(), that is used
 * to get the current backend status.
 *
 * In order to be managed more easily, all backend wrappers have
 * an identifier, that is passed in the constructor, and that
 * should be unique for each backend. This identifier can also
 * be passed to the backend if needed.
 *
 * @section capabilities Capabilities
 *
 * A backend have capabilities that might vary from backend to
 * backend. Those capabilities provides what the backend can
 * deliver. A sane application should never call methods that
 * are related to a capability that is not provided by the backend,
 * as the behaviour might be unknown.
 *
 * @section managingBackend Managing backend
 *
 * The backend wrapper is used to manage backend and provide
 * a neat interface of the backend to the application. When
 * a backend is launched, the status should be set to
 * AbstractBackendWrapper::Launching. When it is being stopped,
 * it should be set to AbstractBackendWrapper::Stopping. While the
 * backend ping the wrapper back, it should also register its
 * capabilities. While an error occur in the backend (like failing
 * to register a DBus service, for example), the
 * AbstractBackendWrapper::Invalid status should be set.
 *
 * Three helper methods are used to help implementing backend wrapper:
 * - setStatus()
 * - setCapabilities()
 * - setLastError()
 *
 * @section informationStorage Information storage
 *
 * This class is also used to store informations that
 * the backend retrieved. These informations can be
 * stored and access through
 * - setCapabilities()
 * - setCompanies()
 * - setLines()
 * - setJourneys()
 * - setStations()
 * - setWaitingTime()
 *
 * as well as
 * - capabilities()
 * - companies()
 * - lines()
 * - journeys()
 * - stations()
 * - waitingTime()
 *
 * This class also provides interfaces for implementing some capabilities
 * of the providers, that should be implemented in subclasses:
 * - requestListCompanies()
 * - requestListLines()
 * - requestListJourneys()
 * - requestListStations()
 * - requestWaitingTime()
 *
 * Remark that there is no request for capabilities. It is because
 * registering capabilities is something that backends should do
 * automatically, in order to be validated. Subclasses should implement
 * a method to perform this registration (that should use setCapabilities())
 * and that should set the status to AbstractBackendWrapper::Launched.
 *
 */
class PUBLICTRANSPORTATION_EXPORT AbstractBackendWrapper: public QObject
{
    Q_OBJECT
    /**
     * @short Status
     */
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
public:
    /**
     * @brief Enumeration describing backend status
     */
    enum Status {
        /**
         * @short The backend is stopped
         */
        Stopped,
        /**
         * @short The backend is launching
         */
        Launching,
        /**
         * @short The backend is launched
         */
        Launched,
        /**
         * @short The backend is stopping
         */
        Stopping,
        /**
         * @short The backend is in an invalid state
         */
        Invalid
    };
    enum RequestType {
        SuggestStationType
    };

    /**
     * @brief Default constructor
     *
     * A set of properties can be passed to the constructor.
     * Those arguments can be used in the implementation to
     * provide, for example, additional command line arguments,
     * to the backend that controlled by this wrapper.
     *
     * @param identifier identifier for this backend wrapper.
     * @param executable command line that launch the backend.
     * @param arguments list of arguments.
     * @param parent parent object.
     */
    explicit AbstractBackendWrapper(const QString &identifier, const QString &executable,
                                    const QMap<QString, QString> &arguments, QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~AbstractBackendWrapper();
    /**
     * @brief Identifier
     * @return identifier.
     */
    QString identifier() const;
    /**
     * @brief Status
     * @return status.
     */
    Status status() const;
    /**
     * @brief Last error
     * @return last error.
     */
    QString lastError() const;
    /**
     * @brief Capabilities
     * @return capabilities.
     */
    QStringList capabilities() const;


    virtual QString requestSuggestStations(const QString &partialStation) = 0;
    virtual QString requestJourneysFromStation(const Station &station, int limit) = 0;
public Q_SLOTS:
    /**
     * @brief Launch the backend
     *
     * Launch the backend. Implementation can use the
     * executable and the arguments that are passed
     * while an instance of the backend wrapper is created
     * to perform custom launches.
     */
    virtual void launch() = 0;
    /**
     * @brief Stop the backend
     *
     * Stops the backend. The stop is asynchronous, and can
     * occur a bit after.
     */
    virtual void stop() = 0;
    /**
     * @brief Wait for stopped
     *
     * This method can be reimplemented to wait for the backend
     * to finish cleanly.
     */
    virtual void waitForStopped();
    /**
     * @brief Kill the backend
     *
     * Kills the backend. The backend should be immediately
     * stopped, as this method is called either in emergency
     * situations.
     */
    virtual void kill() = 0;
    void registerError(const QString &request, const QString &error);
    void registerSuggestedStations(const QString &request,
                                   const QList<PublicTransportation::Station> &suggestedStations);
    void registerJourneysFromStation(const QString &request,
                                     const QList<PublicTransportation::LineJourneys> &journeys);
Q_SIGNALS:
    /**
     * @brief Status changed
     */
    void statusChanged();
    /**
     * @brief Capabilities changed
     */
    void capabilitiesChanged();

    void errorRegistered(const QString &request, const QString &error);
    void suggestedStationsRegistered(const QString & request,
                                     const QList<PublicTransportation::Station> &suggestedStations);
    void journeysFromStationRegistered(const QString &request,
                                       const QList<PublicTransportation::LineJourneys> &journeys);
protected:
    /**
     * @brief D-pointer based constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractBackendWrapper(AbstractBackendWrapperPrivate &dd, QObject *parent);
    /**
     * @brief Executable
     * @return executable.
     */
    QString executable() const;
    /**
     * @brief Arguments
     * @return arguments.
     */
    QMap<QString, QString> arguments() const;
    /**
     * @brief Set status
     * @param status status to set.
     */
    void setStatus(Status status);
    /**
     * @brief Set last error
     * @param lastError error to set.
     */
    void setLastError(const QString &lastError);
    /**
     * @brief Set capabilities
     * @param capabilities capabilities to set.
     */
    void setCapabilities(const QStringList &capabilities);
    QString createRequest(RequestType requestType);

    /**
     * @brief D-pointer
     */
    QScopedPointer<AbstractBackendWrapperPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractBackendWrapper)
};

}

#endif // PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_H

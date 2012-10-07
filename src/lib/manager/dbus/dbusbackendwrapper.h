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
#include <QtCore/QProcess>
#include <QtDBus/QDBusArgument>

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
     * @brief Kill the backend
     */
    virtual void kill();
    /**
     * @brief Request a list of the companies
     */
    virtual void requestListCompanies();
    /**
     * @brief Request a list of the lines
     * @param company company for which the lines should be listed.
     */
    virtual void requestListLines(const Company &company);
    /**
     * @brief Request a list of the journeys
     * @param company company for which the journeys should be listed.
     * @param line line for which the journeys should be listed.
     */
    virtual void requestListJourneys(const Company &company, const Line &line);
    /**
     * @brief Request a list of the stations
     * @param company company for which the stations should be listed.
     * @param line line for which the stations should be listed.
     * @param journey journey for which the stations should be listed.
     */
    virtual void requestListStations(const Company &company, const Line &line,
                                     const Journey &journey);
    /**
     * @brief Register backend
     *
     * This is a DBus proxy method.
     *
     * This method is used to perform backend registration.
     *
     * @param capabilities capabilities to register.
     */
    void registerBackend(const QStringList &capabilities);
    /**
     * @brief Register listed companies
     *
     * This is a DBus proxy method.
     *
     * @param companies companies to register.
     */
    void registerListedCompanies(const QList<PublicTransportation::Company> &companies);
    /**
     * @brief Register listed lines
     *
     * This is a DBus proxy method.
     *
     * @param company company for which the lines should be registered.
     * @param lines lines to register.
     */
    void registerListedLines(const PublicTransportation::Company &company,
                             const QList<PublicTransportation::Line> &lines);
    /**
     * @brief Register listed journeys
     *
     * This is a DBus proxy method.
     *
     * @param company company for which the journeys should be registered.
     * @param line line for which the journeys should be registered.
     * @param journeys journeys to register.
     */
    void registerListedJourneys(const PublicTransportation::Company &company,
                                const PublicTransportation::Line &line,
                                const QList<PublicTransportation::Journey> &journeys);
    /**
     * @brief Register listed stations
     *
     * This is a DBus proxy method.
     *
     * @param company company for which the stations should be registered.
     * @param line line for which the stations should be registered.
     * @param journey journey for which the stations should be registered.
     * @param stations stations to register.
     */
    void registerListedStations(const PublicTransportation::Company &company,
                                const PublicTransportation::Line &line,
                                const PublicTransportation::Journey &journey,
                                const QList<PublicTransportation::Station> &stations);
Q_SIGNALS:
    /**
     * @brief List companies requested
     *
     * This is a DBus proxy signal.
     */
    void listCompaniesRequested();
    /**
     * @brief List lines requested
     *
     * This is a DBus proxy signal.
     *
     * @param company company for which the lines should be listed.
     */
    void listLinesRequested(const PublicTransportation::Company &company);
    /**
     * @brief List journeys requested
     *
     * This is a DBus proxy signal.
     *
     * @param company company for which the journeys should be listed.
     * @param line line for which the journeys should be listed.
     */
    void listJourneysRequested(const PublicTransportation::Company & company,
                           const PublicTransportation::Line &line);
    /**
     * @brief List stations requested
     *
     * This is a DBus proxy signal.
     *
     * @param company company for which the stations should be listed.
     * @param line line for which the stations should be listed.
     * @param journey journey for which the stations should be listed.
     */
    void listStationsRequested(const PublicTransportation::Company & company,
                           const PublicTransportation::Line & line,
                           const PublicTransportation::Journey & journey);
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

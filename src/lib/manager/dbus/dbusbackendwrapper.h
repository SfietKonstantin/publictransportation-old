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
    virtual int requestSuggestStations(const QString &partialStation);
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
    void registerBackend(const QStringList &capabilities);
Q_SIGNALS:
    /**
     * @brief Request suggested stations
     *
     * This is a DBus proxy signal.
     */
    void suggestStationsRequested(int request, const QString &partialStation);
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

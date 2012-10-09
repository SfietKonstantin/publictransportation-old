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

/**
 * @file dbusbackendwrapper.cpp
 * @short Implementation of PublicTransportation::DBusBackendWrapper
 */

#include "dbusbackendwrapper.h"
#include "manager/abstractbackendwrapper_p.h"

#include <QtCore/QProcess>
#include <QtCore/QStringList>
#include <QtDBus/QDBusConnection>

#include "debug.h"
#include "common/dbus/dbushelper.h"
#include "common/dbus/dbusconstants.h"
#include "common/capabilitiesconstants.h"
#include "dbusbackendwrapperadaptor.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::DBusBackendWrapper
 */
class DBusBackendWrapperPrivate: public AbstractBackendWrapperPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    DBusBackendWrapperPrivate(DBusBackendWrapper *q);
    /**
     * @internal
     * @brief Slot for read standard output
     */
    void slotReadStandardOutput();
    /**
     * @internal
     * @brief Slot for read standard error
     */
    void slotReadStandardError();
    /**
     * @internal
     * @brief Slot for process error
     * @param error error.
     */
    void slotProcessError(QProcess::ProcessError error);
    /**
     * @internal
     * @brief Slot for finished
     * @param code exit code.
     */
    void slotFinished(int code);
    /**
     * @internal
     * @brief Process
     */
    QProcess *process;
    /**
     * @internal
     * @brief DBus object path
     */
    QString dbusObjectPath;
private:
    /**
     * @internal
     * @brief Q-pointer
     */
    DBusBackendWrapper * const q_ptr;
    Q_DECLARE_PUBLIC(DBusBackendWrapper)

};

DBusBackendWrapperPrivate::DBusBackendWrapperPrivate(DBusBackendWrapper *q):
    AbstractBackendWrapperPrivate(), q_ptr(q)
{
}

void DBusBackendWrapperPrivate::slotReadStandardOutput()
{
    process->setReadChannel(QProcess::StandardOutput);
    while (!process->atEnd()) {
        debug("backend") << process->readLine().trimmed().constData();
    }
}

void DBusBackendWrapperPrivate::slotReadStandardError()
{
    process->setReadChannel(QProcess::StandardError);
    while (!process->atEnd()) {
        debug("backend") << process->readLine().trimmed().constData();
    }
}

void DBusBackendWrapperPrivate::slotProcessError(QProcess::ProcessError error)
{
    Q_Q(DBusBackendWrapper);
    debug("backend") << "Child process send the error" << error;
    debug("backend") << process->errorString();
    QString lastError = QString("Child process send the error :\"%1\"").arg(process->errorString());
    q->setLastError(lastError);
    q->setStatus(DBusBackendWrapper::Invalid);
}

void DBusBackendWrapperPrivate::slotFinished(int code)
{
    Q_Q(DBusBackendWrapper);
    debug("backend") << "Finished with code" << code;
    debug("backend") << "Unregister DBus object" << dbusObjectPath.toAscii().constData();
    QDBusConnection::sessionBus().unregisterObject(dbusObjectPath, QDBusConnection::UnregisterTree);
    q->setStatus(AbstractBackendWrapper::Stopped);
}

////// End of private class //////

DBusBackendWrapper::DBusBackendWrapper(const QString &identifier, const QString &executable,
                                       const QMap<QString, QString> &arguments, QObject *parent):
    AbstractBackendWrapper(*(new DBusBackendWrapperPrivate(this)), parent)
{
    Q_D(DBusBackendWrapper);
    registerDBusTypes();

    d->identifier = identifier;
    d->executable = executable;
    d->arguments = arguments;

    d->process = new QProcess(this);
    connect(d->process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotReadStandardOutput()));
    connect(d->process, SIGNAL(readyReadStandardError()), this, SLOT(slotReadStandardError()));
    connect(d->process, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(slotProcessError(QProcess::ProcessError)));
    connect(d->process, SIGNAL(finished(int)), this, SLOT(slotFinished(int)));
}

DBusBackendWrapper::~DBusBackendWrapper()
{
    kill();
}

void DBusBackendWrapper::launch()
{
    Q_D(DBusBackendWrapper);

    if (identifier().isEmpty()) {
        setLastError("No identifier was set");
        setStatus(Invalid);
        return;
    }

    QByteArray object = QCryptographicHash::hash(identifier().toAscii(), QCryptographicHash::Md5);
    QString dbusIdentifier = QString::fromAscii(object.toHex());

    // Register to DBus
    d->dbusObjectPath = DBUS_BACKEND_PATH_PREFIX;
    d->dbusObjectPath.append(dbusIdentifier);

    new PublictransportationAdaptor(this);
    if (!QDBusConnection::sessionBus().registerObject(d->dbusObjectPath, this)) {
        setLastError(QString("Failed to register object on path %1").arg(d->dbusObjectPath));
        setStatus(Invalid);
        return;
    }

    // Launch the backend
    setStatus(Launching);
    d->process->setWorkingDirectory(APPLICATION_FOLDER);
    QString trueExecutable = executable();
    trueExecutable.replace("$PROVIDER", QString(PROVIDER_PATH) + " --plugin ");
    trueExecutable.append(QString(" --identifier %1 ").arg(dbusIdentifier));

    d->process->start(trueExecutable);
}

void DBusBackendWrapper::stop()
{
    Q_D(DBusBackendWrapper);
    if (d->process->state() == QProcess::NotRunning) {
        return;
    }

    debug("dbus-backend-wrapper") << "Stop backend for" << d->dbusObjectPath.toAscii().constData()
                                  << "with pid" << d->process->pid();

    setStatus(Stopping);
    d->process->terminate();
}

void DBusBackendWrapper::waitForStopped()
{
    Q_D(DBusBackendWrapper);
    d->process->waitForFinished(5000);
    return;
}

void DBusBackendWrapper::kill()
{
    Q_D(DBusBackendWrapper);
    if (d->process->state() == QProcess::NotRunning) {
        return;
    }

    debug("dbus-backend-wrapper") << "Kill backend for" << d->dbusObjectPath.toAscii().constData()
                                  << "with pid" << d->process->pid();
    d->process->kill();
    d->process->waitForFinished(-1);
    setStatus(Stopped);
}

void DBusBackendWrapper::requestListCompanies()
{
    emit listCompaniesRequested();
}

void DBusBackendWrapper::requestListLines(const Company &company)
{
    emit listLinesRequested(company);
}

void DBusBackendWrapper::requestListJourneys(const Company &company, const Line &line)
{
    emit listJourneysRequested(company, line);
}

void DBusBackendWrapper::requestListStations(const Company &company, const Line &line,
                                         const Journey &journey)
{
    emit listStationsRequested(company, line, journey);
}

void DBusBackendWrapper::registerBackend(const QStringList &capabilities)
{
    Q_D(DBusBackendWrapper);
    debug("dbus-backend-wrapper") << "Begin registration of backend for"
                                  << d->dbusObjectPath.toAscii().constData();

    if (status() == Stopping || status() == Stopped) {
        warning("dbus-backend-wrapper") << "Backend for" << d->dbusObjectPath.toAscii().constData()
                                        << "is registering while not yet launched";
        kill();
        setLastError("Backend is registering while not yet launched");
        setStatus(Invalid);
        return;
    }

    if (status() == Launched) {
        warning("dbus-backend-wrapper") << "Backend for" << d->dbusObjectPath.toAscii().constData()
                                        << "is registering twice";
        kill();
        setLastError("Backend is registering twice");
        setStatus(Invalid);
        return;
    }

    if (d->status == Invalid) {
        warning("dbus-backend-wrapper") << "Backend for" << d->dbusObjectPath.toAscii().constData()
                                        << "is registering more than twice";
        return;
    }

    debug("dbus-backend-wrapper") << "End registration of backend for"
                                  << d->dbusObjectPath.toAscii().constData();
    debug("dbus-backend-wrapper") << "Capabilities of backend retrieved for"
                                  << d->dbusObjectPath.toAscii().constData();
    debug("dbus-backend-wrapper") << "List of capabilities:";
    debug("dbus-backend-wrapper") << capabilities;

    setCapabilities(capabilities);
    setStatus(Launched);
}

void DBusBackendWrapper::registerListedCompanies(const QList<Company> &companies)
{
    Q_D(DBusBackendWrapper);
    QStringList companiesNames;
    foreach(Company company, companies) {
        companiesNames.append(company.name());
    }

    debug("dbus-backend-wrapper") << "Companies of backend retrieved for"
                                  << d->dbusObjectPath.toAscii().constData();
    debug("dbus-backend-wrapper") << "List of companies:";
    debug("dbus-backend-wrapper") << companiesNames;

    setCompanies(companies);
}

void DBusBackendWrapper::registerListedLines(const Company &company, const QList<Line> &lines)
{
    Q_D(DBusBackendWrapper);

    debug("dbus-backend-wrapper") << "Lines of backend for company" << company.name()
                                  << "retrieved for" << d->dbusObjectPath.toAscii().constData();
    debug("dbus-backend-wrapper") << "List of lines:";
    foreach(Line line, lines) {
        QString lineName = QString("%1: %2");
        lineName = lineName.arg(line.name(), line.properties().value("description").toString());
        debug("dbus-backend-wrapper") << lineName;
    }

    setLines(company, lines);
}

void DBusBackendWrapper::registerListedJourneys(const Company &company, const Line &line,
                                                const QList<Journey> &journeys)
{
    Q_D(DBusBackendWrapper);

    debug("dbus-backend-wrapper") << "Journeys of backend for company" << company.name()
                                  << "and line" << line.name()
                                  << "retrieved for" << d->dbusObjectPath.toAscii().constData();
    debug("dbus-backend-wrapper") << "List of journeys:";
    foreach(Journey journey, journeys) {
        QString journeyName = journey.name();
        debug("dbus-backend-wrapper") << journeyName;
    }

    setJourneys(company, line, journeys);
}

void DBusBackendWrapper::registerListedStations(const Company &company, const Line &line,
                                                const Journey &journey,
                                                 const QList<Station> &stations)
{
    Q_D(DBusBackendWrapper);

    debug("dbus-backend-wrapper") << "Stations of backend for company" << company.name()
                                  << "line" << line.name() << "and journey" << journey.name()
                                  << "retrieved for" << d->dbusObjectPath.toAscii().constData();
    debug("dbus-backend-wrapper") << "List of stations:";
    foreach(Station station, stations) {
        QString stationName = station.name();
        debug("dbus-backend-wrapper") << stationName;
    }

    setStations(company, line, journey, stations);
}

}

#include "moc_dbusbackendwrapper.cpp"

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
 * @file providerplugindbuswrapper.cpp
 * @short Implementation of PublicTransportation::ProviderPluginDBusWrapper
 */


#include "providerplugindbuswrapper.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QList>
#include <QtCore/QPluginLoader>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusServiceWatcher>

#include "debug.h"
#include "common/dbus/dbusconstants.h"
#include "common/dbus/dbushelper.h"
#include "provider/providerpluginobject.h"
#include "backenddbusproxy.h"

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::ProviderPluginDBusWrapper
 */
class ProviderPluginDBusWrapperPrivate
{
public:
    /**
     * @internal
     * @brief Slot for service unregistered
     * @param service service name.
     */
    void slotServiceUnregistered(QString service);
    /**
     * @internal
     * @brief Proxy
     */
    OrgSfietKonstantinPublictransportationInterface *proxy;
    /**
     * @internal
     * @brief DBus object path
     */
    QString dbusObjectPath;
    /**
     * @internal
     * @brief Provider plugin
     */
    ProviderPluginObject *provider;
};

void ProviderPluginDBusWrapperPrivate::slotServiceUnregistered(QString service)
{
    Q_UNUSED(service)
    QCoreApplication::quit();
}

////// End of private class //////

ProviderPluginDBusWrapper::ProviderPluginDBusWrapper(const QString &identifier, QObject *parent):
    QObject(parent), d_ptr(new ProviderPluginDBusWrapperPrivate)
{
    Q_D(ProviderPluginDBusWrapper);
    registerDBusTypes();

    d->dbusObjectPath = QString(DBUS_BACKEND_PATH_PREFIX) + identifier;
    d->provider = 0;
    d->proxy = new OrgSfietKonstantinPublictransportationInterface(DBUS_SERVICE, d->dbusObjectPath,
                                                                   QDBusConnection::sessionBus(),
                                                                   this);
    QDBusServiceWatcher *watcher
            = new QDBusServiceWatcher(DBUS_SERVICE, QDBusConnection::sessionBus(),
                                      QDBusServiceWatcher::WatchForUnregistration, this);
    connect(watcher, SIGNAL(serviceUnregistered(QString)),
            this, SLOT(slotServiceUnregistered(QString)));
}

ProviderPluginDBusWrapper::~ProviderPluginDBusWrapper()
{
}

bool ProviderPluginDBusWrapper::load(const QString &plugin)
{
    Q_D(ProviderPluginDBusWrapper);
    QDir dir (PLUGIN_FOLDER);
    if (!dir.exists(plugin)) {
        warning("provider-wrapper") << "The plugin" << plugin.toAscii().constData()
                                    << "cannot be found";
        return false;
    }


    QString pluginPath = dir.absoluteFilePath(plugin);
    QPluginLoader pluginLoader(pluginPath);
    QObject *pluginObject = pluginLoader.instance();
    if (!pluginObject) {
        warning("provider-wrapper") << "The plugin" << plugin.toAscii().constData()
                                    << "cannot be loaded";
        return false;
    }

    d->provider = qobject_cast<ProviderPluginObject *>(pluginObject);
    if (!d->provider) {
        warning("provider-wrapper") << "The plugin" << plugin.toAscii().constData() << "is not valid";
        return false;
    }

    // Establish some connections
    connect(d->proxy, SIGNAL(listCompaniesRequested()), this, SLOT(sendListedCompanies()));
    connect(d->proxy, SIGNAL(listLinesRequested(PublicTransportation::Company)),
            this, SLOT(sendListedLines(PublicTransportation::Company)));
    connect(d->proxy, SIGNAL(listJourneysRequested(PublicTransportation::Company,
                                                   PublicTransportation::Line)),
            this, SLOT(sendListedJourneys(PublicTransportation::Company,
                                          PublicTransportation::Line)));
    connect(d->proxy, SIGNAL(listStationsRequested(PublicTransportation::Company,
                                                   PublicTransportation::Line,
                                                   PublicTransportation::Journey)),
            this, SLOT(sendListedStations(PublicTransportation::Company,PublicTransportation::Line,
                                          PublicTransportation::Journey)));

    // Register
    debug("provider-wrapper") << "Registration from backend with pid"
                              << QCoreApplication::applicationPid();
   d->proxy->registerBackend(d->provider->capabilities());

    return true;
}

void ProviderPluginDBusWrapper::sendListedCompanies() const
{
    Q_D(const ProviderPluginDBusWrapper);
    debug("provider-wrapper") << "Sending companies from backend with pid"
                              << QCoreApplication::applicationPid();

    d->proxy->registerListedCompanies(d->provider->listCompanies());
}

void ProviderPluginDBusWrapper::sendListedLines(const Company &company) const
{
    Q_D(const ProviderPluginDBusWrapper);
    debug("provider-wrapper") << "Sending lines from backend with pid"
                              << QCoreApplication::applicationPid();

    d->proxy->registerListedLines(company, d->provider->listLines(company));
}

void ProviderPluginDBusWrapper::sendListedJourneys(const Company &company, const Line &line) const
{
    Q_D(const ProviderPluginDBusWrapper);
    debug("provider-wrapper") << "Sending lines from backend with pid"
                              << QCoreApplication::applicationPid();
    d->proxy->registerListedJourneys(company, line, d->provider->listJourneys(company, line));
}

void ProviderPluginDBusWrapper::sendListedStations(const Company &company, const Line &line,
                                                   const Journey &journey) const
{
    Q_D(const ProviderPluginDBusWrapper);
    debug("provider-wrapper") << "Sending stations from backend with pid"
                              << QCoreApplication::applicationPid();
    d->proxy->registerListedStations(company, line, journey,
                                     d->provider->listStations(company, line, journey));
}

}

#include "moc_providerplugindbuswrapper.cpp"
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

#ifndef PUBLICTRANSPORTATION_PROVIDERPLUGININTERFACE_H
#define PUBLICTRANSPORTATION_PROVIDERPLUGININTERFACE_H

/**
 * @file providerplugininterface.h
 * @short Definition of PublicTransportation::ProviderPluginInterface
 */

#include <QtCore/QStringList>
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"

namespace PublicTransportation
{

/**
 * @brief Interface for a provider plugin
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
 * @section implementing Implementing a provider plugin
 *
 * Implementation should be done using
 * PublicTransportation::ProviderPluginObject, that
 * provides a QObject base instead of a plain interface,
 * but the methods to be implemented are still the same.
 *
 * capabilities() list the capabilities of the provider,
 * and must be implemented properly. Other methods like
 * listCompanies(), listLines(), listJourneys(),
 * listStations() etc. must be implemented as well, but,
 * depending to the supported capabilities of the provider,
 * they might return, or do nothing.
 *
 * @section asynchronous Asynchronous calls
 *
 * Some methods should returns nothing when called. Instead,
 * they should trigger an asynchronous call, and emit signals
 * that are declared in PublicTransportation::ProviderPluginObject
 * when the operation is terminated.
 *
 */
class ProviderPluginInterface
{
public:
    /**
     * @brief ~ProviderPluginInterface
     */
    virtual ~ProviderPluginInterface() {}
    /**
     * @brief Capabilities
     * @return capabilities.
     */
    virtual QStringList capabilities() const = 0;
    virtual void retrieveSuggestedStations(const QString &request,
                                           const QString &partialStation) = 0;
};

}

Q_DECLARE_INTERFACE(PublicTransportation::ProviderPluginInterface,
                    "org.SfietKonstantin.publictransportation.Plugin.ProviderPluginInterface/1.0")

#endif // PUBLICTRANSPORTATION_PROVIDERPLUGININTERFACE_H

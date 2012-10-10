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

#ifndef PUBLICTRANSPORTATION_PROVIDERPLUGINWRAPPER_H
#define PUBLICTRANSPORTATION_PROVIDERPLUGINWRAPPER_H

/**
 * @file providerplugindbuswrapper.h
 * @short Definition of PublicTransportation::ProviderPluginDBusWrapper
 */

#include "publictransportation_global.h"
#include <QtCore/QObject>

namespace PublicTransportation
{

class Company;
class Line;
class Journey;
class Station;
class ProviderPluginDBusWrapperPrivate;

/**
 * @brief Provider plugin wrapper that uses DBus
 *
 * This class is a wrapper around the provider plugin,
 * that provides a clean method to interface with both
 * the plugin and DBus.
 *
 * It loads a plugin using load(), and performs
 * registration automatically.
 */
class PUBLICTRANSPORTATION_EXPORT ProviderPluginDBusWrapper : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param identifier DBus identifier.
     * @param parent parent object.
     */
    explicit ProviderPluginDBusWrapper(const QString &identifier, QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~ProviderPluginDBusWrapper();
    /**
     * @brief Load a plugin
     * @param plugin the plugin to load.
     * @return if the plugin has been successfully loaded.
     */
    bool load(const QString &plugin);
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<ProviderPluginDBusWrapperPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(ProviderPluginDBusWrapper)
    Q_PRIVATE_SLOT(d_func(), void slotServiceUnregistered(QString))
};

}

#endif // PUBLICTRANSPORTATION_PROVIDERPLUGINWRAPPER_H

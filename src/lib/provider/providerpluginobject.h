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

/**
 * @brief Base for a provider plugin
 *
 * This class is the recommanded base for a provider
 * plugin. It provides all the interfaces declared
 * in PublicTransportation::ProviderPluginInterface,
 * but also offers a QObject as a base.
 *
 * For more information about creating a provider plugin,
 * see \ref PublicTransportation::ProviderPluginInterface.
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
    explicit ProviderPluginObject(QObject *parent = 0): QObject(parent) {}
    /**
     * @brief Destructor
     */
    virtual ~ProviderPluginObject() {}
Q_SIGNALS:
    /**
     * @brief Waiting time retrieved
     * @param company company for which the waiting time is retrieved.
     * @param line line for which the waiting time is retrieved.
     * @param journey journey for which the waiting time is retrieved.
     * @param station station for which the waiting time is retrieved.
     * @param waitingTimes retrieved waiting time.
     */
    void waitingTimeRetrieved(const PublicTransportation::Company &company,
                              const PublicTransportation::Line &line,
                              const PublicTransportation::Journey &journey,
                              const PublicTransportation::Station &station,
                              const QList<PublicTransportation::WaitingTime> &waitingTimes);
};

}

#endif // PUBLICTRANSPORTATION_PROVIDERPLUGINOBJECT_H

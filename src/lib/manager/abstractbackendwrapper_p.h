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

#ifndef PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_P_H
#define PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_P_H

/**
 * @internal
 * @file abstractbackendwrapper_p.h
 * @short Definition of PublicTransportation::AbstractBackendWrapperPrivate
 */

#include "abstractbackendwrapper.h"

// Warning
//
// This file exists for the convenience
// of other publictransportation classes.
// This header file may change from version
// to version without notice or even be removed.

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::AbstractBackendWrapper
 */
struct RequestData
{
    /**
     * @internal
     * @brief Request
     */
    QString request;
    /**
     * @internal
     * @brief Request type
     */
    AbstractBackendWrapper::RequestType type;
};

/**
 * @internal
 * @brief Private class for PublicTransportation::AbstractBackendWrapper
 */
class AbstractBackendWrapperPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    AbstractBackendWrapperPrivate();
    /**
     * @internal
     * @brief Identifier
     */
    QString identifier;
    /**
     * @internal
     * @brief Executable
     */
    QString executable;
    /**
     * @internal
     * @brief Arguments
     */
    QMap<QString, QString> arguments;
    /**
     * @internal
     * @brief Status
     */
    AbstractBackendWrapper::Status status;
    /**
     * @internal
     * @brief Last error
     */
    QString lastError;
    /**
     * @internal
     * @brief Capabilities
     */
    QStringList capabilities;
    /**
     * @internal
     * @brief Requests
     */
    QMap<QString, RequestData *> requests;
};

}

#endif // PUBLICTRANSPORTATION_ABSTRACTBACKENDWRAPPER_P_H

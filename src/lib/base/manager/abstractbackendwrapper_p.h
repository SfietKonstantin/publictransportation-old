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

#ifndef PT2_ABSTRACTBACKENDWRAPPER_P_H
#define PT2_ABSTRACTBACKENDWRAPPER_P_H

// Warning
//
// This file exists for the convenience
// of other publictransportation classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file abstractbackendwrapper_p.h
 * @short Definition of PT2::AbstractBackendWrapperPrivate
 */

#include "abstractbackendwrapper.h"

#include <QtCore/QMap>


namespace PT2
{

/**
 * @internal
 * @brief Private class used in PT2::AbstractBackendWrapper
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
     * @brief Copyright
     */
    QString copyright;
    /**
     * @internal
     * @brief Requests
     */
    QMap<QString, RequestData *> requests;
};

}

#endif // PT2_ABSTRACTBACKENDWRAPPER_P_H

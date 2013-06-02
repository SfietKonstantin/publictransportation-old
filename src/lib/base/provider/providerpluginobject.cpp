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

#include "providerpluginobject.h"
#include "common/errorid.h"

namespace PT2
{

ProviderPluginObject::ProviderPluginObject(QObject *parent):
    QObject(parent)
{
}

ProviderPluginObject::~ProviderPluginObject()
{
}

//void ProviderPluginObject::retrieveCopyright(const QString &request)
//{
//    emit copyrightRetrieved(request, "Please implement the copyright");
//}

//void ProviderPluginObject::retrieveSuggestedStations(const QString &request,
//                                                     const QString &partialStation)
//{
//    Q_UNUSED(partialStation)
//    emit errorRetrieved(request, NOT_IMPLEMENTED,
//                        tr("SUGGEST_STATIONS capability is not implemented"));
//}

//void ProviderPluginObject::retrieveJourneysFromStation(const QString &request,
//                                                       const Station &station, int limit)
//{
//    Q_UNUSED(station)
//    Q_UNUSED(limit)
//    emit errorRetrieved(request, NOT_IMPLEMENTED,
//                        tr("JOURNEYS_FROM_STATION capability is not implemented"));
//}

//void ProviderPluginObject::retrieveJourneysAndWaitingTimesFromStation(const QString &request,
//                                                                      const Station &station,
//                                                                      int limit)
//{
//    Q_UNUSED(station)
//    Q_UNUSED(limit)
//    emit errorRetrieved(request, NOT_IMPLEMENTED,
//                        tr("JOURNEYS_WAITING_TIMES_FROM_STATION capability is not implemented"));
//}

//void ProviderPluginObject::retrieveWaitingTime(const QString &request, const Company &company,
//                                               const Line &line, const Journey &journey,
//                                               const Station &station)
//{
//    Q_UNUSED(company)
//    Q_UNUSED(line)
//    Q_UNUSED(journey)
//    Q_UNUSED(station)
//    emit errorRetrieved(request, NOT_IMPLEMENTED,
//                        tr("WAITING_TIME capability is not implemented"));
//}

//void ProviderPluginObject::retrieveStationsFromJourney(const QString &request,
//                                                       const Company &company,
//                                                       const Line &line, const Journey &journey,
//                                                       const Station &station)
//{
//    Q_UNUSED(company)
//    Q_UNUSED(line)
//    Q_UNUSED(journey)
//    Q_UNUSED(station)
//    emit errorRetrieved(request, NOT_IMPLEMENTED,
//                        tr("STATIONS_FROM_JOURNEY capability is not implemented"));
//}

}

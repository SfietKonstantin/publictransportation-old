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

/**
 * @file abstractbackendwrapper.cpp
 * @short Implementation of PT2::AbstractBackendWrapper
 */

#include "abstractbackendwrapper.h"
#include "abstractbackendwrapper_p.h"

#include <QtCore/QUuid>

#include "debug.h"
#include "common/errorid.h"
#include "common/company.h"
#include "common/line.h"
#include "common/ride.h"
#include "common/station.h"
//#include "common/waitingtime.h"
//#include "common/infojourneys.h"
//#include "common/journeyandwaitingtime.h"
//#include "common/infojourneywaitingtime.h"

namespace PT2
{

AbstractBackendWrapperPrivate::AbstractBackendWrapperPrivate()
{
     status = AbstractBackendWrapper::Stopped;
}

////// End of private class //////

AbstractBackendWrapper::AbstractBackendWrapper(const QString &identifier, const QString &executable,
                                               QObject *parent):
    QObject(parent), d_ptr(new AbstractBackendWrapperPrivate())
{
    Q_D(AbstractBackendWrapper);
    d->identifier = identifier;
    d->executable = executable;
}

AbstractBackendWrapper::AbstractBackendWrapper(AbstractBackendWrapperPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{

}

AbstractBackendWrapper::~AbstractBackendWrapper()
{
    Q_D(AbstractBackendWrapper);
    qDeleteAll(d->requests);
}

QString AbstractBackendWrapper::identifier() const
{
    Q_D(const AbstractBackendWrapper);
    return d->identifier;
}

AbstractBackendWrapper::Status AbstractBackendWrapper::status() const
{
    Q_D(const AbstractBackendWrapper);
    return d->status;
}

QString AbstractBackendWrapper::lastError() const
{
    Q_D(const AbstractBackendWrapper);
    return d->lastError;
}

QStringList AbstractBackendWrapper::capabilities() const
{
    Q_D(const AbstractBackendWrapper);
    return d->capabilities;
}

QString AbstractBackendWrapper::copyright() const
{
    Q_D(const AbstractBackendWrapper);
    return d->copyright;
}

void AbstractBackendWrapper::waitForStopped()
{
}

void AbstractBackendWrapper::registerError(const QString &request, const QString &errorId,
                                           const QString &error)
{
    Q_D(AbstractBackendWrapper);
    if (d->requests.contains(request)) {
        debug("abs-backend-wrapper") << "Request" << request << "failed";
        debug("abs-backend-wrapper") << errorId;
        debug("abs-backend-wrapper") << error;

        delete d->requests.take(request);
        emit errorRegistered(request, errorId, error);
    }
}

//void AbstractBackendWrapper::registerCopyright(const QString &request, const QString &copyright)
//{
//    Q_D(AbstractBackendWrapper);
//    if (d->requests.contains(request)) {
//        if (d->requests.value(request)->type != AbstractBackendWrapper::CopyrightType) {
//            registerError(request, INVALID_REQUEST_TYPE, "Invalid request type");
//            return;
//        }

//        debug("abs-backend-wrapper") << "Copyright registered";
//        debug("abs-backend-wrapper") << "Request" << request;
//        debug("abs-backend-wrapper") << copyright;

//        delete d->requests.take(request);
//        emit copyrightRegistered(request, copyright);
//    }
//}

//void AbstractBackendWrapper::registerSuggestedStations(const QString & request,
//                                                       const QList<Station> &suggestedStationList)
//{
//    Q_D(AbstractBackendWrapper);
//    if (d->requests.contains(request)) {
//        if (d->requests.value(request)->type != AbstractBackendWrapper::SuggestStationType) {
//            registerError(request, INVALID_REQUEST_TYPE, "Invalid request type");
//            return;
//        }

//        debug("abs-backend-wrapper") << "Suggested stations registered";
//        debug("abs-backend-wrapper") << "Request" << request;
//        debug("abs-backend-wrapper") << "list of suggested stations";
//        foreach (Station station, suggestedStationList) {
//            debug("abs-backend-wrapper") << station.name();
//        }

//        delete d->requests.take(request);
//        emit suggestedStationsRegistered(request, suggestedStationList);
//    }
//}

//void AbstractBackendWrapper::registerJourneysFromStation(const QString &request,
//                                                         const QList<InfoJourneys> &infoJourneyList)
//{
//    Q_D(AbstractBackendWrapper);
//    if (d->requests.contains(request)) {
//        if (d->requests.value(request)->type != AbstractBackendWrapper::JourneysFromStationType) {
//            registerError(request, INVALID_REQUEST_TYPE, "Invalid request type");
//            return;
//        }

//        debug("abs-backend-wrapper") << "Journeys from station registered";
//        debug("abs-backend-wrapper") << "Request" << request;
//        debug("abs-backend-wrapper") << "list of lines";
//        foreach (InfoJourneys infoJourneys, infoJourneyList) {
//            debug("abs-backend-wrapper") << infoJourneys.line().name();
//        }

//        delete d->requests.take(request);
//        emit journeysFromStationRegistered(request, infoJourneyList);
//    }
//}

//void AbstractBackendWrapper::registerJourneysAndWaitingTimesFromStation(const QString &request,
//                                    const QList<InfoJourneyWaitingTime> &infoJourneyWaitingTimeList)
//{
//    Q_D(AbstractBackendWrapper);
//    if (d->requests.contains(request)) {
//        if (d->requests.value(request)->type
//                != AbstractBackendWrapper::JourneysAndWaitingTimesFromStationType) {
//            registerError(request, INVALID_REQUEST_TYPE, "Invalid request type");
//            return;
//        }

//        debug("abs-backend-wrapper") << "Journeys and waiting times from station registered";
//        debug("abs-backend-wrapper") << "Request" << request;
//        debug("abs-backend-wrapper") << "list of lines";
//        foreach (InfoJourneyWaitingTime infoJourneyAndWaitingTime, infoJourneyWaitingTimeList) {
//            debug("abs-backend-wrapper") << infoJourneyAndWaitingTime.line().name();
//        }

//        delete d->requests.take(request);
//        emit journeysAndWaitingTimesFromStationRegistered(request, infoJourneyWaitingTimeList);
//    }
//}

//void AbstractBackendWrapper::registerWaitingTime(const QString &request,
//                                      const QList<JourneyAndWaitingTime> &journeyAndWaitingTimeList)
//{
//    Q_D(AbstractBackendWrapper);
//    if (d->requests.contains(request)) {
//        if (d->requests.value(request)->type != AbstractBackendWrapper::WaitingTimeType) {
//            registerError(request, INVALID_REQUEST_TYPE, "Invalid request type");
//            return;
//        }

//        debug("abs-backend-wrapper") << "Waiting time registered";
//        debug("abs-backend-wrapper") << "Request" << request;
//        debug("abs-backend-wrapper") << "list of waiting time";
//        foreach (JourneyAndWaitingTime journeyAndWaitingTime, journeyAndWaitingTimeList) {
//            debug("abs-backend-wrapper") << journeyAndWaitingTime.waitingTime().waitingTime();
//        }

//        delete d->requests.take(request);
//        emit waitingTimeRegistered(request, journeyAndWaitingTimeList);
//    }
//}

//void AbstractBackendWrapper::registerStationsFromJourney(const QString &request,
//                                                         const QList<Station> &stationList)
//{
//    Q_D(AbstractBackendWrapper);
//    if (d->requests.contains(request)) {
//        if (d->requests.value(request)->type != AbstractBackendWrapper::StationsFromJourneyType) {
//            registerError(request, INVALID_REQUEST_TYPE, "Invalid request type");
//            return;
//        }

//        debug("abs-backend-wrapper") << "Stations from journeys registered";
//        debug("abs-backend-wrapper") << "Request" << request;
//        debug("abs-backend-wrapper") << "list of stations";
//        foreach (Station station, stationList) {
//            debug("abs-backend-wrapper") << station.name();
//        }

//        delete d->requests.take(request);
//        emit stationsFromJourneyRegistered(request, stationList);
//    }
//}

QString AbstractBackendWrapper::executable() const
{
    Q_D(const AbstractBackendWrapper);
    return d->executable;
}

void AbstractBackendWrapper::setStatus(Status status)
{
    Q_D(AbstractBackendWrapper);
    if (d->status != status) {
        d->status = status;
        emit statusChanged();

        debug("abs-backend-wrapper") << "Status changed to" << d->status;
    }
}

void AbstractBackendWrapper::setLastError(const QString &lastError)
{
    Q_D(AbstractBackendWrapper);
    d->lastError = lastError;
    debug("abs-backend-wrapper") << "Last error:" << lastError;
}

void AbstractBackendWrapper::setCapabilities(const QStringList &capabilities)
{
    Q_D(AbstractBackendWrapper);
    if (d->capabilities != capabilities) {
        d->capabilities = capabilities;
        emit capabilitiesChanged();

        debug("abs-backend-wrapper") << "Capabilities changed";
    }
}

void AbstractBackendWrapper::setCopyright(const QString &copyright)
{
    Q_D(AbstractBackendWrapper);
    if (d->copyright != copyright) {
        d->copyright = copyright;
        emit copyrightChanged();

        debug("abs-backend-wrapper") << "Copyright changed";
    }
}

QString AbstractBackendWrapper::createRequest(RequestType requestType)
{
    Q_D(AbstractBackendWrapper);
    QString request = QUuid::createUuid().toString();

    debug("abs-backend-wrapper") << "Created request (request " << request
                                 << "and type" << requestType << ")";
    RequestData *requestData = new RequestData;
    requestData->request = request;
    requestData->type = requestType;
    d->requests.insert(request, requestData);

    return request;
}


}

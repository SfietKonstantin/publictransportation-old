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
 * @file abstractbackendwrapper.cpp
 * @short Implementation of PublicTransportation::AbstractBackendWrapper
 */

#include "abstractbackendwrapper.h"
#include "abstractbackendwrapper_p.h"

#include <QtCore/QUuid>

#include "debug.h"
#include "common/commonhelper.h"

namespace PublicTransportation
{

AbstractBackendWrapperPrivate::AbstractBackendWrapperPrivate()
{
     status = AbstractBackendWrapper::Stopped;
}

////// End of private class //////

AbstractBackendWrapper::AbstractBackendWrapper(const QString &identifier, const QString &executable,
                                               const QMap<QString, QString> &arguments,
                                               QObject *parent):
    QObject(parent), d_ptr(new AbstractBackendWrapperPrivate())
{
    Q_D(AbstractBackendWrapper);
    d->identifier = identifier;
    d->executable = executable;
    d->arguments = arguments;
}

AbstractBackendWrapper::AbstractBackendWrapper(AbstractBackendWrapperPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{

}

AbstractBackendWrapper::~AbstractBackendWrapper()
{
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

void AbstractBackendWrapper::waitForStopped()
{
}

void AbstractBackendWrapper::registerError(const QString &request, const QString &error)
{
    Q_D(AbstractBackendWrapper);
    if (d->requests.contains(request)) {
        debug("abs-backend-wrapper") << "Request" << request << "failed";
        debug("abs-backend-wrapper") << error;

        delete d->requests.take(request);
        emit errorRegistered(request, error);
    }
}

void AbstractBackendWrapper::registerSuggestedStations(const QString & request,
                                                       const QList<Station> &suggestedStations)
{
    Q_D(AbstractBackendWrapper);
    if (d->requests.contains(request)) {
        delete d->requests.take(request);
        debug("abs-backend-wrapper") << "Suggested stations registered";
        debug("abs-backend-wrapper") << "(Request" << request << ")";
        debug("abs-backend-wrapper") << "list of suggested stations";
        foreach (Station station, suggestedStations) {
            debug("abs-backend-wrapper") << station.name();
        }

        emit suggestedStationsRegistered(request, suggestedStations);
    }
}

void AbstractBackendWrapper::registerJourneysFromStation(const QString &request,
                                                         const QList<InfoJourneys> &infoJourneys)
{
    Q_D(AbstractBackendWrapper);
    if (d->requests.contains(request)) {
        delete d->requests.take(request);
        debug("abs-backend-wrapper") << "Journeys from station registered";
        debug("abs-backend-wrapper") << "(Request" << request << ")";
        debug("abs-backend-wrapper") << "list of lines";
        foreach (InfoJourneys infoJourneys, infoJourneys) {
            debug("abs-backend-wrapper") << infoJourneys.line().name();
        }

        emit journeysFromStationRegistered(request, infoJourneys);
    }
}

void AbstractBackendWrapper::registerWaitingTime(const QString &request,
                                                 const QList<WaitingTime> &waitingTimeList)
{
    Q_D(AbstractBackendWrapper);
    if (d->requests.contains(request)) {
        delete d->requests.take(request);
        debug("abs-backend-wrapper") << "Waiting time registered";
        debug("abs-backend-wrapper") << "(Request" << request << ")";
        debug("abs-backend-wrapper") << "list of waiting time";
        foreach (WaitingTime waitingTime, waitingTimeList) {
            debug("abs-backend-wrapper") << waitingTime.waitingTime();
        }

        emit waitingTimeRegistered(request, waitingTimeList);
    }
}

QString AbstractBackendWrapper::executable() const
{
    Q_D(const AbstractBackendWrapper);
    return d->executable;
}

QMap<QString, QString> AbstractBackendWrapper::arguments() const
{
    Q_D(const AbstractBackendWrapper);
    return d->arguments;
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

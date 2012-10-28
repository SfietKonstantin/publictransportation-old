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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_H

#include "publictransportationpluginhelper_global.h"
#include "abstractonlinehelper.h"

class QIODevice;
class QNetworkAccessManager;
namespace PublicTransportation
{

class Company;
class Line;
class Journey;
class Station;
class JourneyAndWaitingTime;
namespace PluginHelper
{

class AbstractWaitingTimeHelperPrivate;
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractWaitingTimeHelper:
        public AbstractOnlineHelper
{
    Q_OBJECT
public:
    explicit AbstractWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                       QObject *parent = 0);
    void setData(const Company &company, const Line &line,
                 const Journey &journey, const Station &station);
Q_SIGNALS:
    void waitingTimeRetrieved(const QString &request,
                  const QList<PublicTransportation::JourneyAndWaitingTime> journeysAndWaitingTimes);
protected:
    explicit AbstractWaitingTimeHelper(AbstractWaitingTimeHelperPrivate &dd, QObject *parent);
    Company company() const;
    Line line() const;
    Journey journey() const;
    Station station() const;
    virtual QList<JourneyAndWaitingTime> processData(QIODevice *input, bool *ok = 0,
                                                     QString *errorMessage = 0) = 0;
private:
    Q_DECLARE_PRIVATE(AbstractWaitingTimeHelper)
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_H

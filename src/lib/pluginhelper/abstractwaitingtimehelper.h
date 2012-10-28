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

#include <QtCore/QObject>

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
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractWaitingTimeHelper : public QObject
{
    Q_OBJECT
public:
    explicit AbstractWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                                 QObject *parent = 0);
    virtual ~AbstractWaitingTimeHelper();
    void get(const QString &request, const QString &url, const Company &company, const Line &line,
             const Journey &journey, const Station &station);
    void post(const QString &request, const QString &url, const QByteArray &data,
              const Company &company, const Line &line, const Journey &journey,
              const Station &station);
Q_SIGNALS:
    void errorRetrieved(const QString &request, const QString &errorId, const QString &error);
    void waitingTimeRetrieved(const QString &request,
                  const QList<PublicTransportation::JourneyAndWaitingTime> journeysAndWaitingTimes);
protected:
    Company company() const;
    Line line() const;
    Journey journey() const;
    Station station() const;
    virtual QList<JourneyAndWaitingTime> processData(QIODevice *input, bool *ok = 0,
                                                     QString *errorMessage = 0) = 0;
    QScopedPointer<AbstractWaitingTimeHelperPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractWaitingTimeHelper)
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTWAITINGTIMEHELPER_H

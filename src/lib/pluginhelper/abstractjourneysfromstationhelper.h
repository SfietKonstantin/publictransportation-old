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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_H

#include "publictransportationpluginhelper_global.h"

#include "abstractonlinehelper.h"

class QIODevice;
class QNetworkAccessManager;
class QNetworkRequest;
namespace PublicTransportation
{

class Station;
class InfoJourneys;
namespace PluginHelper
{

class AbstractJourneysFromStationHelperPrivate;
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractJourneysFromStationHelper:
        public AbstractOnlineHelper
{
    Q_OBJECT
public:
    explicit AbstractJourneysFromStationHelper(QNetworkAccessManager *networkAccessManager,
                                               QObject *parent = 0);
    void setData(const Station &station, int limit);
Q_SIGNALS:
    void journeysFromStationRetrieved(const QString &request,
                                 const QList<PublicTransportation::InfoJourneys> &infoJourneysList);
protected:
    explicit AbstractJourneysFromStationHelper(AbstractJourneysFromStationHelperPrivate &dd,
                                               QObject *parent);
    Station station() const;
    int limit() const;
    virtual QList<InfoJourneys> processData(QIODevice *input, bool *ok = 0,
                                            QString *errorMessage = 0) = 0;
private:
    Q_DECLARE_PRIVATE(AbstractJourneysFromStationHelper)

};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTJOURNEYSFROMSTATIONHELPER_H

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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTSUGGESTEDSTATIONSHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTSUGGESTEDSTATIONSHELPER_H

#include "publictransportationpluginhelper_global.h"
#include "abstractonlinehelper.h"

class QIODevice;
namespace PublicTransportation
{

class Station;
namespace PluginHelper
{

class AbstractSuggestedStationsHelperPrivate;
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractSuggestedStationsHelper:
        public AbstractOnlineHelper
{
    Q_OBJECT
public:
    explicit AbstractSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager,
                                             QObject *parent = 0);
    void setData(const QString &partialStation);
Q_SIGNALS:
    void suggestedStationsRetrieved(const QString &request,
                                   const QList<PublicTransportation::Station> suggestedStationList);
protected:
    explicit AbstractSuggestedStationsHelper(AbstractSuggestedStationsHelperPrivate &dd,
                                             QObject *parent);
    QString partialStation() const;
    virtual QList<Station> processData(QIODevice *input, bool *ok = 0,
                                       QString *errorMessage = 0) = 0;
private:
    Q_DECLARE_PRIVATE(AbstractSuggestedStationsHelper)

};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTSUGGESTEDSTATIONSHELPER_H

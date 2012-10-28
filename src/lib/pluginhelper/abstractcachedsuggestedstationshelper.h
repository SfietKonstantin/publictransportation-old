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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTCACHEDSUGGESTEDSTATIONSHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTCACHEDSUGGESTEDSTATIONSHELPER_H

#include "publictransportationpluginhelper_global.h"
#include "abstractsuggestedstationshelper.h"

namespace PublicTransportation
{

namespace PluginHelper
{

class AbstractCachedSuggestedStationsHelperPrivate;
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractCachedSuggestedStationsHelper:
        public AbstractSuggestedStationsHelper
{
    Q_OBJECT
public:
    explicit AbstractCachedSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager,
                                                   QObject *parent = 0);
    virtual ~AbstractCachedSuggestedStationsHelper();
    void suggestGet(const QString &request, const QNetworkRequest &networkRequest,
                    const QString &partialStation);
    void suggestPost(const QString &request, const QNetworkRequest &networkRequest,
                     const QByteArray &data, const QString &partialStation);
protected:
    virtual QList<Station> processData(QIODevice *input, bool *ok = 0,
                                       QString *errorMessage = 0) = 0;
private:
    Q_DECLARE_PRIVATE(AbstractCachedSuggestedStationsHelper)

};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTCACHEDSUGGESTEDSTATIONSHELPER_H

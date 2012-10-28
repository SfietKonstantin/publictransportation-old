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

#ifndef PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTONLINEHELPER_H
#define PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTONLINEHELPER_H

#include "publictransportationpluginhelper_global.h"

#include <QtCore/QObject>

class QNetworkAccessManager;
class QNetworkRequest;
namespace PublicTransportation
{

class Station;
namespace PluginHelper
{

class AbstractOnlineHelperPrivate;
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractOnlineHelper : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractOnlineHelper();
    void get(const QString &request, const QNetworkRequest &networkRequest);
    void post(const QString &request, const QNetworkRequest &networkRequest,const QByteArray &data);
Q_SIGNALS:
    void errorRetrieved(const QString &request, const QString &errorId, const QString &error);
protected:
    explicit AbstractOnlineHelper(AbstractOnlineHelperPrivate &dd, QObject *parent);
    QScopedPointer<AbstractOnlineHelperPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractOnlineHelper)
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
    Q_PRIVATE_SLOT(d_func(), void slotError(QNetworkReply::NetworkError))

};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTSUGGESTEDSTATIONSHELPER_H

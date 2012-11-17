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

/**
 * @file abstractonlinehelper.h
 * @short Definition of PublicTransportation::PluginHelper::AbstractOnlineHelper
 */

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

/**
 * @brief A class used to deal with online data
 *
 * This class provides a way to get online data without dealing
 * with network reply management. It provides two methods, get()
 * and post() that are used to do a GET or POST request.
 *
 * Network reply management is done in the private class associated
 * to this one, AbstractOnlineHelperPrivate. This class should not be
 * used directly, and subclasses should be preferred.
 *
 * This classes, and also subclasses, provides direct signals to interface
 * with the backend system, that's why, doing a get or post also uses the
 * request identifier.
 */
class PUBLICTRANSPORTATIONPLUGINHELPER_EXPORT AbstractOnlineHelper : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Destructor
     */
    virtual ~AbstractOnlineHelper();
    /**
     * @brief Perform a GET request
     * @param request request.
     * @param networkRequest network request.
     */
    void get(const QString &request, const QNetworkRequest &networkRequest);
    /**
     * @brief Perform a POST request
     * @param request request.
     * @param networkRequest network request.
     * @param data data used for the POST request.
     */
    void post(const QString &request, const QNetworkRequest &networkRequest,const QByteArray &data);
Q_SIGNALS:
    /**
     * @brief Error retrieved
     * @param request request.
     * @param errorId error id.
     * @param error error.
     */
    void errorRetrieved(const QString &request, const QString &errorId, const QString &error);
protected:
    /**
     * @brief D-pointer based constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractOnlineHelper(AbstractOnlineHelperPrivate &dd, QObject *parent);
    /**
     * @brief D-pointer
     */
    QScopedPointer<AbstractOnlineHelperPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractOnlineHelper)
    /// \cond buggy-doxygen-doc
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
    Q_PRIVATE_SLOT(d_func(), void slotError(QNetworkReply::NetworkError))
    /// \endcond

};

}

}

#endif // PUBLICTRANSPORTATION_PLUGINHELPER_ABSTRACTSUGGESTEDSTATIONSHELPER_H

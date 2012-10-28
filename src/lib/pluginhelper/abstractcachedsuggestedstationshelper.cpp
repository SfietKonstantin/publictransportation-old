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

#include "abstractcachedsuggestedstationshelper.h"
#include "abstractsuggestedstationshelper_p.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "common/errorid.h"
#include "common/station.h"
#include "debug.h"
#include "languagehelper.h"

namespace PublicTransportation
{

namespace PluginHelper
{

class AbstractCachedSuggestedStationsHelperPrivate: public AbstractSuggestedStationsHelperPrivate
{
public:
    AbstractCachedSuggestedStationsHelperPrivate(AbstractCachedSuggestedStationsHelper *q);
    void provideSuggestedStations(const QString &partialStation);
    virtual void slotFinished();
    bool cached;
    QList<Station> stations;
private:
    Q_DECLARE_PUBLIC(AbstractCachedSuggestedStationsHelper)
};

AbstractCachedSuggestedStationsHelperPrivate
    ::AbstractCachedSuggestedStationsHelperPrivate(AbstractCachedSuggestedStationsHelper *q):
    AbstractSuggestedStationsHelperPrivate(q)
{
    cached = false;
}

void AbstractCachedSuggestedStationsHelperPrivate::slotFinished()
{
    Q_Q(AbstractCachedSuggestedStationsHelper);
    debug("helper-cachedsuggestedstations") << "Data retrieved from url" << reply->url().toString();

    bool ok;
    QString errorMessage;
    QList<Station> processedStations = q->processData(reply, &ok, &errorMessage);
    if (!ok) {
        emit q->errorRetrieved(request, BACKEND_WARNING, errorMessage);
    } else {
        stations = processedStations;
        cached = true;
        provideSuggestedStations(partialStation);
    }
    reply->deleteLater();
    reply = 0;
    request = QString();
    partialStation = QString();
}

void AbstractCachedSuggestedStationsHelperPrivate
    ::provideSuggestedStations(const QString &partialStation)
{
    Q_Q(AbstractCachedSuggestedStationsHelper);
    QList<Station> suggestedStations;
    QString unaccentedPartialStation = LanguageHelper::unaccent(partialStation);
    foreach (Station station, stations) {
        if (LanguageHelper::unaccent(station.name()).startsWith(unaccentedPartialStation)) {
            suggestedStations.append(station);
        }
    }
    foreach (Station station, stations) {
        if (LanguageHelper::unaccent(station.name()).contains(unaccentedPartialStation)
            && !suggestedStations.contains(station)) {
            suggestedStations.append(station);
        }
    }
    emit q->suggestedStationsRetrieved(request, suggestedStations);
}

////// End of private class //////

AbstractCachedSuggestedStationsHelper
    ::AbstractCachedSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractSuggestedStationsHelper(*(new AbstractCachedSuggestedStationsHelperPrivate(this)), parent)
{
    Q_D(AbstractCachedSuggestedStationsHelper);
    d->networkAccessManager = networkAccessManager;
}

AbstractCachedSuggestedStationsHelper::~AbstractCachedSuggestedStationsHelper()
{
}

void AbstractCachedSuggestedStationsHelper::suggestGet(const QString &request,
                                                       const QNetworkRequest &networkRequest,
                                                       const QString &partialStation)
{
    Q_D(AbstractCachedSuggestedStationsHelper);
    if (!d->cached) {
        get(request, networkRequest, partialStation);
    } else {
        d->provideSuggestedStations(partialStation);
    }
}

void AbstractCachedSuggestedStationsHelper::suggestPost(const QString &request,
                                                        const QNetworkRequest &networkRequest,
                                                        const QByteArray &data,
                                                        const QString &partialStation)
{
    Q_D(AbstractCachedSuggestedStationsHelper);
    if (!d->cached) {
        post(request, networkRequest, data, partialStation);
    } else {
        d->provideSuggestedStations(partialStation);
    }
}

}

}

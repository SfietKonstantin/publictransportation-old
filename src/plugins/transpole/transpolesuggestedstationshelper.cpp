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

#include "transpolesuggestedstationshelper.h"

#include <QtCore/QRegExp>
#include <QtCore/QVariantMap>

#include "common/station.h"
#include "languagehelper.h"

using namespace PublicTransportation::PluginHelper;

namespace PublicTransportation
{

namespace Provider
{

TranspoleSuggestedStationsHelper
   ::TranspoleSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager, QObject *parent):
    PluginHelper::AbstractSuggestedStationsHelper(networkAccessManager, parent)
{
}

QList<Station> TranspoleSuggestedStationsHelper::processData(QIODevice *input, bool *ok,
                                                             QString *errorMessage)
{
    QRegExp idRegExp ("<a href=\"#\" id=\"([^\"]*)\"");
    QRegExp lineNameRegExp ("<span class=\"lineName\">([^<]*)</span>");
    QRegExp foundRegExp ("pour l'arr[^t]*t ([^\\(]*)\\(([^\\)]*)");

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.transpole");

    QString currentId;
    QList<Station> suggestedStations;

    while (!input->atEnd()) {
        QString data = input->readLine();
        if (currentId.isEmpty()) {
            // We already found the correct station
            if (data.indexOf(foundRegExp) != -1) {
                Station station;
                station.setDisambiguation(disambiguation);
                station.setName(LanguageHelper::unstripHtmlAccents(foundRegExp.cap(1).trimmed()));
                QVariantMap properties;
                properties.insert("code", foundRegExp.cap(2));
                properties.insert("backendName", "Transpole");
                station.setProperties(properties);
                suggestedStations.append(station);
                break;
            }

            // Not found
            if (data.contains("Aucun")) {
                break;
            }

            if (data.indexOf(idRegExp) != -1) {
                currentId = idRegExp.cap(1);
            }
        } else {
            if (data.indexOf(lineNameRegExp) != -1) {
                Station station;
                station.setDisambiguation(disambiguation);
                station.setName(LanguageHelper::unstripHtmlAccents(lineNameRegExp.cap(1)));
                QVariantMap properties;
                properties.insert("code", currentId);
                properties.insert("providerName", "Transpole");
                station.setProperties(properties);
                suggestedStations.append(station);

                currentId = QString();
            }
        }
    }

    if (ok) {
        *ok = true;
    }

    if (errorMessage) {
        *errorMessage = QString();
    }

    return suggestedStations;
}

}

}

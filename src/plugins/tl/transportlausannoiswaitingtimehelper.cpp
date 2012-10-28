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

#include "transportlausannoiswaitingtimehelper.h"

#include <parser.h>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>
#include <QtCore/QTime>
#include <QtCore/QVariantMap>

#include "common/journeyandwaitingtime.h"
#include "debug.h"

namespace PublicTransportation
{

namespace Provider
{

TransportLausannoisWaitingTimeHelper
    ::TransportLausannoisWaitingTimeHelper(QNetworkAccessManager *networkAccessManager, QObject *parent):
    PluginHelper::AbstractWaitingTimeHelper(networkAccessManager, parent)
{
}

QList<JourneyAndWaitingTime> TransportLausannoisWaitingTimeHelper::processData(QIODevice *input,
                                                                        bool *ok,
                                                                        QString *errorMessage)
{
    QJson::Parser parser;

    QList<JourneyAndWaitingTime> journeysAndWaitingTimes;
    QVariant parsedValue = parser.parse(input);
    if (!parsedValue.isValid()) {
        if (ok) {
            *ok = false;
        }
        if (errorMessage) {
            *errorMessage = "Failed to get information from TL website";
        }
        return journeysAndWaitingTimes;
    }

    QVariantList waitTimeList = parsedValue.toList();
    QTime currentTime = QTime::currentTime();

    foreach (QVariant waitTimeEntry, waitTimeList) {
        QVariantMap waitTimeMap = waitTimeEntry.toMap();
        QString destination = waitTimeMap.value("destination").toString();

        QString time = waitTimeMap.value("time").toString();
        debug("tl-plugin") << time;

        Journey newJourney = journey();
        QVariantMap journeyProperties = newJourney.properties();
        journeyProperties.insert("to", destination);
        journeyProperties.insert("destination", destination);
        newJourney.setProperties(journeyProperties);

        QVariantMap properties;
        properties.insert("destination", destination);

        WaitingTime waitingTime;


        QRegExp timeRegExp("(\\d\\d):(\\d\\d)");
        QRegExp realtimeRegExp("(\\d+)");
        if (time.indexOf(timeRegExp) != -1) {
            QTime nextTime = QTime(timeRegExp.capturedTexts().at(1).toInt(),
                                   timeRegExp.capturedTexts().at(2).toInt());
            int minutes = ((currentTime.secsTo(nextTime) / 60) + 1440) % 1440;
            waitingTime.setWaitingTime(minutes);
            properties.insert("type", "timetable");
            waitingTime.setProperties(properties);
        } else if (time.indexOf(realtimeRegExp) != -1) {
            int minutes = realtimeRegExp.capturedTexts().at(1).toInt();
            waitingTime.setWaitingTime(minutes);
            properties.insert("type", "realtime");
            waitingTime.setProperties(properties);
        } else if (time.contains("now")) {
            waitingTime.setWaitingTime(0);
            properties.insert("type", "realtime");
            waitingTime.setProperties(properties);
        }
        journeysAndWaitingTimes.append(JourneyAndWaitingTime(newJourney, waitingTime));
    }

    if (ok) {
        *ok = true;
    }

    if (errorMessage) {
        *errorMessage = QString();
    }

    return journeysAndWaitingTimes;
}

}

}

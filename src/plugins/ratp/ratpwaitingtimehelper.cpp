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

#include "ratpwaitingtimehelper.h"

#include <QtCore/QIODevice>
#include <QtCore/QTime>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>
#include <QtCore/QVariantMap>

#include "common/journeyandwaitingtime.h"
#include "debug.h"

#include "languagehelper.h"

using namespace PublicTransportation::PluginHelper;

namespace PublicTransportation
{

namespace Provider
{

RatpWaitingTimeHelper::RatpWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                             QObject *parent):
    PluginHelper::AbstractWaitingTimeHelper(networkAccessManager, parent)
{
}

QList<JourneyAndWaitingTime> RatpWaitingTimeHelper::processData(QIODevice *input, bool *ok,
                                                                QString *errorMessage)
{
    QList<JourneyAndWaitingTime> journeysAndWaitingTimeList;

    QTime currentTime = QTime::currentTime();
    QRegExp timeMetroRegExp ("&gt;&nbsp;([^<]*)</div><div[^>]*><b>([^<]*)");
    QRegExp timeRerRegExp ("&gt;&nbsp;([^<]*)</div><div[^>]*><a[^>]*>([^<]*)</a></div><div[^>]*>\
<b>([^<]*)");
    QRegExp timeRegExp("(\\d\\d):(\\d\\d)");
    while (!input->atEnd()) {
        QVariantMap journeyProperties = journey().properties();

        QString minutesString;
        QVariantMap properties;
        QString data = input->readLine();
        if (data.indexOf(timeMetroRegExp) != -1) {
            QString destination = timeMetroRegExp.cap(1);
            properties.insert("destination", LanguageHelper::unstripHtmlAccents(destination));
            minutesString = timeMetroRegExp.cap(2);
        } else if (data.indexOf(timeRerRegExp) != -1) {
            QString destination = timeRerRegExp.cap(1);
            destination = LanguageHelper::unstripHtmlAccents(destination);
            properties.insert("destination", destination);
            journeyProperties.insert("to", destination);
            journeyProperties.insert("destination", destination);
            properties.insert("train", LanguageHelper::unstripHtmlAccents(timeRerRegExp.cap(2)));
            minutesString = timeRerRegExp.cap(3);
            debug("test") << minutesString;
        }

        if (!minutesString.isEmpty()) {
            int minutes = -1;
            if (minutesString.contains("Train")) {
                minutes = 0;
            } else if (minutesString.contains("mn")) {
                minutes = minutesString.remove("mn").trimmed().toInt();
            } else if (minutesString.indexOf(timeRegExp) != -1) {
                QTime nextTime = QTime(timeRegExp.capturedTexts().at(1).toInt(),
                                       timeRegExp.capturedTexts().at(2).toInt());
                minutes = ((currentTime.secsTo(nextTime) / 60) + 1440) % 1440;
            }

            Journey newJourney = journey();
            newJourney.setProperties(journeyProperties);

            WaitingTime waitingTime;
            waitingTime.setProperties(properties);
            waitingTime.setWaitingTime(minutes);
            journeysAndWaitingTimeList.append(JourneyAndWaitingTime(newJourney, waitingTime));
        }
    }

    if (ok) {
        *ok = true;
    }

    if (errorMessage) {
        *errorMessage = QString();
    }

    return journeysAndWaitingTimeList;
}

}

}

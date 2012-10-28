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

#include "ratp.h"

#include <QtCore/QFile>
#include <QtCore/QtPlugin>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtXml/QDomDocument>

#include "debug.h"
#include "common/errorid.h"
#include "common/capabilitiesconstants.h"
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/infojourneys.h"
#include "common/journeyandwaitingtime.h"

namespace PublicTransportation
{

namespace Provider
{

class RatpPrivate
{
public:
    RatpPrivate(Ratp *q);
    static QString unaccent(const QString &string);
    static QString unstripHtmlAccents(const QString &string);
    void slotWaitingTimeFinished();
    QStringList stations;
    QNetworkAccessManager *nam;
    Journey waitingTimeJourney;
    QNetworkReply *waitingTimeReply;
    QString waitingTimeRequest;
private:
    Ratp * const q_ptr;
    Q_DECLARE_PUBLIC(Ratp)
};

RatpPrivate::RatpPrivate(Ratp *q):
    q_ptr(q)
{
    waitingTimeReply = 0;

    QFile file (":/data/backward/stations.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        debug("ratp-plugin") << "Failed to read" << file.fileName().constData();
        return;
    }
    QTextStream fileStream (&file);
    while (!fileStream.atEnd()) {
        QString line = fileStream.readLine().trimmed();
        if (!line.isEmpty()) {
            stations.append(line);
        }
    }

    file.close();

}

QString RatpPrivate::unaccent(const QString &string)
{
    QString canonicalForm = string.toLower().normalized(QString::NormalizationForm_D);
    QString returnedString;
    foreach (QChar c, canonicalForm) {
        if (c.category() != QChar::Mark_NonSpacing &&
            c.category() != QChar::Mark_SpacingCombining) {
              returnedString.append(c);
         }
    }

    return returnedString;
}

QString RatpPrivate::unstripHtmlAccents(const QString &string)
{
    QString newString = string;
    newString.replace("&Agrave;", QString::fromUtf8("À"));
    newString.replace("&agrave;", QString::fromUtf8("à"));
    newString.replace("&Acirc;", QString::fromUtf8("Â"));
    newString.replace("&acirc;", QString::fromUtf8("â"));
    newString.replace("&Auml;", QString::fromUtf8("Ä"));
    newString.replace("&auml;", QString::fromUtf8("ä"));
    newString.replace("&Egrave;", QString::fromUtf8("È"));
    newString.replace("&egrave;", QString::fromUtf8("è"));
    newString.replace("&Eacute;", QString::fromUtf8("É"));
    newString.replace("&eacute;", QString::fromUtf8("é"));
    newString.replace("&Ecirc;", QString::fromUtf8("Ê"));
    newString.replace("&ecirc;", QString::fromUtf8("ê"));
    newString.replace("&Euml;", QString::fromUtf8("Ë"));
    newString.replace("&euml;", QString::fromUtf8("ë"));
    newString.replace("&Icirc;", QString::fromUtf8("Î"));
    newString.replace("&icirc;", QString::fromUtf8("î"));
    newString.replace("&Iuml;", QString::fromUtf8("Ï"));
    newString.replace("&iuml;", QString::fromUtf8("ï"));
    newString.replace("&Ocirc;", QString::fromUtf8("Ô"));
    newString.replace("&ocirc;", QString::fromUtf8("ô"));
    newString.replace("&Ouml;", QString::fromUtf8("Ö"));
    newString.replace("&ouml;", QString::fromUtf8("ö"));
    newString.replace("&Ugrave;", QString::fromUtf8("Ù"));
    newString.replace("&ugrave;", QString::fromUtf8("ù"));
    newString.replace("&Ucirc;", QString::fromUtf8("Û"));
    newString.replace("&ucirc;", QString::fromUtf8("û"));
    newString.replace("&Uuml;", QString::fromUtf8("Ü"));
    newString.replace("&uuml;", QString::fromUtf8("ü"));
    newString.replace("&Yuml;", QString::fromUtf8("Ÿ"));
    newString.replace("&yuml;", QString::fromUtf8("ÿ"));

    return newString;
}

void RatpPrivate::slotWaitingTimeFinished()
{
    Q_Q(Ratp);
    debug("ratp-plugin") << "Data retrieved from url" << waitingTimeReply->url().toString();

    QList<JourneyAndWaitingTime> journeysAndWaitingTimeList;

    QTime currentTime = QTime::currentTime();
    QRegExp timeMetroRegExp ("&gt;&nbsp;([^<]*)</div><div[^>]*><b>([^<]*)");
    QRegExp timeRerRegExp ("&gt;&nbsp;([^<]*)</div><div[^>]*><a[^>]*>([^<]*)</a></div><div[^>]*>\
<b>([^<]*)");
    QRegExp timeRegExp("(\\d\\d):(\\d\\d)");
    while (!waitingTimeReply->atEnd()) {
        QVariantMap journeyProperties = waitingTimeJourney.properties();

        QString minutesString;
        QVariantMap properties;
        QString data = waitingTimeReply->readLine();
        if (data.indexOf(timeMetroRegExp) != -1) {
            QString destination = timeMetroRegExp.cap(1);
            properties.insert("destination", unstripHtmlAccents(destination));
            minutesString = timeMetroRegExp.cap(2);
        } else if (data.indexOf(timeRerRegExp) != -1) {
            QString destination = timeRerRegExp.cap(1);
            destination = unstripHtmlAccents(destination);
            properties.insert("destination", destination);
            journeyProperties.insert("to", destination);
            journeyProperties.insert("destination", destination);
            properties.insert("train", unstripHtmlAccents(timeRerRegExp.cap(2)));
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

            Journey journey = waitingTimeJourney;
            waitingTimeJourney.setProperties(journeyProperties);

            WaitingTime waitingTime;
            waitingTime.setProperties(properties);
            waitingTime.setWaitingTime(minutes);
            journeysAndWaitingTimeList.append(JourneyAndWaitingTime(journey,
                                                                    waitingTime));
        }
    }

    emit q->waitingTimeRetrieved(waitingTimeRequest, journeysAndWaitingTimeList);
    waitingTimeReply->deleteLater();
    waitingTimeJourney = Journey();
}

////// End of private class //////

Ratp::Ratp(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new RatpPrivate(this))
{
    Q_D(Ratp);
    d->nam = new QNetworkAccessManager(this);
}

QStringList Ratp::capabilities() const
{
    QStringList capabilities;
    capabilities.append(SUGGEST_STATIONS);
    capabilities.append(JOURNEYS_FROM_STATION);
    capabilities.append(WAITING_TIME);
    return capabilities;
}

void Ratp::retrieveCopyright(const QString &request)
{
    QString copyright = tr("This provider uses wap.ratp.fr.") + "\n"
                        + QString::fromUtf8("RATP - Tous droits réservés");
    emit copyrightRetrieved(request, copyright);
}

void Ratp::retrieveSuggestedStations(const QString &request,
                                                    const QString &partialStation)
{
    Q_D(Ratp);
    if (partialStation.size() < 2) {
        emit suggestedStationsRetrieved(request, QList<Station>());
        return;
    }

    QList<Station> suggestedStations;
    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.ratp");

    QVariantMap properties;
    properties.insert("backendName", "RATP");


    foreach (QString stationName, d->stations) {
        if (d->unaccent(stationName).startsWith(d->unaccent(partialStation))) {
            Station station (disambiguation, stationName, properties);
            suggestedStations.append(station);
        }
    }
    foreach (QString stationName, d->stations) {
        if (d->unaccent(stationName).contains(d->unaccent(partialStation))) {
            bool added = false;
            foreach (Station station, suggestedStations) {
                if (station.name() == stationName) {
                    added = true;
                }
            }

            if (!added) {
                Station station (disambiguation, stationName, properties);
                suggestedStations.append(station);
            }
        }
    }

    emit suggestedStationsRetrieved(request, suggestedStations);
}

void Ratp::retrieveJourneysFromStation(const QString &request, const Station &station, int limit)
{
    Q_UNUSED(limit)
    QString fileName = QString(":/data/backward/%1.xml").arg(station.name().at(0).toLower());

    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        debug("ratp-plugin") << "Failed to read" << fileName.toAscii().constData();
        emit errorRetrieved(request, BACKEND_WARNING, QString("Failed to read %1").arg(fileName));
        return;
    }

    QDomDocument document;
    document.setContent(&file);

    file.close();

    QDomElement foundElement;
    QDomElement currentElement = document.documentElement().firstChildElement();

    while (!currentElement.isNull() && foundElement.isNull()) {
        if (currentElement.attribute("name") == station.name()) {
            foundElement = currentElement;
        }
        currentElement = currentElement.nextSiblingElement();
    }

    if (foundElement.isNull()) {
        debug("ratp-plugin") << "Failed to find station" << station.name().toAscii().constData();
        emit errorRetrieved(request, BACKEND_WARNING,
                            QString("Failed to find station %1").arg(station.name()));
        return;
    }

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.ratp");
    Company company;
    company.setDisambiguation(disambiguation);
    company.setName("RATP");

    QList<InfoJourneys> infoJourneysList;
    currentElement = foundElement.firstChildElement();
    while (!currentElement.isNull()) {
        InfoJourneys infoJourneys;
        Line line;
        line.setName(currentElement.attribute("name"));
        QVariantMap properties;
        properties.insert("id", currentElement.attribute("id"));
        properties.insert("network", currentElement.attribute("network"));
        line.setDisambiguation(disambiguation);
        line.setProperties(properties);
        infoJourneys.setCompany(company);
        infoJourneys.setLine(line);

        QList<QPair <Journey, Station> > journeysStations;
        QDomElement journeyElement = currentElement.firstChildElement();
        while (!journeyElement.isNull()) {
            Journey journey;
            Station preciseStation;
            journey.setName(journeyElement.attribute("name"));
            preciseStation.setName(station.name());
            QVariantMap journeyProperties;
            QVariantMap stationProperties;
            journeyProperties.insert("id", journeyElement.attribute("id"));
            journeyProperties.insert("to", journeyElement.attribute("to"));
            stationProperties.insert("id", journeyElement.attribute("stationId"));
            journey.setDisambiguation(disambiguation);
            journey.setProperties(journeyProperties);
            preciseStation.setDisambiguation(disambiguation);
            preciseStation.setProperties(stationProperties);
            journeysStations.append(QPair<Journey, Station>(journey, preciseStation));

            journeyElement = journeyElement.nextSiblingElement();
        }

        infoJourneys.setJourneysAndStations(journeysStations);
        infoJourneysList.append(infoJourneys);

        currentElement = currentElement.nextSiblingElement();
    }

    debug("ratp-plugin") << infoJourneysList.count();

    emit journeysFromStationRetrieved(request, infoJourneysList);
}

void Ratp::retrieveWaitingTime(const QString &request, const Company &company, const Line &line,
                               const Journey &journey, const Station &station)
{
    Q_D(Ratp);
    Q_UNUSED(company);
    QString urlString = "http://wap.ratp.fr/siv/schedule?service=next&reseau=%1&lineid=%2&\
directionsens=%3&stationid=%4";
            urlString = urlString.arg(line.properties().value("network").toString(),
                                      line.properties().value("id").toString(),
                                      journey.properties().value("id").toString(),
                                      station.properties().value("id").toString());

    d->waitingTimeRequest = request;
    d->waitingTimeJourney = journey;
    d->waitingTimeReply = d->nam->get(QNetworkRequest(QUrl(urlString)));
    connect(d->waitingTimeReply, SIGNAL(finished()), this, SLOT(slotWaitingTimeFinished()));
}

}

}

#include "moc_ratp.cpp"

Q_EXPORT_PLUGIN2(ratp, PublicTransportation::Provider::Ratp)

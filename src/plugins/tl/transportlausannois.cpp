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

#include "transportlausannois.h"

#include <QtCore/QFile>
#include <QtCore/QtPlugin>
#include <QtCore/QTime>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <parser.h>

#include "debug.h"
#include "common/capabilitiesconstants.h"
#include "common/company.h"

namespace PublicTransportation
{

namespace Provider
{

class TransportLausannoisPrivate
{
public:
    TransportLausannoisPrivate(TransportLausannois *q);
    void slotFinished();
    QList<Company> companies;
    QNetworkAccessManager *nam;

    Company companyForWaitTime;
    Line lineForWaitTime;
    Journey journeyForWaitTime;
    Station stationForWaitTime;
private:
    TransportLausannois * const q_ptr;
    Q_DECLARE_PUBLIC(TransportLausannois)
};

TransportLausannoisPrivate::TransportLausannoisPrivate(TransportLausannois *q):
    q_ptr(q)
{
}

void TransportLausannoisPrivate::slotFinished()
{
    Q_Q(TransportLausannois);
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(q->sender());

    debug("tl-plugin") << "Data retrieved from url" << reply->url().toString();
    QJson::Parser parser;

    QList<WaitingTime> waitingTimes;
    QVariantList waitTimeList = parser.parse(reply).toList();
    foreach (QVariant waitTimeEntry, waitTimeList) {
        QVariantMap waitTimeMap = waitTimeEntry.toMap();
        QString stop = waitTimeMap.value("stop").toString();
        QString destination = waitTimeMap.value("destination").toString();

        QString time = waitTimeMap.value("time").toString();

        QVariantMap properties;
        properties.insert("name", QString("%1 > %2").arg(stop, destination));

        WaitingTime waitingTime;

        QRegExp timeRegExp("(\\d\\d):(\\d\\d)");
        QRegExp realtimeRegExp("(\\d+)");
        QTime currentTime = QTime::currentTime();
        if (time.indexOf(timeRegExp) != -1) {
            QTime nextTime = QTime(timeRegExp.capturedTexts().at(1).toInt(),
                                   timeRegExp.capturedTexts().at(2).toInt());
            int minutes = currentTime.secsTo(nextTime) / 60;
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
        waitingTimes.append(waitingTime);
    }

    q->waitingTimeRetrieved(companyForWaitTime, lineForWaitTime,
                            journeyForWaitTime, stationForWaitTime, waitingTimes);

    companyForWaitTime = Company();
    lineForWaitTime = Line();
    journeyForWaitTime = Journey();
    stationForWaitTime = Station();
}

////// End of private class //////

TransportLausannois::TransportLausannois(QObject *parent) :
    ProviderPluginObject(parent), d_ptr(new TransportLausannoisPrivate(this))
{
    Q_D(TransportLausannois);
    QVariantMap properties;
    properties.insert("description", QString::fromUtf8("Transports de la région de Lausanne"));
    Company tl (QVariantMap(), "tl", QString(), properties);
    d->companies.append(tl);

    d->nam = new QNetworkAccessManager(this);
}

TransportLausannois::~TransportLausannois()
{
}

QStringList TransportLausannois::capabilities() const
{
    QStringList capabilities;
    capabilities.append(CAPABILITY_LIST_COMPANIES);
    capabilities.append(CAPABILITY_LIST_LINES);
    capabilities.append(CAPABILITY_LIST_JOURNEYS);
    capabilities.append(CAPABILITY_LIST_STATIONS);
    return capabilities;
}

QList<Company> TransportLausannois::listCompanies() const
{
    Q_D(const TransportLausannois);
    return d->companies;
}

QList<Line> TransportLausannois::listLines(const Company &company) const
{
    Q_UNUSED(company)
    QFile file (":/data/lines.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        debug("tl-plugin") << "Failed to open lines.txt";
        return QList<Line>();
    }
    QTextStream fileTextStream(&file);
    fileTextStream.setCodec("utf-8");

    QList <Line> lines;

    while (!fileTextStream.atEnd()) {
        QString textLine = fileTextStream.readLine();
        QStringList splittedTextLine = textLine.split("::");

        Line line;
        QVariantMap properties;
        properties.insert("id", splittedTextLine.at(0));
        properties.insert("description", splittedTextLine.at(2));
        line.setDisambiguation(QVariantMap());
        line.setName(splittedTextLine.at(1));
        line.setProperties(properties);

        lines.append(line);
    }

    file.close();
    return lines;
}

QList<Journey> TransportLausannois::listJourneys(const Company &company, const Line &line) const
{
    Q_UNUSED(company)

    QFile file (QString(":/data/%1_directions.txt").arg(line.name()));
    if (!file.open(QIODevice::ReadOnly)) {
        debug("tl-plugin") << "Failed to open" << file.fileName().constData();
        return QList<Journey>();
    }
    QTextStream fileTextStream(&file);
    fileTextStream.setCodec("utf-8");

    QList <Journey> journeys;

    while (!fileTextStream.atEnd()) {
        QString textLine = fileTextStream.readLine();
        QStringList splittedTextLine = textLine.split("::");

        QString journeyId = splittedTextLine.at(0);
        QString journeyFrom = splittedTextLine.at(1);
        QString journeyTo = splittedTextLine.at(2);
        QString journeyDescription = splittedTextLine.at(3);
        QString journeyAdditionalInfo = "";
        QString journeyVia = QString();

        int viaIndex = journeyDescription.indexOf("via");
        if (viaIndex != -1) {
            journeyAdditionalInfo = journeyDescription.right(journeyDescription.size() - viaIndex);
            journeyVia = journeyDescription.right(journeyDescription.size() - viaIndex - 4);
        }
        QString journeyName = QString("%1 > %2 %3").arg(journeyFrom, journeyTo,
                                                        journeyAdditionalInfo);

        Journey journey;
        QVariantMap properties;
        properties.insert("id", journeyId);
        properties.insert("internalDescription", journeyDescription);
        if (!journeyVia.isNull()) {
            properties.insert("via", journeyVia);
        }
        journey.setDisambiguation(QVariantMap());
        journey.setName(journeyName);
        journey.setProperties(properties);

        journeys.append(journey);
    }

    file.close();
    return journeys;
}

QList<Station> TransportLausannois::listStations(const Company &company, const Line &line,
                                             const Journey &journey) const
{
    Q_UNUSED(company)
    Q_UNUSED(line)

    QFile file (QString(":/data/%1.txt").arg(journey.properties().value("id").toString()));
    if (!file.open(QIODevice::ReadOnly)) {
        debug("tl-plugin") << "Failed to open" << file.fileName().constData();
        return QList<Station>();
    }
    QTextStream fileTextStream(&file);
    fileTextStream.setCodec("utf-8");

    QList <Station> stations;

    while (!fileTextStream.atEnd()) {
        QString textLine = fileTextStream.readLine();
        QStringList splittedTextLine = textLine.split("::");

        Station station;
        QVariantMap properties;
        properties.insert("id", splittedTextLine.at(0));
        properties.insert("city", splittedTextLine.at(1));
        station.setDisambiguation(QVariantMap());
        station.setName(splittedTextLine.at(2));
        station.setProperties(properties);

        stations.append(station);
    }

    file.close();
    return stations;
}

void TransportLausannois::getWaitingTime(const Company &company, const Line &line,
                                         const Journey &journey, const Station &station)
{
    Q_D(TransportLausannois);
    QString url = "http://m.t-l.ch/ressources/horaire.php?level=4&id=%1&line=%2";
    url = url.arg(station.properties().value("id").toString(),
                  line.properties().value("id").toString());

    d->companyForWaitTime = company;
    d->lineForWaitTime = line;
    d->journeyForWaitTime = journey;
    d->stationForWaitTime = station;

    QNetworkRequest request = QNetworkRequest(QUrl(url));
    QNetworkReply *reply = d->nam->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(slotFinished()));
}

}

}

#include "moc_transportlausannois.cpp"

Q_EXPORT_PLUGIN2(tl, PublicTransportation::Provider::TransportLausannois)

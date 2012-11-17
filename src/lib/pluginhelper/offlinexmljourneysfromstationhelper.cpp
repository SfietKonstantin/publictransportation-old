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

/**
 * @file offlinexmljourneysfromstationhelper.cpp
 * @short Implementation of PublicTransportation::PluginHelper::OfflineXmlJourneysFromStationHelper
 */


#include "offlinexmljourneysfromstationhelper.h"

#include <QtCore/QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomAttr>

#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"
#include "common/infojourneys.h"
#include "debug.h"

namespace PublicTransportation
{

namespace PluginHelper
{

QList<InfoJourneys> OfflineXmlJourneysFromStationHelper::journeysFromStation(const QString &xmlFile,
                                                                             const Station &station,
                                                                  const QVariantMap &disambiguation,
                                                                             const Company &company,
                                                                              bool *ok,
                                                                              QString *errorMessage)
{
    QFile file (xmlFile);
    if (!file.open(QIODevice::ReadOnly)) {
        debug("helper-xmljourneyfromstation") << "Failed to read"
                                              << xmlFile.toAscii().constData();
        if (ok) {
            *ok = false;
        }
        if (errorMessage) {
            *errorMessage = QString("Failed to read %1").arg(xmlFile);
        }
        return QList<InfoJourneys>();
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
        debug("helper-xmljourneyfromstation") << "Failed to find station"
                                              << station.name().toAscii().constData();
        if (ok) {
            *ok = false;
        }
        if (errorMessage) {
            *errorMessage = QString("Failed to find station %1").arg(station.name());
        }
        return QList<InfoJourneys>();
    }

    QList<InfoJourneys> infoJourneysList;
    currentElement = foundElement.firstChildElement();
    while (!currentElement.isNull()) {
        InfoJourneys infoJourneys;

        QVariantMap properties;
        QDomNamedNodeMap attributes = currentElement.attributes();
        for (int i = 0; i < attributes.count(); i++) {
            QDomNode attributeNode = attributes.item(i);
            if (attributeNode.isAttr()) {
                QDomAttr attribute = attributeNode.toAttr();
                if (attribute.name() != "name") {
                    properties.insert(attribute.name(), attribute.value());
                }
            }
        }

        Line line (disambiguation, currentElement.attribute("name"), properties);

        infoJourneys.setCompany(company);
        infoJourneys.setLine(line);

        QList<QPair <Journey, Station> > journeysStations;
        QDomElement journeyElement = currentElement.firstChildElement();
        while (!journeyElement.isNull()) {
            QVariantMap journeyProperties;
            QVariantMap stationProperties = station.properties();
            QDomNamedNodeMap attributes = journeyElement.attributes();
            for (int i = 0; i < attributes.count(); i++) {
                QDomNode attributeNode = attributes.item(i);
                if (attributeNode.isAttr()) {
                    QDomAttr attribute = attributeNode.toAttr();
                    QString attributeName = attribute.name();
                    if (attributeName != "name") {
                        if (!attributeName.startsWith("station")) {
                            journeyProperties.insert(attribute.name(), attribute.value());
                        } else {
                            attributeName = attributeName.right(attributeName.size() - 7);
                            attributeName[0] = attributeName.at(0).toLower();
                            stationProperties.insert(attributeName, attribute.value());
                        }
                    }
                }
            }


            Journey journey (disambiguation, journeyElement.attribute("name"), journeyProperties);
            Station preciseStation;
            preciseStation.setName(station.name());
            preciseStation.setDisambiguation(station.disambiguation());
            preciseStation.setProperties(stationProperties);
            journeysStations.append(QPair<Journey, Station>(journey, preciseStation));

            journeyElement = journeyElement.nextSiblingElement();
        }

        infoJourneys.setJourneysAndStations(journeysStations);
        infoJourneysList.append(infoJourneys);

        currentElement = currentElement.nextSiblingElement();
    }

    if (ok) {
        *ok = true;
    }
    if (errorMessage) {
        *errorMessage = QString();
    }
    return infoJourneysList;
}

}

}

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

#include "transpolejourneysfromstationhelper.h"

#include <QtCore/QRegExp>
#include <QtCore/QVariantMap>

#include "common/company.h"
#include "common/infojourneys.h"

#include "languagehelper.h"

using namespace PublicTransportation::PluginHelper;

namespace PublicTransportation
{

namespace Provider
{

TranspoleJourneysFromStationHelper
   ::TranspoleJourneysFromStationHelper(QNetworkAccessManager *networkAccessManager,
                                        QObject *parent):
    AbstractJourneysFromStationHelper(networkAccessManager, parent)
{
}

QList<InfoJourneys> TranspoleJourneysFromStationHelper::processData(QIODevice *input,
                                                                    bool *ok, QString *errorMessage)
{
    QRegExp idRegExp ("<a href=\"#\" id=\"([^\"]*)\"");
    QRegExp lineRegExp ("<span class=\"linePicto\"><span style=\"display:none\">([^-]*)");
    QRegExp lineNameRegExp ("<span class=\"lineName\">([^<]*)</span>");

    QVariantMap disambiguation;
    disambiguation.insert("id", "org.SfietKonstantin.publictransportation.transpole");

    QString currentId;
    QString currentLine;

    QList<InfoJourneys> infoJourneysList;

    Company company;
    company.setDisambiguation(disambiguation);
    company.setName("Transpole");

    while (!input->atEnd()) {
        QString data = input->readLine();
        if (currentId.isEmpty()) {
            if (data.indexOf(idRegExp) != -1) {
                currentId = idRegExp.cap(1);
            }
        } else if (currentLine.isEmpty()) {
            if (data.indexOf(lineRegExp) != -1) {
                currentLine = lineRegExp.cap(1).trimmed();
            }
        } else {
            if (data.indexOf(lineNameRegExp) != -1) {
                bool existing = false;
                InfoJourneys infoJourneysToAdd;
                QPair<Journey, Station> journeyAndStation;

                foreach (InfoJourneys infoJourneys, infoJourneysList) {
                    if (infoJourneys.line().name() == currentLine) {
                        infoJourneysToAdd = infoJourneys;
                        existing = true;
                    }
                }

                Line line;
                line.setDisambiguation(disambiguation);
                line.setName(currentLine);

                if (!existing) {
                    infoJourneysToAdd.setCompany(company);
                    infoJourneysToAdd.setLine(line);
                }

                Journey journey;
                journey.setDisambiguation(disambiguation);
                journey.setName(LanguageHelper::unstripHtmlAccents(lineNameRegExp.cap(1)));
                journeyAndStation.first = journey;

                Station newStation;
                newStation.setDisambiguation(disambiguation);
                newStation.setName(station().name());
                QVariantMap properties;
                properties.insert("id", currentId);
                properties.insert("code", station().properties().value("code"));
                newStation.setProperties(properties);
                journeyAndStation.second = newStation;

                QList<QPair<Journey, Station> > journeysAndStations;

                if (existing) {
                    journeysAndStations = infoJourneysToAdd.journeysAndStations();
                }
                journeysAndStations.append(journeyAndStation);
                infoJourneysToAdd.setJourneysAndStations(journeysAndStations);

                if (!existing) {
                    infoJourneysList.append(infoJourneysToAdd);
                }

                currentId = QString();
                currentLine = QString();
            }
        }
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

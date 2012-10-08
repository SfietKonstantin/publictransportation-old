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
 * @file abstractbackendwrapper.cpp
 * @short Implementation of PublicTransportation::AbstractBackendWrapper
 */

#include "abstractbackendwrapper.h"
#include "abstractbackendwrapper_p.h"

#include "debug.h"
#include "common/commonhelper.h"

namespace PublicTransportation
{

AbstractBackendWrapper::AbstractBackendWrapper(const QString &identifier, const QString &executable,
                                               const QMap<QString, QString> &arguments,
                                               QObject *parent):
    QObject(parent), d_ptr(new AbstractBackendWrapperPrivate())
{
    Q_D(AbstractBackendWrapper);
    d->identifier = identifier;
    d->executable = executable;
    d->arguments = arguments;
}

AbstractBackendWrapper::AbstractBackendWrapper(AbstractBackendWrapperPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{

}

AbstractBackendWrapper::~AbstractBackendWrapper()
{
}

QString AbstractBackendWrapper::identifier() const
{
    Q_D(const AbstractBackendWrapper);
    return d->identifier;
}

AbstractBackendWrapper::Status AbstractBackendWrapper::status() const
{
    Q_D(const AbstractBackendWrapper);
    return d->status;
}

QString AbstractBackendWrapper::lastError() const
{
    Q_D(const AbstractBackendWrapper);
    return d->lastError;
}

QStringList AbstractBackendWrapper::capabilities() const
{
    Q_D(const AbstractBackendWrapper);
    return d->capabilities;
}

QList<Company> AbstractBackendWrapper::companies() const
{
    Q_D(const AbstractBackendWrapper);
    return d->companies;
}

QList<Line> AbstractBackendWrapper::lines(const Company &company) const
{
    Q_D(const AbstractBackendWrapper);
    Company sharedCompany = sharedCopy<Company>(company, d->companies);
    if (sharedCompany.isNull()) {
        return QList<Line>();
    }

    return sharedCompany.lines();
}

QList<Journey> AbstractBackendWrapper::journeys(const Company &company, const Line &line) const
{
    Q_D(const AbstractBackendWrapper);
    Company sharedCompany = sharedCopy<Company>(company, d->companies);
    if (sharedCompany.isNull()) {
        return QList<Journey>();
    }

    Line sharedLine = sharedCopy<Line>(line, sharedCompany.lines());
    if (sharedLine.isNull()) {
        return QList<Journey>();
    }

    return sharedLine.journeys();
}

QList<Station> AbstractBackendWrapper::stations(const Company &company, const Line &line,
                                                const Journey &journey) const
{
    Q_D(const AbstractBackendWrapper);
    Company sharedCompany = sharedCopy<Company>(company, d->companies);
    if (sharedCompany.isNull()) {
        return QList<Station>();
    }

    Line sharedLine = sharedCopy<Line>(line, sharedCompany.lines());
    if (sharedLine.isNull()) {
        return QList<Station>();
    }

    Journey sharedJourney = sharedCopy<Journey>(journey, sharedLine.journeys());
    if (sharedJourney.isNull()) {
        return QList<Station>();
    }

    return sharedJourney.stations();
}

void AbstractBackendWrapper::waitForStopped()
{
}

QString AbstractBackendWrapper::executable() const
{
    Q_D(const AbstractBackendWrapper);
    return d->executable;
}

QMap<QString, QString> AbstractBackendWrapper::arguments() const
{
    Q_D(const AbstractBackendWrapper);
    return d->arguments;
}

void AbstractBackendWrapper::setStatus(Status status)
{
    Q_D(AbstractBackendWrapper);
    if (d->status != status) {
        d->status = status;
        emit statusChanged();

        debug("abs-backend-wrapper") << "Status changed to" << d->status;
    }
}

void AbstractBackendWrapper::setLastError(const QString &lastError)
{
    Q_D(AbstractBackendWrapper);
    d->lastError = lastError;
    debug("abs-backend-wrapper") << "Last error:" << lastError;
}

void AbstractBackendWrapper::setCapabilities(const QStringList &capabilities)
{
    Q_D(AbstractBackendWrapper);
    if (d->capabilities != capabilities) {
        d->capabilities = capabilities;
        emit capabilitiesChanged();

        debug("abs-backend-wrapper") << "Capabilities changed";
    }
}

void AbstractBackendWrapper::setCompanies(const QList<Company> &companies)
{
    Q_D(AbstractBackendWrapper);
    QList<Company> companiesToAdd;

    foreach (Company company, companies) {
        if (!d->companies.contains(company)) {
            companiesToAdd.append(company);
        }
    }

    if (companiesToAdd.isEmpty()) {
        return;
    }

    foreach (Company company, companiesToAdd) {
        d->companies.append(company);
    }
    emit companiesChanged();

    debug("abs-backend-wrapper") << "Companies changed";
}

void AbstractBackendWrapper::setLines(const Company &company, const QList<Line> &lines)
{
    Q_D(AbstractBackendWrapper);

    Company sharedCompany = sharedCopy<Company>(company, d->companies);
    if (sharedCompany.isNull()) {
        warning("abs-backend-wrapper") << "Lines are set for an unknown company:" << company.name();
        return;
    }

    QList<Line> companyLines = sharedCompany.lines();
    QList<Line> linesToAdd;

    foreach (Line line, lines) {
        if (!companyLines.contains(line)) {
            linesToAdd.append(line);
        }
    }

    if (linesToAdd.isEmpty()) {
        return;
    }

    foreach (Line line, linesToAdd) {
        sharedCompany.addLine(line);
    }

    emit linesChanged(sharedCompany);
    debug("abs-backend-wrapper") << "Lines changed for company" << sharedCompany.name();
}

void AbstractBackendWrapper::setJourneys(const Company &company, const Line &line,
                                         const QList<Journey> &journeys)
{
    Q_D(AbstractBackendWrapper);

    Company sharedCompany = sharedCopy<Company>(company, d->companies);
    if (sharedCompany.isNull()) {
        warning("abs-backend-wrapper") << "Journeys are set for an unknown company:"
                                       << company.name();
        return;
    }

    Line sharedLine = sharedCopy<Line>(line, sharedCompany.lines());
    if (sharedLine.isNull()) {
        warning("abs-backend-wrapper") << "Journeys are set for an unknown line:" << line.name()
                                       << "(and for company " << company.name() << ")";
        return;
    }

    QList<Journey> lineJourneys = sharedLine.journeys();
    QList<Journey> journeysToAdd;

    foreach (Journey journey, journeys) {
        if (!lineJourneys.contains(journey)) {
            journeysToAdd.append(journey);
        }
    }

    if (journeysToAdd.isEmpty()) {
        return;
    }

    foreach (Journey journey, journeysToAdd) {
        sharedLine.addJourney(journey);
    }

    emit journeysChanged(sharedCompany, sharedLine);
    debug("abs-backend-wrapper") << "Journeys changed for company" << sharedCompany.name()
                                 << "and line" << sharedLine.name();
}

void AbstractBackendWrapper::setStations(const Company &company, const Line &line,
                                         const Journey &journey, const QList<Station> &stations)
{
    Q_D(AbstractBackendWrapper);

    Company sharedCompany = sharedCopy<Company>(company, d->companies);
    if (sharedCompany.isNull()) {
        warning("abs-backend-wrapper") << "Stations are set for an unknown company:"
                                       << company.name();
        return;
    }

    Line sharedLine = sharedCopy<Line>(line, sharedCompany.lines());
    if (sharedLine.isNull()) {
        warning("abs-backend-wrapper") << "Stations are set for an unknown line:" << line.name()
                                       << "(and for company " << company.name() << ")";
        return;
    }

    Journey sharedJourney = sharedCopy<Journey>(journey, sharedLine.journeys());
    if (sharedJourney.isNull()) {
        warning("abs-backend-wrapper") << "Stations are set for an unknown journey:"
                                       << journey.name() << "(and for company "
                                       << company.name() << "and line" << line.name() << ")";
        return;
    }

    QList<Station> journeyStations = sharedJourney.stations();
    QList<Station> stationsToAdd;

    foreach (Station station, stations) {
        if (!journeyStations.contains(station)) {
            stationsToAdd.append(station);
        }
    }

    if (stationsToAdd.isEmpty()) {
        return;
    }

    foreach (Station station, stationsToAdd) {
        sharedJourney.addStation(station);
    }

    emit stationsChanged(sharedCompany, sharedLine, sharedJourney);
    debug("abs-backend-wrapper") << "Stations changed for company" << sharedCompany.name()
                                 << ", line" << sharedLine.name()
                                 << "and journey" << sharedJourney.name();
}

}

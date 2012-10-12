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

#ifndef PUBLICTRANSPORTATION_INFOJOURNEYS_H
#define PUBLICTRANSPORTATION_INFOJOURNEYS_H

#include "publictransportation_global.h"

#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QExplicitlySharedDataPointer>

#include "company.h"
#include "line.h"
#include "journey.h"
#include "station.h"

namespace PublicTransportation
{

class InfoJourneysPrivate: public QSharedData
{
public:
    Company company;
    Line line;
    QList<QPair<Journey, Station> > journeysStations;
};

class PUBLICTRANSPORTATION_EXPORT InfoJourneys
{
public:
    explicit InfoJourneys();
    explicit InfoJourneys(const Company &company, const Line &line,
                          const QList<QPair<Journey, Station> > &journeys);
    /**
     * @brief Copy constructor
     * @param other other line-journeys object.
     */
    InfoJourneys(const InfoJourneys &other);
    /**
     * @brief Destructor
     */
    virtual ~InfoJourneys();
    bool operator==(const InfoJourneys &other) const;
    /**
     * @brief If the line-journeys object is null
     * @return if the line-journeys object is null.
     */
    bool isNull() const;
    Company company() const;
    void setCompany(const Company &company);
    Line line() const;
    void setLine(const Line &line);
    QList<QPair<Journey, Station> > journeysAndStations() const;
    void setJourneysAndStations(const QList<QPair<Journey, Station> > &journeysStations);
protected:
    QExplicitlySharedDataPointer<InfoJourneysPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(InfoJourneys)
};

}

Q_DECLARE_METATYPE(PublicTransportation::InfoJourneys)
Q_DECLARE_METATYPE(QList<PublicTransportation::InfoJourneys>)

#endif // PUBLICTRANSPORTATION_INFOJOURNEYS_H

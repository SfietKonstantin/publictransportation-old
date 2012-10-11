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

#ifndef PUBLICTRANSPORTATION_LINEJOURNEYS_H
#define PUBLICTRANSPORTATION_LINEJOURNEYS_H

#include "publictransportation_global.h"

#include <QtCore/QList>
#include <QtCore/QExplicitlySharedDataPointer>

#include "line.h"
#include "journey.h"

namespace PublicTransportation
{

class LineJourneysPrivate: public QSharedData
{
public:
    Line line;
    QList<Journey> journeys;
};

class PUBLICTRANSPORTATION_EXPORT LineJourneys
{
public:
    explicit LineJourneys();
    explicit LineJourneys(const Line &line, const QList<Journey> &journeys);
    /**
     * @brief Copy constructor
     * @param other other line-journeys object.
     */
    LineJourneys(const LineJourneys &other);
    /**
     * @brief Destructor
     */
    virtual ~LineJourneys();
    bool operator==(const LineJourneys &other) const;
    /**
     * @brief If the line-journeys object is null
     * @return if the line-journeys object is null.
     */
    bool isNull() const;
    Line line() const;
    void setLine(const Line &line);
    QList<Journey> journeys() const;
    void setJourneys(const QList<Journey> &journeys);
protected:
    QExplicitlySharedDataPointer<LineJourneysPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(LineJourneys)
};

}

Q_DECLARE_METATYPE(PublicTransportation::LineJourneys)
Q_DECLARE_METATYPE(QList<PublicTransportation::LineJourneys>)

#endif // PUBLICTRANSPORTATION_LINEJOURNEYS_H

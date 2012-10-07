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

#ifndef PUBLICTRANSPORTATION_PROVIDER_TLLIST_H
#define PUBLICTRANSPORTATION_PROVIDER_TLLIST_H

#include <QtCore/QList>
#include "common/company.h"
#include "common/line.h"
#include "common/journey.h"
#include "common/station.h"

namespace PublicTransportation
{

namespace Provider
{

/**
 * @short List of all TL lines, journeys and stations
 *
 * This class provides, in an hard-coded way, all
 * informations related to TL, including all the
 * lines, the journeys, and stations.
 *
 * It provides methods that are compatible with provider
 * interface.
 *
 * Content of this class is generated with a script that
 * downloads information from t-l.ch.
 */
class TlList
{
public:
    /**
     * @short Lines
     * @return TL lines.
     */
    static QList<Line> lines();
    /**
     * @short Journeys
     * @param line line.
     * @return Journeys associated to the line.
     */
    static QList<Journey> journeys(const Line &line);
    /**
     * @short Journeys
     * @param line line.
     * @return Journeys associated to the line.
     */
    static QList<Station> stations(const Line &line, const Journey &journey);
};

}

}

#endif // PUBLICTRANSPORTATION_PROVIDER_TLLIST_H

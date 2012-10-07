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

#ifndef CAPABILITIESCONSTANTS_H
#define CAPABILITIESCONSTANTS_H

/**
 * @file capabilitiesconstants.h
 * @short Definition of constants that stands for backend capabilities
 */


/**
 * @short CAPABILITY_LIST_COMPANIES
 *
 * The backend is able to list companies.
 */
#define CAPABILITY_LIST_COMPANIES "list_companies"
/**
 * @short CAPABILITY_LIST_LINES
 *
 * The backend is able to list lines.
 */
#define CAPABILITY_LIST_LINES "list_lines"
/**
 * @short CAPABILITY_LIST_JOURNEYS
 *
 * The backend is able to list journeys.
 */
#define CAPABILITY_LIST_JOURNEYS "list_journeys"
/**
 * @short CAPABILITY_LIST_STATIONS
 *
 * The backend is able to list stations.
 */
#define CAPABILITY_LIST_STATIONS "list_stations"
/**
 * @short CAPABILITY_SEARCH_LINE
 *
 * The backend is able to search for lines.
 */
#define CAPABILITY_SEARCH_LINE "search_line"
/**
 * @short CAPABILITY_SEARCH_STATION
 *
 * The backend is able to search for stations.
 */
#define CAPABILITY_SEARCH_STATION "search_station"
/**
 * @short CAPABILITY_REAL_TIME
 *
 * The backend is able to get realtime information.
 */
#define CAPABILITY_REAL_TIME "real_time"
/**
 * @short CAPABILITY_TIMETABLE
 *
 * The backend is able to get timetables.
 */
#define CAPABILITY_TIMETABLE "timetable"

#endif // CAPABILITIESCONSTANTS_H

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
 * @short SUGGEST_STATIONS
 *
 * The backend is able suggest stations.
 */
#define SUGGEST_STATIONS "suggest_stations"
/**
 * @short JOURNEYS_FROM_STATION
 *
 * The backend is able to get journeys from a station.
 */
#define JOURNEYS_FROM_STATION "journeys_from_station"
/**
 * @short JOURNEYS_WAITING_TIMES_FROM_STATION
 *
 * The backend is able to get journeys with waiting time from a station.
 */
#define JOURNEYS_WAITING_TIMES_FROM_STATION "journeys_waiting_times_from_station"
/**
 * @short WAITING_TIME
 *
 * The backend is able to get waiting time.
 */
#define WAITING_TIME "waiting_time"
/**
 * @short STATIONS_FROM_JOURNEY
 *
 * The backend is able to list the stations in a journey.
 */
#define STATIONS_FROM_JOURNEY "stations_from_journey"

#endif // CAPABILITIESCONSTANTS_H

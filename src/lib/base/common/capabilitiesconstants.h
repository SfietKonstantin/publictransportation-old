/*
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * The names of its contributors may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef CAPABILITIESCONSTANTS_H
#define CAPABILITIESCONSTANTS_H

/**
 * @file capabilitiesconstants.h
 * @short Definition of constants that stands for backend capabilities
 */


/**
 * @short CAPABILITY_SUGGEST_STATIONS
 *
 * The backend is able suggest stations.
 */
#define CAPABILITY_SUGGEST_STATIONS "capability:suggest_stations"
/**
 * @short JOURNEYS_FROM_STATION
 *
 * The backend is able to get journeys from a station.
 */
//#define JOURNEYS_FROM_STATION "journeys_from_station"
/**
 * @short JOURNEYS_WAITING_TIMES_FROM_STATION
 *
 * The backend is able to get journeys with waiting time from a station.
 */
//#define JOURNEYS_WAITING_TIMES_FROM_STATION "journeys_waiting_times_from_station"
/**
 * @short WAITING_TIME
 *
 * The backend is able to get waiting time.
 */
//#define WAITING_TIME "waiting_time"
/**
 * @short STATIONS_FROM_JOURNEY
 *
 * The backend is able to list the stations in a journey.
 */
//#define STATIONS_FROM_JOURNEY "stations_from_journey"

#endif // CAPABILITIESCONSTANTS_H

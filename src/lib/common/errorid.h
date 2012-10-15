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

#ifndef ERRORID_H
#define ERRORID_H

/**
 * @file errorid.h
 * @short Definition of constants that describes error categories
 */

/**
 * @short INVALID_REQUEST_TYPE
 *
 * The error is sent when the backend wrapper receive
 * a response from the backend that do not correspond
 * to the type of data that were requested.
 *
 * This error should help for debugging backends, and
 * is not displayed in a GUI.
 */
#define INVALID_REQUEST_TYPE "invalid_request_type"
/**
 * @short NOT_IMPLEMENTED
 *
 * The error is sent when the capability is not implemented
 * in the backend, but still requested.
 *
 * This error should help for debugging backends, and
 * is not displayed in a GUI.
 */
#define NOT_IMPLEMENTED "not_implemented"
/**
 * @short BACKEND_WARNING
 *
 * The error is sent because something happened in the backend
 * side, because of some external reasons. Reasons can be lack
 * of internet connection, server timeout, or invalid data retrieved
 * from a server.
 *
 * This error is displayed in a GUI, in order to help the user
 * to understand why there is a failure in an operation.
 */
#define BACKEND_WARNING "backend_warning"
/**
 * @short OTHER_ERROR
 *
 * Other error happened.
 *
 * This error code should not be set, unless there is a specific
 * reason. It is not displayed in a GUI.
 */
#define OTHER_ERROR "other_error"

#endif // ERRORID_H

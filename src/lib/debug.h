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

#ifndef PUBLICTRANSPORTATION_DEBUG_H
#define PUBLICTRANSPORTATION_DEBUG_H

/**
 * @internal
 * @file debug.h
 * @short Debug methods
 */

#include <QtCore/QDebug>

namespace PublicTransportation
{

/**
 * @internal
 * @brief Debug
 *
 * This method outputs a debug trace, that
 * is prefixed with the name of the component to debug.
 *
 * @param prefix prefix.
 * @return a QDebug object used for debugging.
 */
inline QDebug debug(const QByteArray &prefix)
{
    QByteArray truePrefix = "  [" + prefix + "]";
    return (QDebug(QtDebugMsg) << truePrefix.constData());
}

/**
 * @internal
 * @brief Warning
 *
 * This method outputs a warning, that
 * is prefixed with the name of the component to debug.
 *
 * @param prefix prefix.
 * @return a QDebug object used for warning.
 */
inline QDebug warning(const QByteArray &prefix)
{
    QByteArray truePrefix = "W [" + prefix + "]";
    return (QDebug(QtWarningMsg) << truePrefix.constData());
}

/**
 * @internal
 * @brief Fatal
 *
 * This method outputs a fatal message, that
 * is prefixed with the name of the component to debug.
 *
 * Most of the time, a fatal message interrupts the
 * program.
 *
 * @param prefix prefix.
 * @return a QDebug object used for debugging.
 */
inline QDebug fatal(const QByteArray &prefix)
{
    QByteArray truePrefix = "! [" + prefix + "]";
    return (QDebug(QtFatalMsg) << truePrefix.constData());
}

}

#endif // PUBLICTRANSPORTATION_DEBUG_H

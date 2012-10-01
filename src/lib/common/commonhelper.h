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

#ifndef PUBLICTRANSPORTATION_COMMONHELPER_H
#define PUBLICTRANSPORTATION_COMMONHELPER_H

#include <QtCore/QList>

namespace PublicTransportation
{

template<class T> inline T sharedCopy(const T &entry, const QList<T> list)
{
    if (list.contains(entry)) {
        return list[list.indexOf(entry)];
    } else {
        return T();
    }
}

}

#endif // PUBLICTRANSPORTATION_COMMONHELPER_H
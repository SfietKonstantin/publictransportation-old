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

#include "signalreceiver.h"

using namespace PublicTransportation;

SignalReceiver::SignalReceiver(QObject *parent) :
    QObject(parent)
{
}

QList<Station> SignalReceiver::suggestedStations() const
{
    return m_suggestedStations;
}

void SignalReceiver::saveSuggestedStations(int request, const QList<Station> &suggestedStations)
{
    Q_UNUSED(request)
    m_suggestedStations = suggestedStations;
}

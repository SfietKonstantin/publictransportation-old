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

#ifndef PUBLICTRANSPORTATION_PROVIDER_TRANSPOLESUGGESTEDSTATIONSHELPER_H
#define PUBLICTRANSPORTATION_PROVIDER_TRANSPOLESUGGESTEDSTATIONSHELPER_H

#include "abstractsuggestedstationshelper.h"

namespace PublicTransportation
{

namespace Provider
{

class TranspoleSuggestedStationsHelper: public PluginHelper::AbstractSuggestedStationsHelper
{
public:
    explicit TranspoleSuggestedStationsHelper(QNetworkAccessManager *networkAccessManager,
                                              QObject *parent = 0);
protected:
    virtual QList<Station> processData(QIODevice *input, bool *ok, QString *errorMessage);
};

}

}

#endif // PUBLICTRANSPORTATION_PROVIDER_TRANSPOLESUGGESTEDSTATIONSHELPER_H

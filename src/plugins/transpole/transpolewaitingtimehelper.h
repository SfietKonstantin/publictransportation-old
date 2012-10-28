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

#ifndef PUBLICTRANSPORTATION_PROVIDER_TRANSPOLEWAITINGTIMEHELPER_H
#define PUBLICTRANSPORTATION_PROVIDER_TRANSPOLEWAITINGTIMEHELPER_H

#include "abstractwaitingtimehelper.h"

namespace PublicTransportation
{

namespace Provider
{

class TranspoleWaitingTimeHelperPrivate;
class TranspoleWaitingTimeHelper: public PluginHelper::AbstractWaitingTimeHelper
{
public:
    explicit TranspoleWaitingTimeHelper(QNetworkAccessManager *networkAccessManager,
                                        QObject *parent = 0);
    void checkRan(const Company &companyToCheck, const Line &lineToCheck,
                  const Journey &journeyToCheck, const Station &stationToCheck);
    void load(const QString &request);
protected:
    virtual QList<JourneyAndWaitingTime> processData(QIODevice *input, bool *ok,
                                                     QString *errorMessage);
private:
    Q_DECLARE_PRIVATE(TranspoleWaitingTimeHelper)
};

}

}

#endif // PUBLICTRANSPORTATION_PROVIDER_TRANSPOLEWAITINGTIMEHELPER_H

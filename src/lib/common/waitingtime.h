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

#ifndef PUBLICTRANSPORTATION_WAITTIME_H
#define PUBLICTRANSPORTATION_WAITTIME_H

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QString>
#include <QtCore/QVariantMap>

namespace PublicTransportation
{

class WaitingTimePrivate: public QSharedData
{
public:
    /**
     * @internal
     * @brief Waiting time
     */
    int waitingTime;
    /**
     * @internal
     * @brief Parameters
     */
    QVariantMap properties;
};

class WaitingTime
{
public:
    /**
     * @brief Default constructor
     */
    explicit WaitingTime();
    /**
     * @brief Copy constructor
     * @param other other wait time.
     */
    WaitingTime(const WaitingTime &other);
    virtual ~WaitingTime();
    /**
     * @brief If the waiting time is null
     * @return if the waiting time is null.
     */
    bool isNull() const;
    /**
     * @brief Waiting time
     * @return waiting time.
     */
    int waitingTime() const;
    /**
     * @brief Set waiting time
     * @param waitingTime waiting time to set.
     */
    void setWaitingTime(int waitingTime);
    /**
     * @brief Properties
     * @return properties.
     */
    QVariantMap properties() const;
    /**
     * @brief Set properties
     * @param properties properties to set.
     */
    void setProperties(const QVariantMap &properties);
protected:
    /**
     * @brief D-pointer based constructor
     * @param dd d-pointer.
     */
    WaitingTime(WaitingTimePrivate &dd);
    /**
     * @brief D-pointer
     */
    QExplicitlySharedDataPointer<WaitingTimePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(WaitingTime)
};

}

Q_DECLARE_METATYPE(PublicTransportation::WaitingTime)
Q_DECLARE_METATYPE(QList<PublicTransportation::WaitingTime>)

#endif // PUBLICTRANSPORTATION_WAITTIME_H

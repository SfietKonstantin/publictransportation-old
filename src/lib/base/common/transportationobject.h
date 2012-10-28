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

#ifndef PUBLICTRANSPORTATION_TRANSPORTATIONOBJECT_H
#define PUBLICTRANSPORTATION_TRANSPORTATIONOBJECT_H

/**
 * @file transportationobject.h
 * @short Definition of PublicTransportation::TransportationObject
 */

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QString>
#include <QtCore/QVariantMap>

namespace PublicTransportation
{

/**
 * @internal
 * @brief Private class for PublicTransportation::TransportationObject
 *
 * This class is used to store the explicitly shared
 * data for PublicTransportation::TransportationObject.
 */
struct TransportationObjectPrivate: public QSharedData
{
    /**
     * @internal
     * @brief Disambiguation
     */
    QVariantMap disambiguation;
    /**
     * @internal
     * @brief Name
     */
    QString name;
    /**
     * @internal
     * @brief Properties
     */
    QVariantMap properties;
};

/**
 * @brief Base class for entities related to public transportation
 *
 * This class is a generic storage class that is used
 * to store informations about entities that are used in
 * public transportation.
 *
 * Common properties of any public transportation entity
 * are the following
 * - name()
 * - disambiguation()
 * - properties()
 *
 * and can be set using
 * - setName()
 * - setDisambiguation()
 * - setProperties()
 *
 * The name is a human-readable name that should be able to
 * identify (but not uniquely) the name of the public
 * transportation entity. It can be identified furthermore
 * using the disambiguation properties. Finally the properties
 * property is used to set some properties that can be useful.
 * They are stored using a dictionnary.
 *
 * This class is an explicitely shared class, that means that
 * any copy of this class refers to the same instance, and
 * changing one copy will change all the others.
 *
 * This class also provides some conveinent operators, that
 * are used to compare one transportation entity to another.
 */
class TransportationObject
{
public:
    /**
     * @brief Default constructor
     */
    explicit TransportationObject();
    /**
     * @brief Copy constructor
     * @param other other transportation object.
     */
    TransportationObject(const TransportationObject &other);
    /**
     * @brief Destructor
     */
    virtual ~TransportationObject();
    /**
     * @brief Equality
     * @param other transportation object to compare to.
     * @return if the two transportation objects are equal.
     */
    bool operator==(const TransportationObject &other) const;
    /**
     * @brief Inequality
     * @param other transportation object to compare to.
     * @return if the two transportation objects are not equal.
     */
    bool operator!=(const TransportationObject &other) const;
    /**
     * @brief Inequality
     *
     * This method compares a transportation object to another
     * sorting them with name. This transportation object will
     * be lesser than another if the name is lesser in the
     * lexicographic order.
     *
     * @param other transportation object to compare to
     * @return if the transportation object is lesser that the other.
     */
    bool operator<(const TransportationObject &other) const;
    /**
     * @brief If the transportation object is null
     * @return if the transportation object is null.
     */
    bool isNull() const;
    /**
     * @brief Disambiguation
     * @return disambiguation.
     */
    QVariantMap disambiguation() const;
    /**
     * @brief Set disambiguation
     * @param disambiguation disambiguation to set.
     */
    void setDisambiguation(const QVariantMap &disambiguation);
    /**
     * @brief Name
     * @return name.
     */
    QString name() const;
    /**
     * @brief Set name
     * @param name name to set.
     */
    void setName(const QString &name);
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
    TransportationObject(TransportationObjectPrivate &dd);
    /**
     * @brief D-pointer
     */
    QExplicitlySharedDataPointer<TransportationObjectPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(TransportationObject)


};

}

#endif // PUBLICTRANSPORTATION_TRANSPORTATIONOBJECT_H

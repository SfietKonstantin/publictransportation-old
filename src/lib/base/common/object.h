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


#ifndef PT2_TRANSPORTATIONOBJECT_H
#define PT2_TRANSPORTATIONOBJECT_H

/**
 * @file object.h
 * @short Definition of PT2::Object
 */

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QString>
#include <QtCore/QVariantMap>

namespace PT2
{

/**
 * @internal
 * @brief Private class for PT2::Object
 *
 * This class is used to store the explicitly shared
 * data for PT2::TransportationObject.
 */
struct ObjectPrivate: public QSharedData
{
    /**
     * @internal
     * @brief Identifier
     */
    QString identifier;
    /**
       @internal
     * @brief Internal
     */
    QVariantMap internal;
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
 * pt2.
 *
 * All entities used in pt2 share the same properties
 * - identifier()
 * - internal()
 * - name()
 * - properties()
 *
 * than can be set using
 * - setIdentifier()
 * - setName()
 * - setInternal()
 * - setProperties()
 *
 * \e identifier is a string that is only used for
 * identification purpose. All public transportation entities
 * should define one that could identify them uniquely.
 * Comparing two public transportation is done using only that
 * string. If they are the same, the two entities are considered
 * the same.
 *
 * \e internal is a dictionnary of data, that contains internal
 * data that can be used by providers to transmit data. None of
 * the data in that dictionnary is used by the UI.
 *
 * \e name is a human-readable name that should be used to
 * identify the name of the entity. It is the one that will
 * displayed in the UI.
 *
 * \e properties is also a dictionnary. It contains additional
 * informations, that are used by the UI. Depending on the type
 * of the entity, various data, identified by predefined keys,
 * can be used.
 *
 * This class is an explicitely shared class, that means that
 * any copy of this class refers to the same instance, and
 * changing one copy will change all the others.
 *
 * This class also provides some conveinent operators, that
 * are used to compare one transportation entity to another.
 */
class Object
{
public:
    /**
     * @brief Default constructor
     */
    explicit Object();
    /**
     * @brief Copy constructor
     * @param other other transportation object.
     */
    Object(const Object &other);
    /**
     * @brief Destructor
     */
    virtual ~Object();
    /**
     * @brief Equality
     * @param other transportation object to compare to.
     * @return if the two transportation objects are equal.
     */
    bool operator==(const Object &other) const;
    /**
     * @brief Inequality
     * @param other transportation object to compare to.
     * @return if the two transportation objects are not equal.
     */
    bool operator!=(const Object &other) const;
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
    bool operator<(const Object &other) const;
    /**
     * @brief If the transportation object is null
     * @return if the transportation object is null.
     */
    bool isNull() const;
    /**
     * @brief Identifier
     * @return identifier.
     */
    QString identifier() const;
    /**
     * @brief Set identifier
     * @param identifier identifier to set.
     */
    void setIdentifier(const QString &identifier);
    /**
     * @brief Internal
     * @return internal.
     */
    QVariantMap internal() const;
    /**
     * @brief Set internal
     * @param internal internal to set.
     */
    void setInternal(const QVariantMap &internal);
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
    Object(ObjectPrivate &dd);
    /**
     * @brief D-pointer
     */
    QExplicitlySharedDataPointer<ObjectPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(Object)


};

}

#endif // PT2_TRANSPORTATIONOBJECT_H

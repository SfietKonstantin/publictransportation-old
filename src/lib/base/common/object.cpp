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


/**
 * @file object.cpp
 * @short Implementation of PT2::Object
 */

#include "object.h"

namespace PT2
{

Object::Object():
    d_ptr(new ObjectPrivate)
{
}

Object::Object(const Object &other):
    d_ptr(other.d_ptr)
{
}

Object::Object(ObjectPrivate &dd):
    d_ptr(&dd)
{
}

Object::~Object()
{
}

bool Object::operator==(const Object &other) const
{
    Q_D(const Object);
    return (d->identifier == other.identifier());
}

bool Object::operator!=(const Object &other) const
{
    return !(*this == other);
}

bool Object::operator<(const Object &other) const
{
    Q_D(const Object);
    return (d->name < other.name());
}

bool Object::isNull() const
{
    Q_D(const Object);
    return (d->identifier.isEmpty() && d->name.isNull() && d->properties.isEmpty());
}

QString Object::identifier() const
{
    Q_D(const Object);
    return d->identifier;
}

void Object::setIdentifier(const QString &identifier)
{
    Q_D(Object);
    d->identifier = identifier;
}

QVariantMap Object::internal() const
{
    Q_D(const Object);
    return d->internal;
}

void Object::setInternal(const QVariantMap &internal)
{
    Q_D(Object);
    d->internal = internal;
}

QString Object::name() const
{
    Q_D(const Object);
    return d->name;
}

void Object::setName(const QString &name)
{
    Q_D(Object);
    d->name = name;
}

QVariantMap Object::properties() const
{
    Q_D(const Object);
    return d->properties;
}

void Object::setProperties(const QVariantMap &properties)
{
    Q_D(Object);
    d->properties = properties;
}

}

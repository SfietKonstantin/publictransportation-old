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
 * @file backendinfo.cpp
 * @short Implementation of PT2::BackendInfo
 */

#include "backendinfo.h"
#include "desktopfileparser_p.h"

#include <QtCore/QLocale>
#include <QtCore/QSharedData>
#include <QtCore/QVariant>

namespace PT2
{

/**
 * @internal
 * @brief DESKTOP_FILE_NAME
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_NAME = "Name";
/**
 * @internal
 * @brief DESKTOP_FILE_COMMENT
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_COMMENT = "Comment";
/**
 * @internal
 * @brief DESKTOP_FILE_ICON
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_ICON = "Icon";
/**
 * @internal
 * @brief DESKTOP_FILE_TYPE
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_TYPE = "Type";
/**
 * @internal
 * @brief DESKTOP_FILE_TYPE_VALUE
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_TYPE_VALUE = "Service";
/**
 * @internal
 * @brief DESKTOP_FILE_EXEC
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_EXEC = "Exec";
/**
 * @internal
 * @brief DESKTOP_FILE_BACKENDINFO_ID
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_BACKENDINFO_ID = "X-PublicTransportation-BackendInfo-Id";
/**
 * @internal
 * @brief DESKTOP_FILE_BACKENDINFO_COUNTRY
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_BACKENDINFO_COUNTRY = "X-PublicTransportation-BackendInfo-Country";
/**
 * @internal
 * @brief DESKTOP_FILE_BACKENDINFO_CITIES
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_BACKENDINFO_CITIES = "X-PublicTransportation-BackendInfo-Cities";
/**
 * @internal
 * @brief DESKTOP_FILE_BACKENDINFO_AUTHOR
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_BACKENDINFO_AUTHOR = "X-PublicTransportation-BackendInfo-Author";
/**
 * @internal
 * @brief DESKTOP_FILE_BACKENDINFO_EMAIL
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_BACKENDINFO_EMAIL = "X-PublicTransportation-BackendInfo-Email";
/**
 * @internal
 * @brief DESKTOP_FILE_BACKENDINFO_WEBSITE
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_BACKENDINFO_WEBSITE = "X-PublicTransportation-BackendInfo-Website";
/**
 * @internal
 * @brief DESKTOP_FILE_BACKENDINFO_VERSION
 *
 * Used in PublicTransportation::BackendInfo.
 */
static const char *DESKTOP_FILE_BACKENDINFO_VERSION = "X-PublicTransportation-BackendInfo-Version";

BackendInfo::BackendInfo():
    d_ptr(new BackendInfoPrivate)
{
}

BackendInfo::BackendInfo(const QString &file):
    d_ptr(new BackendInfoPrivate)
{
    Q_D(BackendInfo);

    // Parse desktop file
    DesktopFileParser parser (file);
    parser.beginGroup("Desktop Entry");

    // Check if it is valid
    if (parser.value(DESKTOP_FILE_TYPE).toString() != DESKTOP_FILE_TYPE_VALUE) {
        return;
    }

    if (!parser.contains(DESKTOP_FILE_EXEC)) {
        return;
    }

    d->icon = parser.value(DESKTOP_FILE_ICON).toString();

    // Get the name and description
    QLocale locale;
    QString localeName = locale.name();
    QString languageName = localeName.split("_").first();
    QStringList languages;
    languages.append(localeName);
    languages.append(languageName);

    QString name;
    QString description;
    foreach (QString language, languages) {
        if (parser.contains(DESKTOP_FILE_NAME, language) && name.isEmpty()) {
            name = parser.value(DESKTOP_FILE_NAME, language).toString();
        }

        if (parser.contains(DESKTOP_FILE_COMMENT, language) && description.isEmpty()) {
            description = parser.value(DESKTOP_FILE_COMMENT, language).toString();
        }
    }
    if (name.isEmpty()) {
        name = parser.value(DESKTOP_FILE_NAME).toString();
    }
    if (description.isEmpty()) {
        description = parser.value(DESKTOP_FILE_COMMENT).toString();
    }
    d->name = name;
    d->description = description;
    d->country = parser.value(DESKTOP_FILE_BACKENDINFO_COUNTRY).toString();
    QVariant citiesVariant = parser.value(DESKTOP_FILE_BACKENDINFO_CITIES);
    if (citiesVariant.type() == QVariant::String) {
        d->cities.append(citiesVariant.toString());
    } else if (citiesVariant.type() == QVariant::StringList) {
        d->cities = citiesVariant.toStringList();
    }

    d->executable = parser.value(DESKTOP_FILE_EXEC).toString();
    d->identifier = parser.value(DESKTOP_FILE_BACKENDINFO_ID).toString();
    d->author = parser.value(DESKTOP_FILE_BACKENDINFO_AUTHOR).toString();
    d->email = parser.value(DESKTOP_FILE_BACKENDINFO_EMAIL).toString();
    d->website = parser.value(DESKTOP_FILE_BACKENDINFO_WEBSITE).toString();
    d->version = parser.value(DESKTOP_FILE_BACKENDINFO_VERSION).toString();
}

BackendInfo::BackendInfo(const BackendInfo &other):
    d_ptr(other.d_ptr)
{
}

BackendInfo::~BackendInfo()
{
}

bool BackendInfo::isValid() const
{
    Q_D(const BackendInfo);
    return !d->executable.isEmpty() && !d->identifier.isEmpty();
}

QString BackendInfo::icon() const
{
    Q_D(const BackendInfo);
    return d->icon;
}

QString BackendInfo::name() const
{
    Q_D(const BackendInfo);
    return d->name;
}

QString BackendInfo::description() const
{
    Q_D(const BackendInfo);
    return d->description;
}

QString BackendInfo::executable() const
{
    Q_D(const BackendInfo);
    return d->executable;
}

QString BackendInfo::backendIdentifier() const
{
    Q_D(const BackendInfo);
    return d->identifier;
}

QString BackendInfo::backendCountry() const
{
    Q_D(const BackendInfo);
    return d->country;
}

QStringList BackendInfo::backendCities() const
{
    Q_D(const BackendInfo);
    return d->cities;
}

QString BackendInfo::backendAuthor() const
{
    Q_D(const BackendInfo);
    return d->author;
}

QString BackendInfo::backendEmail() const
{
    Q_D(const BackendInfo);
    return d->email;
}

QString BackendInfo::backendWebsite() const
{
    Q_D(const BackendInfo);
    return d->website;
}

QString BackendInfo::backendVersion() const
{
    Q_D(const BackendInfo);
    return d->version;
}

}

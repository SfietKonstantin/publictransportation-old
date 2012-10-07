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

#include "backendinfo.h"
#include "desktopfileparser_p.h"

#include <QtCore/QDebug>
#include <QtCore/QLocale>
#include <QtCore/QSharedData>

#ifdef MEEGO_EDITION_HARMATTAN
#include <MLocale>
#endif

namespace PublicTransportation
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
    QStringList languages;
#if (QT_VERSION < QT_VERSION_CHECK(4, 8, 0))
#  ifdef MEEGO_EDITION_HARMATTAN
    MLocale locale = MLocale();
    languages.append(locale.name());
    languages.append(locale.language());
    languages.append(QString("%1_%2").arg(locale.language()).arg(locale.country()));
#  endif
#else
    languages = QLocale::system().uiLanguages();
#endif
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

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

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file desktopfileparser_p.cpp
 * @short Implementation of PT2::DesktopFileParser
 */

#include "desktopfileparser_p.h"

#include <QtCore/QSettings>

namespace PT2
{

/**
 * @internal
 * @brief Private class for PublicTransportation::DesktopFileParser
 */
class DesktopFileParserPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param file the file to parse.
     */
    DesktopFileParserPrivate(const QString &file);
    /**
     * @internal
     * @brief Get the true key
     *
     * This method is used to get the true key,
     * provided a key, and a language code.
     *
     * The true key will be in the following form:
     * key[lang].
     *
     * If no language code is passed, the passed
     * key is returned.
     *
     * @param key key.
     * @param lang language code.
     * @return true key.
     */
    static QString trueKey(const QString &key, const QString &lang);

    /**
     * @internal
     * @brief QSettings
     *
     * This QSettings instance is used to parse
     * the desktop file.
     */
    QSettings settings;
    /**
     * @internal
     * @brief The file being parsed
     */
    QString file;
};

DesktopFileParserPrivate::DesktopFileParserPrivate(const QString &file):
    settings(file, QSettings::IniFormat)
{
    settings.setIniCodec("UTF-8");
    this->file = file;
}

QString DesktopFileParserPrivate::trueKey(const QString &key, const QString &lang)
{
    if (lang.isEmpty()) {
        return key;
    } else {
        QString trueKey = QString("%1[%2]").arg(key).arg(lang);
        return trueKey;
    }
}

////// End of private class //////

DesktopFileParser::DesktopFileParser(const QString &file):
    d_ptr(new DesktopFileParserPrivate(file))
{
}

DesktopFileParser::~DesktopFileParser()
{
}

QString DesktopFileParser::file() const
{
    Q_D(const DesktopFileParser);
    return d->file;
}

void DesktopFileParser::beginGroup(const QString &group)
{
    Q_D(DesktopFileParser);
    d->settings.beginGroup(group);
}

void DesktopFileParser::endGroup()
{
    Q_D(DesktopFileParser);
    d->settings.endGroup();
}

QStringList DesktopFileParser::keys() const
{
    Q_D(const DesktopFileParser);
    return d->settings.childKeys();
}

bool DesktopFileParser::contains(const QString &key, const QString &lang) const
{
    Q_D(const DesktopFileParser);
    return d->settings.contains(d->trueKey(key, lang));
}

QVariant DesktopFileParser::value(const QString &key, const QString &lang) const
{
    Q_D(const DesktopFileParser);
    return d->settings.value(d->trueKey(key, lang));
}

}

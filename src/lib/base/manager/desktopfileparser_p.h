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

#ifndef PT2_DESKTOPFILEPARSER_P_H
#define PT2_DESKTOPFILEPARSER_P_H

// Warning
//
// This file exists for the convenience
// of other publictransportation classes.
// This header file may change from version
// to version without notice or even be removed.


/**
 * @internal
 * @file desktopfileparser_p.h
 * @short Definition of PT2::DesktopFileParser
 */

#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

namespace PT2
{

class DesktopFileParserPrivate;

/**
 * @internal
 * @brief A desktop file parser
 *
 * This class is used to parse desktop files,
 * that are INI-like files. It wraps a QSettings
 * and provides some more capabilities, like
 * finding language key.
 */
class DesktopFileParser
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param file desktop file to parse.
     */
    explicit DesktopFileParser(const QString &file);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~DesktopFileParser();
    /**
     * @internal
     * @brief Desktop file to parse
     * @return desktop file to parse.
     */
    QString file() const;
    /**
     * @internal
     * @brief Begin group
     *
     * This method is used to set the current group
     * that is used to parse the desktop file.
     *
     * @param group name of the group.
     */
    void beginGroup(const QString &group);
    /**
     * @internal
     * @brief End group
     *
     * This method is used to unset the current group
     * that is used to parse the desktop file.
     */
    void endGroup();
    /**
     * @internal
     * @brief Available keys
     *
     * This method is used to get the available keys
     * in the current group.
     *
     * @return available keys.
     */
    QStringList keys() const;
    /**
     * @internal
     * @brief If the desktop file contains a key
     *
     * This method is used to check if the current group
     * contains a key, with an associated language key.
     *
     * @param key the key to check.
     * @param lang the language key associated to the key.
     * @return if the desktop file contains the key.
     */
    bool contains(const QString &key, const QString &lang = QString()) const;
    /**
     * @internal
     * @brief Value
     *
     * This method is used to get the value associated to
     * a key in the current group, with an associated language
     * key.
     *
     * @param key the key to retrieve.
     * @param lang the language key associated to the key.
     * @return value associated to the key and language key.
     */
    QVariant value(const QString &key, const QString &lang = QString()) const;
protected:
    /**
     * @internal
     * @brief D-pointer
     */
    const QScopedPointer<DesktopFileParserPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DesktopFileParser)
};

}

#endif // PT2_DESKTOPFILEPARSER_P_H

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
#ifndef PT2_BACKENDINFO_H
#define PT2_BACKENDINFO_H

/**
 * @file backendinfo.h
 * @short Definition of PT2::BackendInfo
 */

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QStringList>

namespace PT2
{


/**
 * @internal
 * @brief Private class for PT2::BackendInfo
 *
 * This class is used to store the explicitly shared
 * data for PT2::BackendInfo.
 */
struct BackendInfoPrivate: public QSharedData
{
    /**
     * @internal
     * @brief Icon
     */
    QString icon;
    /**
     * @internal
     * @brief Name
     */
    QString name;
    /**
     * @internal
     * @brief Description
     */
    QString description;
    /**
     * @internal
     * @brief Executable
     */
    QString executable;
    /**
     * @internal
     * @brief Identifier
     */
    QString identifier;
    /**
     * @internal
     * @brief Author
     */
    QString author;
    /**
     * @internal
     * @brief Email
     */
    QString email;
    /**
     * @internal
     * @brief Website
     */
    QString website;
    /**
     * @internal
     * @brief Version
     */
    QString version;
    /**
     * @internal
     * @brief Country
     */
    QString country;
    /**
     * @internal
     * @brief Cities
     */
    QStringList cities;
};

/**
 * @brief Informations about a backend
 *
 * This class is used to get informations about
 * a given backend. This information is extracted
 * from a desktop file, that contains some
 * extensions in order to provide public transportation
 * specific backend informations.
 *
 * \section backendInfoDesktopFile Desktop file format
 *
 * The desktop file have the following structure
 * \code{.desktop}
 * [Desktop Entry]
 * Name=Backend name
 * Comment=Comment on the backend
 * Icon=/path/to/an/icon
 * Type=Service
 * Exec=$PROVIDER plugin.so
 * # Exec=python myscript.py
 * X-PublicTransportation-BackendInfo-Id=com.mycompany.backendname
 * X-PublicTransportation-BackendInfo-Country=COUNTRY-ISO-CODE (nothing for international)
 * X-PublicTransportation-BackendInfo-Cities=City 1,City 2 (or All for national)
 * X-PublicTransportation-BackendInfo-Author=Some author
 * X-PublicTransportation-BackendInfo-Email=some.author@mycompany.com
 * X-PublicTransportation-BackendInfo-Website=http://www.mycompany.com
 * X-PublicTransportation-BackendInfo-Version=1.0.0
 * \endcode
 *
 * \b Name, \b Comment, \b Icon are used to provide basic informations about
 * the backend, while \b Type must be specified as "Service". More informations
 * about the plugin should be provided using the \b X-PublicTransportation-BackendInfo-*
 * keys. The \b Id key is mandatory, and should be unique, since it is used to
 * identify the backend.
 *
 * \b Exec should provide the executable name. It can provide either a script,
 * or use the provider loader to load C++ plugin. In that case, you should use
 * $PROVIDER to replace the path of the provider. Please note that, while being
 * executed, one more parameter, that is "\-\-identifier someidentifier" is passed
 * to the executable. This identifier is used to communicate between the backend
 * and the backend manager.
 *
 * For example, with DBus, this identifier is the path to the DBus object that
 * corresponds to the backend being run.
 */
class BackendInfo
{
public:
    /**
     * @brief Invalid constructor
     */
    explicit BackendInfo();
    /**
     * @brief Default constructor
     * @param file file to parse.
     */
    explicit BackendInfo(const QString &file);
    /**
     * @brief Copy constructor
     * @param other other BackendInfo.
     */
    BackendInfo(const BackendInfo &other);
    /**
     * @short Destructor
     */
    virtual ~BackendInfo();
    /**
     * @brief If the backend is valid
     * @return if the backend is valid.
     */
    bool isValid() const;
    /**
     * @brief Icon of the backend
     * @return icon of the backend.
     */
    QString icon() const;
    /**
     * @short Name of the backend
     * @return name of the backend.
     */
    QString name() const;
    /**
     * @short Description of the backend
     * @return description of the backend.
     */
    QString description() const;
    /**
     * @brief Executable that is launched
     * @return executable that is launched.
     */
    QString executable() const;
    /**
     * @brief Backend identifier
     * @return backend identifier.
     */
    QString backendIdentifier() const;
    /**
     * @brief Backend country
     * @return backend country.
     */
    QString backendCountry() const;
    /**
     * @brief Backend cities
     * @return backend cities.
     */
    QStringList backendCities() const;
    /**
     * @brief Backend author
     * @return backend author.
     */
    QString backendAuthor() const;
    /**
     * @brief Backend email
     * @return backend email.
     */
    QString backendEmail() const;
    /**
     * @brief Backend website
     * @return backend website.
     */
    QString backendWebsite() const;
    /**
     * @brief Backend version
     * @return backend version.
     */
    QString backendVersion() const;
protected:
    /**
     * @brief D-pointer
     */
    QExplicitlySharedDataPointer<BackendInfoPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(BackendInfo)
};

}

#endif // PT2_BACKENDINFO_H

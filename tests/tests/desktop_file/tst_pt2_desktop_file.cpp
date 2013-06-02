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

#include <QtCore/QLocale>
#include <QtTest/QtTest>

#include <manager/desktopfileparser_p.h>
#include <manager/backendinfo.h>

class TstPt2Data: public QObject
{
    Q_OBJECT

private slots:
    void testDesktopFileParser()
    {
        PT2::DesktopFileParser desktopFileParser (":/a.desktop");
        desktopFileParser.beginGroup("Desktop Entry");
        QStringList keys = desktopFileParser.keys();
        QCOMPARE(keys.contains("Name") == true, true);
        QCOMPARE(keys.contains("Comment") == true, true);
        QCOMPARE(keys.contains("Icon") == true, true);
        QCOMPARE(keys.contains("Name[fr_FR]") == true, true);
        QCOMPARE(keys.contains("Comment[fr_FR]") == true, true);
        QCOMPARE(desktopFileParser.value("Name").toString(), QString("A name"));
        QCOMPARE(desktopFileParser.value("Comment").toString(), QString("A comment"));
        QCOMPARE(desktopFileParser.value("Icon").toString(), QString("An icon"));
        QCOMPARE(desktopFileParser.value("Name", "fr_FR").toString(),
                 QString("A name in French"));
        QCOMPARE(desktopFileParser.value("Comment", "fr_FR").toString(),
                 QString("A comment in French"));
        QCOMPARE(desktopFileParser.value("Name", "de").toString(), QString());
        desktopFileParser.endGroup();
    }
    void testBackendInfo()
    {
        PT2::BackendInfo backendInfo (":/backend1.desktop");
        QCOMPARE(backendInfo.isValid() == true, true);
        QCOMPARE(backendInfo.icon(), QString("/path/to/an/icon.png"));
        QCOMPARE(backendInfo.name(), QString("A backend"));
        QCOMPARE(backendInfo.description(), QString("Comment about a backend"));
        QCOMPARE(backendInfo.executable(), QString("$PROVIDER backend.so"));
        QCOMPARE(backendInfo.backendIdentifier(), QString("org.SfietKonstantin.backend"));
        QCOMPARE(backendInfo.backendCountry(), QString("FR"));
        QCOMPARE(backendInfo.backendCities().contains("Paris") == true, true);
        QCOMPARE(backendInfo.backendCities().contains("Lyon") == true, true);
        QCOMPARE(backendInfo.backendCities().contains("Strasbourg") == true, true);
        QCOMPARE(backendInfo.backendAuthor(), QString("Lucien XU"));
        QCOMPARE(backendInfo.backendEmail(), QString("my.email@provider.com"));
        QCOMPARE(backendInfo.backendWebsite(), QString("http://mywebsite.com"));
        QCOMPARE(backendInfo.backendVersion(), QString("1.0.0"));
    }
    void testBackendInfo2()
    {
        QLocale::setDefault(QLocale("de"));
        PT2::BackendInfo backendInfo (":/backend2.desktop");
        QCOMPARE(backendInfo.isValid() == true, true);
        QCOMPARE(backendInfo.icon(), QString("/path/to/an/icon.png"));
        QCOMPARE(backendInfo.name(), QString("A backend in German"));
        QCOMPARE(backendInfo.description(), QString("Comment about a backend in German"));
        QCOMPARE(backendInfo.executable(), QString("$PROVIDER backend.so"));
        QCOMPARE(backendInfo.backendIdentifier(), QString("org.SfietKonstantin.backend"));
        QCOMPARE(backendInfo.backendCountry(), QString("FR"));
        QCOMPARE(backendInfo.backendCities().contains("Paris") == true, true);
        QCOMPARE(backendInfo.backendAuthor(), QString("Lucien XU"));
        QCOMPARE(backendInfo.backendEmail(), QString("my.email@provider.com"));
        QCOMPARE(backendInfo.backendWebsite(), QString("http://mywebsite.com"));
        QCOMPARE(backendInfo.backendVersion(), QString("1.0.0"));
    }
};

QTEST_MAIN(TstPt2Data)

#include "tst_pt2_desktop_file.moc"

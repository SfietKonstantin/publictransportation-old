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


#include <QtCore/QLocale>
#include <QtTest/QtTest>

#include "manager/desktopfileparser_p.h"
#include "manager/backendinfo.h"

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

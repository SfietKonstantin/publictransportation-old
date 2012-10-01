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

/**
 * @internal
 * @file tests/tests/main.cpp
 * @short Entry point of the tests
 */

#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

#include "testbase.h"
#include "testdbus.h"

/**
 * @internal
 * @short Main
 *
 * Entry point of the test application
 * that tests public transportation.
 *
 * @param argc argc.
 * @param argv argv.
 * @return exit code.
 */
int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);
    Q_UNUSED(app)

    TestBase testBase;
    QTest::qExec(&testBase, argc, argv);

    TestDBus testDBus;
    QTest::qExec(&testDBus, argc, argv);

    return 0;
}

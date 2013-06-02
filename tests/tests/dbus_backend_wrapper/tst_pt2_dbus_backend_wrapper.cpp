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

#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtDBus/QDBusConnection>
#include <manager/dbus/dbusbackendwrapper.h>
#include <common/dbus/dbusconstants.h>

static const char *HELPERS_DIR = "helpers";
static const char *DUMMY = "dummy_dbus_provider";

class TstPt2DBusBackendWrapper: public QObject
{
    Q_OBJECT

private:
    static const QString helper()
    {
        // Try to find the helper
        QString path;

        QDir dir (QCoreApplication::instance()->applicationDirPath());
        dir.cd(HELPERS_DIR);
        if (dir.exists(DUMMY)) {
            path = dir.absoluteFilePath(DUMMY);
        } else {
            dir = QDir(QCoreApplication::instance()->applicationDirPath());
            dir.cdUp();
            dir.cdUp();
            dir.cd(HELPERS_DIR);
            dir.cd(DUMMY);
            path = dir.absoluteFilePath(DUMMY);
        }
        return path;
    }

private slots:
    void testDBusBackendWrapperDeath()
    {
        QString path = helper();

        if (path.isEmpty()) {
            QSKIP("Failed to find the dummy provider", SkipAll);
        }

        QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
        PT2::DBusBackendWrapper wrapper ("org.SfietKonstantin.test", path + " --fake-death", this);
        wrapper.launch();
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Launching);
        QTest::qWait(1000);
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Stopped);
        QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
    }

    void testDBusBackendWrapperNoReply()
    {
        QString path = helper();

        if (path.isEmpty()) {
            QSKIP("Failed to find the dummy provider", SkipAll);
        }

        QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
        PT2::DBusBackendWrapper wrapper ("org.SfietKonstantin.test", path + " --fake-noreply",
                                         this);
        wrapper.launch();
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Launching);
        QTest::qWait(1000);
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Loading);
        QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
    }

    void testDBusBackendWrapperQuit()
    {
        QString path = helper();

        if (path.isEmpty()) {
            QSKIP("Failed to find the dummy provider", SkipAll);
        }

        QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
        PT2::DBusBackendWrapper wrapper ("org.SfietKonstantin.test", path + " --quit", this);

        wrapper.launch();
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Launching);
        QTest::qWait(500);
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Stopped);
        QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
    }

    void testDBusBackendWrapperSegfault()
    {
        QString path = helper();

        if (path.isEmpty()) {
            QSKIP("Failed to find the dummy provider", SkipAll);
        }

        QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
        PT2::DBusBackendWrapper wrapper ("org.SfietKonstantin.test", path + " --segfault",
                                         this);
        wrapper.launch();
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Launching);
        QTest::qWait(500);
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Stopped);
        QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
    }

    void testDBusBackendWrapperNormal()
    {
        QString path = helper();

        if (path.isEmpty()) {
            QSKIP("Failed to find the dummy provider", SkipAll);
        }

        QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
        PT2::DBusBackendWrapper wrapper ("org.SfietKonstantin.test", path, this);
        wrapper.launch();
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Launching);
        QTest::qWait(1000);
        QCOMPARE(wrapper.status(), PT2::AbstractBackendWrapper::Loading);
        QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
    }
};

QTEST_MAIN(TstPt2DBusBackendWrapper)

#include "tst_pt2_dbus_backend_wrapper.moc"

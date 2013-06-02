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
#include <QtTest/QSignalSpy>
#include <QtCore/QDebug>

#include <manager/abstractbackendwrapper.h>
#include <manager/abstractbackendwrapper_p.h>
#include "../generator.h"

static const char *IDENTIFIER = "";

namespace PT2
{

class BackendWrapper: public PT2::AbstractBackendWrapper
{
public:
    explicit BackendWrapper(const QString &identifier, const QString &executable,
                            QObject *parent = 0):
        AbstractBackendWrapper(identifier, executable, parent)
    {
    }
    void launch() {}
    void stop() {}
    void waitForStopped() {}
    void kill() {}
    QString publicExecutable()
    {
        return executable();
    }
    void publicSetStatus(Status status)
    {
        setStatus(status);
    }
    void publicSetLastError(const QString &lastError)
    {
        setLastError(lastError);
    }
    void publicSetCapabilities(const QStringList &capabilities)
    {
        setCapabilities(capabilities);
    }
    void publicSetCopyright(const QString &copyright)
    {
        setCopyright(copyright);
    }
    QMap<QString, RequestData *> publicRequests() const
    {
        Q_D(const AbstractBackendWrapper);
        return d->requests;
    }
    QString publicCreateRequest(RequestType requestType)
    {
        return createRequest(requestType);
    }

private:
    Q_DECLARE_PRIVATE(AbstractBackendWrapper)
};

}

class TstPt2AbstractBackendWrapper: public QObject
{
    Q_OBJECT

private slots:
    void testBaseCommonEntities()
    {
        Generator::initRand();
        // Check constructor
        QString identifier = Generator::generateRandomString();
        QString executable = Generator::generateRandomString();
        PT2::BackendWrapper backendWrapper (identifier, executable);
        QCOMPARE(backendWrapper.identifier(), identifier);
        QCOMPARE(backendWrapper.publicExecutable(), executable);

        // Check status
        QSignalSpy statusSpy(&backendWrapper, SIGNAL(statusChanged()));
        backendWrapper.publicSetStatus(PT2::BackendWrapper::Running);
        QCOMPARE(backendWrapper.status(), PT2::BackendWrapper::Running);
        QCOMPARE(statusSpy.count(), 1);
        QCOMPARE(statusSpy.takeFirst().isEmpty() == true, true);

        // Check last error
        QString lastError = Generator::generateRandomString();
        backendWrapper.publicSetLastError(lastError);

        // Check capabilities
        QStringList capabilities;
        int totalCapabilities = rand() % 10 + 5;
        for (int i = 0; i < totalCapabilities; i++) {
            capabilities.append(Generator::generateRandomString());
        }
        QSignalSpy capabilitiesSpy(&backendWrapper, SIGNAL(capabilitiesChanged()));
        backendWrapper.publicSetCapabilities(capabilities);
        QCOMPARE(backendWrapper.capabilities(), capabilities);
        QCOMPARE(capabilitiesSpy.count(), 1);
        QCOMPARE(capabilitiesSpy.takeFirst().isEmpty() == true, true);

        // Check copyright
        QString copyright = Generator::generateRandomString();
        QSignalSpy copyrightSpy(&backendWrapper, SIGNAL(copyrightChanged()));
        backendWrapper.publicSetCopyright(copyright);
        QCOMPARE(backendWrapper.copyright(), copyright);
        QCOMPARE(copyrightSpy.count(), 1);
        QCOMPARE(copyrightSpy.takeFirst().isEmpty() == true, true);

        // Check create request
        // TODO: write unit test later
    }
};

QTEST_MAIN(TstPt2AbstractBackendWrapper)

#include "tst_pt2_abstract_backend_wrapper.moc"

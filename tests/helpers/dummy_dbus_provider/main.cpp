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

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtDBus/QDBusInterface>
#include <common/dbus/dbusconstants.h>

class Object: public QObject
{
    Q_OBJECT
public:
    explicit Object(const QString &identifier, QObject *parent = 0):
        QObject(parent)
    {
        m_identifier = identifier;
        m_counter = 0;
    }
public slots:
    void timeout()
    {
        m_counter ++;
        if (m_counter == 1) {
            qDebug() << "Registering the backend";
            QDBusInterface interface (DBUS_SERVICE,
                                      QString(DBUS_BACKEND_PATH_PREFIX) + m_identifier);
            interface.call("registerBackendStart");
        }
    }
private:
    int m_counter;
    QString m_identifier;
};

int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);
    int indexOfIdentifier = app.arguments().indexOf("--identifier") + 1;
    QString identifier = app.arguments().at(indexOfIdentifier);
    qDebug() << "Identifier" << identifier;
    if (app.arguments().contains("--fake-death")) {
        qDebug() << "Faking death";
        QTimer *timer = new QTimer();
        QObject::connect(timer, SIGNAL(timeout()), &app, SLOT(quit()));
        timer->start(250);
    } else if (app.arguments().contains("--fake-noreply")) {
        qDebug() << "Faking no reply";
        QDBusInterface interface (DBUS_SERVICE, QString(DBUS_BACKEND_PATH_PREFIX) + identifier);
        interface.call("registerBackendStart");
    } else if (app.arguments().contains("--segfault")) {
        qDebug() << "Creating a segmentation fault";
        int *a = NULL;
        *a = 3;
    } else if (app.arguments().contains("--quit")) {
        qDebug() << "Quitting";
        return 0;
    } else {
        qDebug() << "Normal behaviour";
        Object *object = new Object(identifier);
        QTimer *timer = new QTimer(object);
        timer->setSingleShot(false);
        QObject::connect(timer, SIGNAL(timeout()), object, SLOT(timeout()));
        timer->start(500);
    }

    app.exec();
}

#include "main.moc"

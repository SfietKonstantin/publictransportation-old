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

/**
 * @file generator.cpp
 * @short Implementation of Generator
 */

#include "generator.h"

#include <QtCore/QDateTime>
#include <math.h>

/**
 * @brief LETTERS
 *
 * Used in Generator.
 */
static const char *LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void Generator::initRand()
{
    qsrand(QDateTime::currentDateTime().currentMSecsSinceEpoch());
}

bool Generator::generateRandomBool()
{
    if (rand() % 2) {
        return true;
    } else {
        return false;
    }
}

int Generator::generateRandomNumber()
{
    int randomInt = rand();
    if (generateRandomBool()) {
        return randomInt;
    } else {
        return -1 * randomInt;
    }
}

double Generator::generateRandomDouble()
{
    int randomInt = rand();
    int numberOfDigits = log(randomInt);
    int randomNumberOfDigits = rand() % (numberOfDigits + 1);

    float randomFloat = ((float) randomInt) / (pow(10, randomNumberOfDigits));
    if (generateRandomBool()) {
        return randomFloat;
    } else {
        return -1 * randomFloat;
    }
}

QString Generator::generateRandomString()
{
    int size = (rand() % 50) + 10;
    QByteArray data (LETTERS);

    QByteArray output;
    for (int i = 0; i < size; i++) {
        output.append(data.at(rand() % data.size()));
    }
    return QString::fromAscii(output);
}

QVariantMap Generator::generateRandomVariantMap()
{
    QVariantMap data;
    data.insert("someBool", generateRandomBool());
    data.insert("someInt", generateRandomNumber());
    data.insert("someDouble", generateRandomDouble());
    data.insert("someString", generateRandomString());
    return data;
}

int Generator::rand()
{
    return qrand();
}

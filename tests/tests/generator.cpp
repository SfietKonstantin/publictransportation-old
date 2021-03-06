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

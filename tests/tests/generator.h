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

#ifndef GENERATOR_H
#define GENERATOR_H

/**
 * @file generator.h
 * @short Definition of Generator
 */

#include <QtCore/QVariantMap>

/**
 * @brief Generates random values
 *
 * This class groups a set of methods
 * that are used to generate random
 * values, that can be integers, doubles,
 * strings, boolean or variant maps.
 *
 * Initializing the generator (using the
 * current date and time as a seed) is done
 * by calling initRand().
 *
 * These methods are used for generating
 * the random values:
 * - generateRandomBool()
 * - generateRandomNumber()
 * - generateRandomDouble()
 * - generateRandomString()
 * - generateRandomVariantMap()
 *
 * Random variables can be useful for unittesting.
 */
class Generator
{
public:
    /**
     * @brief Initialize the random values generator
     */
    static void initRand();
    /**
     * @brief Generate a random boolean
     * @return a random boolean.
     */
    static bool generateRandomBool();
    /**
     * @brief Generate a random integer number
     * @return a random integer number.
     */
    static int generateRandomNumber();
    /**
     * @brief Generate a random double
     * @return a random double.
     */
    static double generateRandomDouble();
    /**
     * @brief Generate a random string
     * @return a random string.
     */
    static QString generateRandomString();
    /**
     * @brief Generate a random variant map
     *
     * The generated variant map always contains a
     * boolean, an integer, a double and a string.
     *
     * @return a random variant map.
     */
    static QVariantMap generateRandomVariantMap();
private:
    /**
     * @internal
     * @brief rand
     * @return random positive integer.
     */
    static int rand();
};

#endif // GENERATOR_H

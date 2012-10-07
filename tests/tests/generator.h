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

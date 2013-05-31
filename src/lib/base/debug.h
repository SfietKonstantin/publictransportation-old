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

#ifndef PT2_DEBUG_H
#define PT2_DEBUG_H

/**
 * @internal
 * @file debug.h
 * @short Debug methods
 */

#include <QtCore/QDebug>

namespace PT2
{

/**
 * @internal
 * @brief Debug
 *
 * This method outputs a debug trace, that
 * is prefixed with the name of the component to debug.
 *
 * @param prefix prefix.
 * @return a QDebug object used for debugging.
 */
inline QDebug debug(const QByteArray &prefix)
{
    QByteArray truePrefix = "  [" + prefix + "]";
    return (QDebug(QtDebugMsg) << truePrefix.constData());
}

/**
 * @internal
 * @brief Warning
 *
 * This method outputs a warning, that
 * is prefixed with the name of the component to debug.
 *
 * @param prefix prefix.
 * @return a QDebug object used for warning.
 */
inline QDebug warning(const QByteArray &prefix)
{
    QByteArray truePrefix = "W [" + prefix + "]";
    return (QDebug(QtWarningMsg) << truePrefix.constData());
}

/**
 * @internal
 * @brief Fatal
 *
 * This method outputs a fatal message, that
 * is prefixed with the name of the component to debug.
 *
 * Most of the time, a fatal message interrupts the
 * program.
 *
 * @param prefix prefix.
 * @return a QDebug object used for debugging.
 */
inline QDebug fatal(const QByteArray &prefix)
{
    QByteArray truePrefix = "! [" + prefix + "]";
    return (QDebug(QtFatalMsg) << truePrefix.constData());
}

}

#endif // PT2_DEBUG_H

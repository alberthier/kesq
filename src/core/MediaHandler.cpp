/***************************************************************************
 *   Copyright (C) 2008 by Éric ALBER                                      *
 *   eric.alber@gmail.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "MediaHandler.h"
#include <QMetaObject>

using namespace Kesq;

MediaHandler::MediaHandler(QObject* parent) :
    Plugin(parent)
{
}

MediaHandler::~MediaHandler()
{
}

bool MediaHandler::handles(const QUrl& media)
{
    bool ret = false;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "handles", Q_RETURN_ARG(bool, ret), Q_ARG(const QUrl, media));
    }
    return ret;
}

void MediaHandler::setMedia(const QUrl& media)
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "setMedia", Q_ARG(const QUrl, media));
    }
}

void MediaHandler::togglePlayback()
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "togglePlayback");
    }
}

void MediaHandler::stop()
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "stop");
    }
}

void MediaHandler::fastForward()
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "fastForward");
    }
}

void MediaHandler::fastRewind()
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "fastRewind");
    }
}

int MediaHandler::volume()
{
    int ret = 0;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "volume", Q_RETURN_ARG(int, ret));
    }
    return ret;
}

void MediaHandler::setVolume(int v)
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "setVolume", Q_ARG(int, v));
    }
}

QString MediaHandler::artist() const
{
    QString ret;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "artist", Q_RETURN_ARG(QString, ret));
    }
    return ret;
}

QString MediaHandler::album() const
{
    QString ret;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "album", Q_RETURN_ARG(QString, ret));
    }
    return ret;
}

QString MediaHandler::title() const
{
    QString ret;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "title", Q_RETURN_ARG(QString, ret));
    }
    return ret;
}

QTime MediaHandler::length() const
{
    QTime ret;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "length", Q_RETURN_ARG(QTime, ret));
    }
    return ret;
}

QTime MediaHandler::currentTime() const
{
    QTime ret;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "currentTime", Q_RETURN_ARG(QTime, ret));
    }
    return ret;
}

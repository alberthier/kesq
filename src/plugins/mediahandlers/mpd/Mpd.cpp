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

#include "Mpd.h"
#include <QtPlugin>
#include <QDomDocument>
#include <QDomElement>
#include <QUrl>
#include <libmpd/libmpdclient.h>

Q_EXPORT_PLUGIN2(org.kesq.mpd, Mpd);

Mpd::Mpd() :
    QObject(),
    m_volume(0),
    m_port(0),
    m_connection(NULL)
{
}

Mpd::~Mpd()
{
    mpd_closeConnection(m_connection);
}

/**
 * 
 * @param config 
 * @param mainDataDir 
 * @param userDataDir 
 */
void Mpd::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    Q_UNUSED(mainDataDir);
    Q_UNUSED(userDataDir);

    if (config != NULL) {
        QDomElement root(config->documentElement());
        if (root.tagName() == "Mpd") {
            for (QDomNode n(root.firstChild()); !n.isNull(); n = n.nextSibling()) {
                if (n.isElement()) {
                    QDomElement e(n.toElement());
                    if (e.tagName() == "Connection") {
                        m_server = e.attribute("server");
                        m_port = e.attribute("port").toUShort();
                    }
                }
            }
        }
    }
    m_connection = mpd_newConnection(m_server.toAscii(), m_port, 10);
    if (m_connection != NULL) {
        mpd_Status* status = mpd_getStatus(m_connection);
        if (status != NULL) {
            m_volume = status->volume;
            mpd_freeStatus(status);
        }
    }
}

bool Mpd::handles(const QUrl& media)
{
    if (media.scheme() == "mpd") {
        return true;
    }
    return false;
}

void Mpd::setMedia(const QUrl& media)
{
    if (media.hasQueryItem("togglePlayback")) {
        m_command = "togglePlayback";
    } else {
        m_command = QString::null;
    }
}

void Mpd::togglePlayback()
{
    if (m_connection != NULL) {
        if (m_command == "togglePlayback") {
            mpd_Status* status = mpd_getStatus(m_connection);
            if (status != NULL) {
                mpd_sendPauseCommand(m_connection, status->state == MPD_STATUS_STATE_PLAY);
                mpd_freeStatus(status);
            }
        }
    }
}

void Mpd::stop()
{
}

void Mpd::fastForward()
{
}

void Mpd::fastRewind()
{
}

int Mpd::volume()
{
    return m_volume;
}

void Mpd::setVolume(int v)
{
    m_volume = v;
    if (m_connection != NULL) {
        mpd_sendSetvolCommand(m_connection, v);
    }
}

QString Mpd::artist() const
{
    return QString::null;
}

QString Mpd::album() const
{
    return QString::null;
}

QString Mpd::title() const
{
    return QString::null;
}

QTime Mpd::length() const
{
    return QTime();
}

QTime Mpd::currentTime() const
{
    return QTime();
}


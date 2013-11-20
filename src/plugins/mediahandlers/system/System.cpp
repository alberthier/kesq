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

#include "System.h"
#include <QtPlugin>
#include <QUrl>
#include <QProcess>

Q_EXPORT_PLUGIN2(org.kesq.system, System);

System::System() :
    QObject(),
    m_volume(0)
{
}

System::~System()
{
}

void System::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    Q_UNUSED(config);
    Q_UNUSED(mainDataDir);
    Q_UNUSED(userDataDir);
}

bool System::handles(const QUrl& media)
{
    if (media.scheme() == "system") {
        return true;
    }
    return false;
}

void System::setMedia(const QUrl& media)
{
    m_commandLine = media.path();
}

void System::togglePlayback()
{
    if (!m_commandLine.isEmpty()) {
        QProcess::startDetached(m_commandLine);
        m_commandLine = QString::null;
    }
}

void System::stop()
{
}

void System::fastForward()
{
}

void System::fastRewind()
{
}

int System::volume()
{
    return m_volume;
}

void System::setVolume(int v)
{
    m_volume = v;
}

QString System::artist() const
{
    return QString::null;
}

QString System::album() const
{
    return QString::null;
}

QString System::title() const
{
    return QString::null;
}

QTime System::length() const
{
    return QTime();
}

QTime System::currentTime() const
{
    return QTime();
}


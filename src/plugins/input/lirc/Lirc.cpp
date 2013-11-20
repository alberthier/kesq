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

#include "Lirc.h"
#include <QtPlugin>
#include "QlircInput.h"
#include <QFile>

Q_EXPORT_PLUGIN2(org.kesq.lirc, Lirc);

Lirc::Lirc() :
    QObject()
{
    connect(QlircInput::instance(), SIGNAL(keyPressed(const QString&)), this, SLOT(remoteKeyPressed(const QString&)));
}

Lirc::~Lirc()
{
}

void Lirc::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    Q_UNUSED(config);

    QString lircrc(userDataDir + "/lircrc");
    if (!QFile::exists(lircrc)) {
        lircrc = mainDataDir + "/lircrc";
        if (!QFile::exists(lircrc)) {
            lircrc = QString::null;
        }
    }
    if (!QlircInput::instance()->init(lircrc)) {
        qWarning(tr("Unable to initialize LIRC").toAscii());
    }
}

void Lirc::remoteKeyPressed(const QString& key)
{
    if (key == "SELECT") {
        emit select();
    } else if (key == "BACK") {
        emit back();
    } else if (key == "MOVEUP") {
        emit moveUp();
    } else if (key == "MOVEDOWN") {
        emit moveDown();
    } else if (key == "PLAYPAUSE") {
        emit togglePlayback();
    } else if (key == "STOP") {
        emit stop();
    } else if (key == "FASTFORWARD") {
        emit fastForward();
    } else if (key == "FASTREWIND") {
        emit fastRewind();
    } else if (key == "PREVIOUS") {
        emit previous();
    } else if (key == "NEXT") {
        emit next();
    } else if (key == "VOLUME+") {
        emit volumeUp();
    } else if (key == "VOLUME-") {
        emit volumeDown();
    }
}

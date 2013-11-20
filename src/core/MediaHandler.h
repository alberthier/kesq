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

#ifndef MEDIA_HANDLER_H
#define MEDIA_HANDLER_H

#include "Plugin.h"
#include <QUrl>
#include <QTime>

namespace Kesq
{

class MediaHandler : public Plugin
{
    Q_OBJECT
public:
    MediaHandler(QObject* parent = NULL);
    virtual ~MediaHandler();

public slots:
    bool handles(const QUrl& media);
    void setMedia(const QUrl& media);
    void togglePlayback();
    void stop();
    void fastForward();
    void fastRewind();
    int volume();
    void setVolume(int v);
    QString artist() const;
    QString album() const;
    QString title() const;
    QTime length() const;
    QTime currentTime() const;

signals:
    void playbackFinished();
};

}

#endif // MEDIA_HANDLER_H

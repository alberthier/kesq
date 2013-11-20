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

#ifndef MOUSE_H
#define MOUSE_H

#include <QObject>

class QDomDocument;

class Mouse : public QObject
{
    Q_OBJECT
public:
    Mouse();
    virtual ~Mouse();
    virtual bool eventFilter(QObject* watched, QEvent* event);

public slots:
    void setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir);

signals:
    void select();
    void back();
    void moveUp();
    void moveDown();
    void togglePlayback();
    void stop();
    void fastForward();
    void fastRewind();
    void previous();
    void next();
    void volumeUp();
    void volumeDown();
};

#endif // MOUSE_H

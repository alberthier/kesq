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

#ifndef INPUT_H
#define INPUT_H

#include "Plugin.h"

namespace Kesq
{

class Input : public Plugin
{
    Q_OBJECT
public:
    Input(QObject* parent = NULL);
    virtual ~Input();

signals:
    // Navigation
    void select();
    void back();
    void moveUp();
    void moveDown();

    // Playback
    void togglePlayback();
    void stop();
    void fastForward();
    void fastRewind();
    void previous();
    void next();
    void volumeUp();
    void volumeDown();
};

}

#endif // INPUT_H

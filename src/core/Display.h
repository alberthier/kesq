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

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Plugin.h"

class QAbstractItemModel;
class QItemSelectionModel;
class QTime;

namespace Kesq
{

class Display : public Plugin
{
    Q_OBJECT
public:
    Display(QObject* parent = NULL);
    virtual ~Display();

public slots:
    void setModel(QAbstractItemModel* model, const QString& label);
    void setSelectionModel(QItemSelectionModel* selection);
    void setMediaInfo(const QString& artist, const QString& album, const QString& title, const QTime& length);
    void setCurrentTime(const QTime& currentTime);
};

}

#endif // DISPLAY_H

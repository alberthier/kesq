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

#ifndef MEDIA_PROVIDER_H
#define MEDIA_PROVIDER_H

#include "Plugin.h"

class QAbstractItemModel;

namespace Kesq
{

class MediaProvider : public Plugin
{
    Q_OBJECT
public:
    MediaProvider(QObject* parent = NULL);
    virtual ~MediaProvider();

public slots:
    QAbstractItemModel* model(int i) const;
    QString mainMenuLabel(int i) const;
    int modelCount() const;
    bool isActive(int i) const;

signals:
    void activated(int i);
    void desactivated(int i);
};

}

#endif // MEDIA_PROVIDER_H

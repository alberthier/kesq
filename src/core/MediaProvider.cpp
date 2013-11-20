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

#include "MediaProvider.h"
#include <QMetaObject>

using namespace Kesq;

MediaProvider::MediaProvider(QObject* parent) :
    Plugin(parent)
{
}

MediaProvider::~MediaProvider()
{
}

QAbstractItemModel* MediaProvider::model(int i) const
{
    QAbstractItemModel* ret = NULL;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "model", Q_RETURN_ARG(QAbstractItemModel*, ret), Q_ARG(int, i));
    }
    return ret;
}

QString MediaProvider::mainMenuLabel(int i) const
{
    QString ret;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "mainMenuLabel", Q_RETURN_ARG(QString, ret), Q_ARG(int, i));
    }
    return ret;
}

int MediaProvider::modelCount() const
{
    int ret = 0;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "modelCount", Q_RETURN_ARG(int, ret));
    }
    return ret;
}

bool MediaProvider::isActive(int i) const
{
    bool ret = false;
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "isActive", Q_RETURN_ARG(bool, ret), Q_ARG(int, i));
    }
    return ret;
}

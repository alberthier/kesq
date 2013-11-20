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

#include "Display.h"
#include <QMetaObject>
#include <QTime>

using namespace Kesq;

Display::Display(QObject* parent) :
    Plugin(parent)
{
}

Display::~Display()
{
}

void Display::setModel(QAbstractItemModel* model, const QString& label)
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "setModel", Q_ARG(QAbstractItemModel*, model), Q_ARG(QString, label));
    }
}

void Display::setSelectionModel(QItemSelectionModel* selection)
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "setSelectionModel", Q_ARG(QItemSelectionModel*, selection));
    }
}

void Display::setMediaInfo(const QString& artist, const QString& album, const QString& title, const QTime& length)
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "setMediaInfo", Q_ARG(QString, artist), Q_ARG(QString, album), Q_ARG(QString, title), Q_ARG(QTime, length));
    }
}

void Display::setCurrentTime(const QTime& currentTime)
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "setCurrentTime", Q_ARG(QTime, currentTime));
    }
}

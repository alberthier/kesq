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

#include <QCoreApplication>
#include <QtPlugin>
#include <QMouseEvent>
#include <QWheelEvent>
#include "Mouse.h"

Q_EXPORT_PLUGIN2(org.kesq.mouse, Mouse);

Mouse::Mouse() :
        QObject()
{
    QCoreApplication::instance()->installEventFilter(this);
}

Mouse::~Mouse()
{
}

bool Mouse::eventFilter(QObject* watched, QEvent* event)
{
    Q_UNUSED(watched);

    switch (event->type()) {
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* me = static_cast<QMouseEvent*>(event);
            switch (me->button()) {
                case Qt::LeftButton:
                    emit select();
                    break;
                case Qt::RightButton:
                    emit back();
                    break;
                default:
                    break;
            }
            return true;
        }
        case QEvent::Wheel:
        {
            QWheelEvent* we = static_cast<QWheelEvent*>(event);
            int steps = we->delta() / 120;
            int i = 0;
            for (i = 0; i < steps; ++i) {
                emit moveUp();
            }
            for (i = 0; i > steps; --i) {
                emit moveDown();
            }
            return true;
        }
        case QEvent::MouseButtonPress:
        case QEvent::MouseMove:
        case QEvent::ContextMenu:
        case QEvent::FocusIn:
            return true;
        default:
            break;
    }
    return false;
}

void Mouse::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    Q_UNUSED(config);
    Q_UNUSED(mainDataDir);
    Q_UNUSED(userDataDir);
}

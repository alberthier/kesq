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
#include <QKeyEvent>
#include <QtPlugin>
#include "Keyboard.h"

Q_EXPORT_PLUGIN2(org.kesq.keyboard, Keyboard);

Keyboard::Keyboard() :
    QObject()
{
    QCoreApplication::instance()->installEventFilter(this);
}

Keyboard::~Keyboard()
{
}

bool Keyboard::eventFilter(QObject* watched, QEvent* event)
{
    Q_UNUSED(watched);
    switch (event->type()) {
        case QEvent::KeyPress:
        {
            QKeyEvent* ke = static_cast<QKeyEvent*>(event);
            switch (ke->key()) {
                case Qt::Key_Return:
                case Qt::Key_Enter:
                    emit select();
                    break;
                case Qt::Key_Backspace:
                    emit back();
                    break;
                case Qt::Key_Up:
                    emit moveUp();
                    break;
                case Qt::Key_Down:
                    emit moveDown();
                    break;
                case Qt::Key_Space:
                    emit togglePlayback();
                    break;
                case Qt::Key_Escape:
                    emit stop();
                    break;
                case Qt::Key_Right:
                    emit fastForward();
                    break;
                case Qt::Key_Left:
                    emit fastRewind();
                    break;
                case Qt::Key_PageUp:
                    emit previous();
                    break;
                case Qt::Key_PageDown:
                    emit next();
                    break;
                case Qt::Key_ParenLeft:
                    emit volumeDown();
                    break;
                case Qt::Key_ParenRight:
                    emit volumeUp();
                    break;
            }
            return true;
            break;
        }
        case QEvent::KeyRelease:
        case QEvent::ShortcutOverride:
        case QEvent::ContextMenu:
        case QEvent::FocusIn:
            return true;
            break;
        default:
            break;
    }
    return false;
}

void Keyboard::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    Q_UNUSED(config);
    Q_UNUSED(mainDataDir);
    Q_UNUSED(userDataDir);
}

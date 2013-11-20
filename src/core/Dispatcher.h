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

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <QPair>
#include <QStringList>
#include <QPersistentModelIndex>

class QAbstractItemModel;
class QStringListModel;
class QItemSelectionModel;
class QTimer;

namespace Kesq
{

class PluginPool;
class MediaProvider;
class MediaHandler;

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    Dispatcher(QObject* parent = NULL);
    virtual ~Dispatcher();

public slots:
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
    void activated(int i);
    void desactivated(int i);

private slots:
    void start();
    void reinitDisplay(const QString& label);
    void updateDisplay();

private:
    bool play(QStringList::Iterator it);

private:
    PluginPool* m_loader;
    QStringListModel* m_mainMenuModel;
    QAbstractItemModel* m_currentModel;
    QItemSelectionModel* m_selectionModel;
    QPersistentModelIndex m_lastSelectedIndex;
    QStringList m_history;
    QStringList::Iterator m_currentHistoryPosition;
    MediaHandler* m_currentHandler;
    QTimer* m_timer;
    QList<QPair<MediaProvider*, int> > m_mainMenuProviders;
};

}

#endif // DISPATCHER_H

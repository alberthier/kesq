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

#include "Dispatcher.h"
#include <QStringListModel>
#include <QTimer>
#include "PluginPool.h"
#include "Display.h"
#include "MediaProvider.h"
#include "MediaHandler.h"
#include "Definitions.h"

using namespace Kesq;

Dispatcher::Dispatcher(QObject* parent) :
    QObject(parent),
    m_loader(NULL),
    m_mainMenuModel(NULL),
    m_currentModel(NULL),
    m_selectionModel(NULL),
    m_currentHandler(NULL),
    m_timer(NULL)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(500);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
    QTimer::singleShot(0, this, SLOT(start()));
    m_currentHistoryPosition = m_history.end();
}

Dispatcher::~Dispatcher()
{
    delete m_selectionModel;
}

void Dispatcher::select()
{
    qDebug("Select");
    QModelIndex currentIndex = m_selectionModel->currentIndex();
    if (currentIndex.isValid()) {
        QModelIndex childIndex;
        if (m_currentModel == m_mainMenuModel) {
            int providerIndex = currentIndex.row();
            if (providerIndex < m_mainMenuProviders.count()) {
                QPair<MediaProvider*, int> p = m_mainMenuProviders[providerIndex];
                QString label = m_mainMenuModel->stringList()[providerIndex];
                m_currentModel = p.first->model(p.second);
                childIndex = m_currentModel->index(0, 0);
                reinitDisplay(label);
            }
        } else {
            childIndex = m_currentModel->index(0, 0, currentIndex);
        }
        if (childIndex.isValid()) {
            m_selectionModel->setCurrentIndex(childIndex, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Current);
            qDebug("Select - go to child");
        } else {
            QString url(m_currentModel->data(currentIndex, Qt::UserRole + 1).toString());
            m_history.erase(m_history.begin(), m_currentHistoryPosition);
            m_history.prepend(url);
            if (play(m_history.begin())) {
                m_lastSelectedIndex = currentIndex;
            }
        }
    }
}

void Dispatcher::back()
{
    qDebug("Back");
    QModelIndex currentIndex = m_selectionModel->currentIndex();
    if (currentIndex.isValid()) {
        if (currentIndex.model() != m_mainMenuModel) {
            QModelIndex parentIndex = currentIndex.parent();
            if (parentIndex.isValid()) {
                m_selectionModel->setCurrentIndex(parentIndex, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Current);
            } else {
                m_currentModel = m_mainMenuModel;
                reinitDisplay(tr("Kesq Media Center"));
            }
        }
    }
}

void Dispatcher::moveUp()
{
    qDebug("MoveUp");
    QModelIndex index = m_selectionModel->currentIndex();
    if (index.isValid()) {
        int row = index.row();
        if (row > 0) {
            m_selectionModel->setCurrentIndex(index.sibling(row - 1, 0), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Current);
        }
    }
}

void Dispatcher::moveDown()
{
    qDebug("MoveDown");
    QModelIndex index = m_selectionModel->currentIndex();
    if (index.isValid()) {
        int row = index.row();
        if (row + 1 < index.model()->rowCount(index.parent())) {
            m_selectionModel->setCurrentIndex(index.sibling(row + 1, 0), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Current);
        }
    }
}

void Dispatcher::togglePlayback()
{
    qDebug("TogglePlayback");
    if (m_currentHandler != NULL) {
        m_currentHandler->togglePlayback();
        if (m_timer->isActive()) {
            m_timer->stop();
        } else {
            m_timer->start();
        }
    }
}

void Dispatcher::stop()
{
    qDebug("Stop");
    if (m_currentHandler != NULL) {
        disconnect(m_currentHandler, SIGNAL(playbackFinished()), m_timer, SLOT(stop()));
        disconnect(m_currentHandler, SIGNAL(playbackFinished()), this, SLOT(next()));
        m_currentHandler->stop();
        m_timer->stop();
        m_currentHandler = NULL;
        updateDisplay();
    }
}

void Dispatcher::fastForward()
{
    qDebug("FastForward");
    if (m_currentHandler != NULL) {
        m_currentHandler->fastForward();
    }
}

void Dispatcher::fastRewind()
{
    qDebug("FastRewind");
    if (m_currentHandler != NULL) {
        m_currentHandler->fastRewind();
    }
}

void Dispatcher::previous()
{
    qDebug("Previous");
    if (m_currentHistoryPosition != m_history.end()) {
        ++m_currentHistoryPosition;
        if (m_currentHistoryPosition != m_history.end()) {
            play(m_currentHistoryPosition);
        }
    }
}

void Dispatcher::next()
{
    qDebug("Next");
    if (m_currentHistoryPosition != m_history.begin()) {
        --m_currentHistoryPosition;
        play(m_currentHistoryPosition);
    } else if (m_lastSelectedIndex.isValid()) {
        m_lastSelectedIndex = m_lastSelectedIndex.sibling(m_lastSelectedIndex.row() + 1, 0);
        while (m_lastSelectedIndex.isValid()) {
            m_history.prepend(m_lastSelectedIndex.model()->data(m_lastSelectedIndex, Qt::UserRole + 1).toString());
            if (play(m_history.begin())) {
                break;
            } else {
                m_lastSelectedIndex = m_lastSelectedIndex.sibling(m_lastSelectedIndex.row() + 1, 0);
            }
        }
    }
}

void Dispatcher::volumeUp()
{
    qDebug("VolumeUp");
    if (m_currentHandler != NULL) {
        int v = m_currentHandler->volume() + 5;
        if (v < 100) {
            m_currentHandler->setVolume(v);
        } else {
            m_currentHandler->setVolume(100);
        }
    }
}

void Dispatcher::volumeDown()
{
    qDebug("VolumeDown");
    if (m_currentHandler != NULL) {
        int v = m_currentHandler->volume() - 5;
        if (v > 0) {
            m_currentHandler->setVolume(v);
        } else {
            m_currentHandler->setVolume(0);
        }
    }
}

void Dispatcher::activated(int i)
{
    MediaProvider* mp = qobject_cast<MediaProvider*>(sender());
    if (mp != NULL) {
    }
}

void Dispatcher::desactivated(int i)
{
    MediaProvider* mp = qobject_cast<MediaProvider*>(sender());
    if (mp != NULL) {
    }
}

void Dispatcher::start()
{
    qWarning(tr("Starting kesq media center v%1").arg(KESQ_VERSION_STR).toAscii());
    m_loader = new PluginPool(this);
    m_loader->loadPlugins();
    QStringList items;
    QListIterator<MediaProvider*> it = m_loader->mediaProvidersIterator();
    while (it.hasNext()) {
        MediaProvider* mp = it.next();
        int max = mp->modelCount();
        for (int i = 0; i < max; ++i) {
            if (mp->isActive(i)) {
                m_mainMenuProviders.append(qMakePair(mp, i));
                items.append(mp->mainMenuLabel(i));
            }
        }
    }
    m_mainMenuModel = new QStringListModel(items, this);
    m_currentModel = m_mainMenuModel;
    reinitDisplay(tr("Kesq Media Center"));
}

void Dispatcher::reinitDisplay(const QString& label)
{
    QItemSelectionModel* oldSelectionModel = m_selectionModel;
    m_selectionModel = new QItemSelectionModel(m_currentModel);
    m_selectionModel->setCurrentIndex(m_currentModel->index(0, 0), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Current);

    QListIterator<Display*> it = m_loader->displaysIterator();
    while (it.hasNext()) {
        Display* display = it.next();
        display->setModel(m_currentModel, label);
        display->setSelectionModel(m_selectionModel);
    }
    delete oldSelectionModel;
}

void Dispatcher::updateDisplay()
{
    QString artist;
    QString album;
    QString title;
    QTime length;
    QTime currentTime;
    if (m_currentHandler != NULL) {
        artist = m_currentHandler->artist();
        album = m_currentHandler->album();
        title = m_currentHandler->title();
        length = m_currentHandler->length();
        currentTime = m_currentHandler->currentTime();
    }
    QListIterator<Display*> it = m_loader->displaysIterator();
    while (it.hasNext()) {
        Display* display = it.next();
        display->setMediaInfo(artist, album, title, length);
        display->setCurrentTime(currentTime);
    }
}

bool Dispatcher::play(QStringList::Iterator it)
{
    if (it == m_history.end()) {
        return false;
    }

    bool playing = false;
    QUrl url(*it);
    QListIterator<MediaHandler*> mhit = m_loader->mediaHandlersIterator();
    while (mhit.hasNext()) {
        MediaHandler* handler = mhit.next();
        if (handler->handles(url)) {
            stop();
            connect(handler, SIGNAL(playbackFinished()), m_timer, SLOT(stop()));
            connect(handler, SIGNAL(playbackFinished()), this, SLOT(next()));
            m_currentHandler = handler;
            m_currentHandler->setMedia(url);
            togglePlayback();
            playing = true;
            break;
        }
    }
    if (playing) {
        m_currentHistoryPosition = it;
    } else {
        m_history.erase(it);
        m_currentHistoryPosition = m_history.begin();
    }

    return playing;
}

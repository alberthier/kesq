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

#ifndef PLUGIN_POOL_H
#define PLUGIN_POOL_H

#include <QObject>
#include <QHash>

class QDomDocument;

namespace Kesq
{

class Input;
class Display;
class MediaHandler;
class MediaProvider;
class Dispatcher;

class PluginPool : public QObject
{
    Q_OBJECT
public:
    PluginPool(Dispatcher* dispatcher);
    virtual ~PluginPool();
    void loadPlugins();
    QListIterator<QObject*> pluginsIterator();
    QListIterator<Input*> inputsIterator();
    QListIterator<Display*> displaysIterator();
    QListIterator<MediaHandler*> mediaHandlersIterator();
    QListIterator<MediaProvider*> mediaProvidersIterator();

private:
    void loadPlugins(const QString& dir);
    void loadPlugin(const QString& libPath);
    bool wrapPlugin(QObject* plugin);
    void connectPlugins();
    QString mainPluginDir() const;
    QString mainDataDir() const;
    QString userPluginDir() const;
    QString userDataDir() const;

private:
    QList<QObject*> m_plugins;
    QHash<QString, QDomDocument*> m_pluginsConfig;
    QList<Input*> m_inputs;
    QList<Display*> m_displays;
    QList<MediaHandler*> m_mediaHandlers;
    QList<MediaProvider*> m_mediaProviders;
    Dispatcher* m_dispatcher;
};

}

#endif // PLUGIN_POOL_H

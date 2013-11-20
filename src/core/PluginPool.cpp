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

#include "PluginPool.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>
#include <QLibrary>
#include <QPluginLoader>
#include <QDomDocument>
#include <QTextStream>
#include "Definitions.h"
#include "Input.h"
#include "Display.h"
#include "MediaHandler.h"
#include "MediaProvider.h"
#include "Dispatcher.h"

using namespace Kesq;

PluginPool::PluginPool(Dispatcher* dispatcher) :
    QObject(dispatcher),
    m_dispatcher(dispatcher)
{
}

PluginPool::~PluginPool()
{
    QHash<QString, QDomDocument*>::Iterator it = m_pluginsConfig.begin();
    QHash<QString, QDomDocument*>::Iterator itEnd = m_pluginsConfig.end();
    for (; it != itEnd; ++it) {
        QString filePath = it.key();
        QDomDocument* doc = it.value();
        if (doc != NULL) {
            QString dataDirPath(mainDataDir());
            if (filePath.startsWith(dataDirPath)) {
                filePath.replace(0, dataDirPath.length(), userDataDir());
            }
            QFileInfo fi(filePath);
            QDir d;
            d.mkpath(fi.absolutePath());

            QFile f(filePath);
            if (f.open(QIODevice::WriteOnly)) {
                QTextStream stream(&f);
                stream << doc->toString(4);
            }
            delete doc;
        }
    }
}

void PluginPool::loadPlugins()
{
    loadPlugins(mainPluginDir());
    loadPlugins(userPluginDir());
    connectPlugins();
}

void PluginPool::loadPlugins(const QString& dir)
{
    QDir d(dir);
    QFileInfoList contents = d.entryInfoList(QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    foreach(QFileInfo fi, contents) {
        if (fi.isDir()) {
            QString path(fi.absoluteFilePath());
            loadPlugins(path);
        } else {
            if (QLibrary::isLibrary(fi.absoluteFilePath())) {
                loadPlugin(fi.absolutePath() + "/" + fi.completeBaseName());
            }
        }
    }
}

void PluginPool::loadPlugin(const QString& libPath)
{
    QPluginLoader loader(libPath);
    if (loader.load()) {
        QObject* object = loader.instance();
        object->setObjectName(loader.fileName());
        if(wrapPlugin(object)) {
            object->setParent(this);

            QFileInfo fi(libPath);
            QString configFileName(fi.baseName());
            if (configFileName.startsWith("lib")) {
                configFileName = configFileName.right(configFileName.length() - 3) + ".xml";
            }

            bool ok = false;
            QString mainPluginPath(mainPluginDir());
            QString userPluginPath(userPluginDir());
            QString subPath(fi.absolutePath());
            if (subPath.startsWith(mainPluginPath)) {
                subPath = subPath.remove(0, mainPluginPath.length() + 1);
                ok = true;
            }
            if (!ok && subPath.startsWith(userPluginPath)) {
                subPath = subPath.remove(0, userPluginPath.length() + 1);
                ok = true;
            }

            QString pluginMainDataDir(mainDataDir() + "/" + subPath);
            QString pluginUserDataDir(userDataDir() + "/" + subPath);

            QString configFilePath(pluginUserDataDir + "/" + configFileName);
            if (!QFile::exists(configFilePath)) {
                configFilePath = pluginMainDataDir + "/" + configFileName;
                if (!QFile::exists(configFilePath)) {
                    configFilePath = QString::null;
                }
            }

            QDomDocument* doc = NULL;
            if (!configFilePath.isNull()) {
                QFile file(configFilePath);
                if (file.open(QIODevice::ReadOnly)) {
                    doc = new QDomDocument("PluginConfig");
                    if (!doc->setContent(&file)) {
                        delete doc;
                        doc = NULL;
                    }
                    file.close();
                } else {
                    configFilePath = QString::null;
                }
            }
            QMetaObject::invokeMethod(object, "setConfiguration", Q_ARG(QDomDocument*, doc), Q_ARG(QString, pluginMainDataDir), Q_ARG(QString, pluginUserDataDir));
            m_plugins.append(object);
            m_pluginsConfig[configFilePath] = doc;
            qDebug(QString("Loaded %1").arg(object->objectName()).toAscii());
        } else {
            qWarning(QString("Failed to wrap %1").arg(object->objectName()).toAscii());
            delete object;
        }
    } else {
        qWarning(QString("Failed to load %1").arg(libPath).toAscii());
        qWarning(loader.errorString().toAscii());
    }
}

bool PluginPool::wrapPlugin(QObject* plugin)
{
    bool used = false;

    Input* input = new Input(this);
    if (input->wrap(plugin)) {
        m_inputs.append(input);
        used = true;
    } else {
        delete input;
    }

    Display* display = new Display(this);
    if (display->wrap(plugin)) {
        m_displays.append(display);
        used = true;
    } else {
        delete display;
    }

    MediaHandler* mediaHandler = new MediaHandler(this);
    if (mediaHandler->wrap(plugin)) {
        m_mediaHandlers.append(mediaHandler);
        used = true;
    } else {
        delete mediaHandler;
    }

    MediaProvider* mediaProvider = new MediaProvider(this);
    if (mediaProvider->wrap(plugin)) {
        m_mediaProviders.append(mediaProvider);
        used = true;
    } else {
        delete mediaProvider;
    }

    return used;
}

void PluginPool::connectPlugins()
{
    foreach(Input* input, m_inputs) {
        connect(input, SIGNAL(select()), m_dispatcher, SLOT(select()));
        connect(input, SIGNAL(back()), m_dispatcher, SLOT(back()));
        connect(input, SIGNAL(moveUp()), m_dispatcher, SLOT(moveUp()));
        connect(input, SIGNAL(moveDown()), m_dispatcher, SLOT(moveDown()));
        connect(input, SIGNAL(togglePlayback()), m_dispatcher, SLOT(togglePlayback()));
        connect(input, SIGNAL(stop()), m_dispatcher, SLOT(stop()));
        connect(input, SIGNAL(fastForward()), m_dispatcher, SLOT(fastForward()));
        connect(input, SIGNAL(fastRewind()), m_dispatcher, SLOT(fastRewind()));
        connect(input, SIGNAL(previous()), m_dispatcher, SLOT(previous()));
        connect(input, SIGNAL(next()), m_dispatcher, SLOT(next()));
        connect(input, SIGNAL(volumeUp()), m_dispatcher, SLOT(volumeUp()));
        connect(input, SIGNAL(volumeDown()), m_dispatcher, SLOT(volumeDown()));
    }
    foreach(MediaProvider* provider, m_mediaProviders) {
        connect(provider, SIGNAL(activated(int)), m_dispatcher, SLOT(activated(int)));
        connect(provider, SIGNAL(desactivated(int)), m_dispatcher, SLOT(desactivated(int)));
    }
}

QListIterator<QObject*> PluginPool::pluginsIterator()
{
    return QListIterator<QObject*>(m_plugins);
}

QListIterator<Input*> PluginPool::inputsIterator()
{
    return QListIterator<Input*>(m_inputs);
}

QListIterator<Display*> PluginPool::displaysIterator()
{
    return QListIterator<Display*>(m_displays);
}

QListIterator<MediaHandler*> PluginPool::mediaHandlersIterator()
{
    return QListIterator<MediaHandler*>(m_mediaHandlers);
}

QListIterator<MediaProvider*> PluginPool::mediaProvidersIterator()
{
    return QListIterator<MediaProvider*>(m_mediaProviders);
}

QString PluginPool::mainPluginDir() const
{
    QDir d(QCoreApplication::applicationDirPath());
    d.cdUp();
    return d.absolutePath() + "/" KESQ_MAIN_PLUGIN_DIR;
}

QString PluginPool::mainDataDir() const
{
    QDir d(QCoreApplication::applicationDirPath());
    d.cdUp();
    return d.absolutePath() + "/" KESQ_MAIN_DATA_DIR;
}

QString PluginPool::userPluginDir() const
{
    return QDir::home().absolutePath() + "/" KESQ_USER_PLUGIN_DIR;
}

QString PluginPool::userDataDir() const
{
    return QDir::home().absolutePath() + "/" KESQ_USER_DATA_DIR;
}

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

#include "FileSystem.h"
#include <QtPlugin>
#include <QDomDocument>
#include <QDomElement>
#include <QDir>
#include <QFile>
#include "FileSystemModel.h"
#include "MediaIconProvider.h"

Q_EXPORT_PLUGIN2(org.kesq.filesystem, FileSystem);

FileSystem::FileSystem() :
    QObject(),
    m_model(NULL)
{
    m_model = new FileSystemModel(this);
}

FileSystem::~FileSystem()
{
}

void FileSystem::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    Q_UNUSED(mainDataDir);
    Q_UNUSED(userDataDir);

    QString rootPath;
    QIcon folderIcon;
    QIcon defaultFileIcon;
    QHash<QString, QIcon> icons;
    if (config != NULL) {
        QDomElement elt = config->documentElement();
        if (!elt.isNull() && elt.tagName() == "FileSystem") {
            for (QDomNode n = elt.firstChild(); !n.isNull(); n = n.nextSibling()) {
                if (n.isElement()) {
                    QDomElement e = n.toElement();
                    if (e.tagName() == "RootPath") {
                        QString p(e.attribute("value"));
                        if (QFile::exists(p)) {
                            rootPath = p;
                        }
                    }
                    if (e.tagName() == "Icons") {
                        for (QDomNode n2 = e.firstChild(); !n2.isNull(); n2 = n2.nextSibling()) {
                            if (n2.isElement()) {
                                QDomElement e2 = n2.toElement();
                                QString iconName(e2.attribute("icon"));
                                QString iconPath(userDataDir + "/" + iconName);
                                if (!QFile::exists(iconPath)) {
                                    iconPath = mainDataDir + "/" + iconName;
                                    if (!QFile::exists(iconPath)) {
                                        iconPath = QString::null;
                                    }
                                }
                                if (e2.tagName() == "Folder") {
                                    folderIcon = QIcon(iconPath);
                                } else if (e2.tagName() == "DefaultFile") {
                                    defaultFileIcon = QIcon(iconPath);
                                } else if (e2.tagName() == "File") {
                                    icons[e2.attribute("type")] = QIcon(iconPath);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (rootPath.isEmpty()) {
        rootPath = QDir::rootPath();
    }
    MediaIconProvider* iconProvider = new MediaIconProvider();
    iconProvider->setFolderIcon(folderIcon);
    iconProvider->setDefaultFileIcon(defaultFileIcon);
    iconProvider->setFileTypeIcons(icons);
    m_model->setIconProvider(iconProvider);
    m_model->setRootPath(rootPath);
}

QAbstractItemModel* FileSystem::model(int i) const
{
    if (i == 0) {
        return m_model;
    }
    return NULL;
}

QString FileSystem::mainMenuLabel(int i) const
{
    if (i == 0) {
        return tr("Fichiers");
    }
    return NULL;
}

int FileSystem::modelCount() const
{
    return 1;
}

bool FileSystem::isActive(int i) const
{
    if (i == 0) {
        return true;
    }
    return false;
}


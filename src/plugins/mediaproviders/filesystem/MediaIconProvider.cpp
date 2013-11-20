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

#include "MediaIconProvider.h"

MediaIconProvider::MediaIconProvider() :
    QFileIconProvider()
{
}

MediaIconProvider::~MediaIconProvider()
{
}

QIcon MediaIconProvider::icon(IconType type) const
{
    switch (type) {
        case QFileIconProvider::Folder:
            if (!m_folderIcon.isNull()) {
                return m_folderIcon;
            }
            break;
        case QFileIconProvider::File:
            if (!m_defaultFileIcon.isNull()) {
                return m_defaultFileIcon;
            }
            break;
        default:
            break;
    }
    return QFileIconProvider::icon(type);
}

QIcon MediaIconProvider::icon(const QFileInfo& info) const
{
    QString ext(info.completeSuffix().toLower());
    while (!ext.isEmpty()) {
        QHash<QString, QIcon>::ConstIterator it = m_fileTypeIcons.find(ext);
        if (it != m_fileTypeIcons.end()) {
            return it.value();
        }
        QFileInfo fi(ext);
        ext = fi.completeSuffix();
    }
    return QFileIconProvider::icon(info);
}

void MediaIconProvider::setFolderIcon(const QIcon& i)
{
    m_folderIcon = i;
}

void MediaIconProvider::setDefaultFileIcon(const QIcon& i)
{
    m_defaultFileIcon = i;
}

void MediaIconProvider::setFileTypeIcons(const QHash<QString, QIcon>& map)
{
    m_fileTypeIcons = map;
}

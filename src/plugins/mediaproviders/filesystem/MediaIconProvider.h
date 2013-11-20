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

#ifndef MEDIA_ICON_PROVIDER_H
#define MEDIA_ICON_PROVIDER_H

#include <QFileIconProvider>
#include <QHash>
#include <QIcon>

class MediaIconProvider : public QFileIconProvider
{
public:
    MediaIconProvider();
    virtual ~MediaIconProvider();
    virtual QIcon icon(IconType type) const;
    virtual QIcon icon(const QFileInfo& info) const;
    void setFolderIcon(const QIcon& i);
    void setDefaultFileIcon(const QIcon& i);
    void setFileTypeIcons(const QHash<QString, QIcon>& map);

private:
    QHash<QString, QIcon> m_fileTypeIcons;
    QIcon m_folderIcon;
    QIcon m_defaultFileIcon;
};

#endif // MEDIA_ICON_PROVIDER_H

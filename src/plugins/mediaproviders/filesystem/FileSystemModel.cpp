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

#include "FileSystemModel.h"

FileSystemModel::FileSystemModel(QObject* parent) :
    QDirModel(parent)
{
}

FileSystemModel::~FileSystemModel()
{
}

void FileSystemModel::setRootPath(const QString& path)
{
    m_rootIndex = QDirModel::index(path);
}

QVariant FileSystemModel::data(const QModelIndex& index, int role) const
{
    if (role == QDirModel::FilePathRole) {
        QString url("file://" + QDirModel::data(index, role).toString());
        return QVariant(url);
    }
    return QDirModel::data(index, role);
}

QModelIndex FileSystemModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return QDirModel::index(row, column, m_rootIndex);
    }
    return QDirModel::index(row, column, parent);
}

QModelIndex FileSystemModel::parent(const QModelIndex& i) const
{
    QModelIndex p(QDirModel::parent(i));
    if (p == m_rootIndex) {
        return QModelIndex();
    }
    return p;
}

int FileSystemModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return QDirModel::rowCount(m_rootIndex);
    }
    return QDirModel::rowCount(parent);
}

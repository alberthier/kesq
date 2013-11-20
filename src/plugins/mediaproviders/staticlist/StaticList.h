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

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include <QObject>
#include <QPair>

class QDomDocument;
class QDomElement;
class QAbstractItemModel;
class QStandardItemModel;
class QStandardItem;

class StaticList : public QObject
{
    Q_OBJECT
public:
    StaticList();
    virtual ~StaticList();

public slots:
    void setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir);
    QAbstractItemModel* model(int i) const;
    QString mainMenuLabel(int i) const;
    int modelCount() const;
    bool isActive(int i) const;

signals:
    void activated(int i);
    void desactivated(int i);

private:
    void loadModel(const QDomElement& elt, QStandardItem* parent);

private:
    QList<QPair<QString, QStandardItemModel*> > m_models;
};

#endif // STATIC_LIST_H

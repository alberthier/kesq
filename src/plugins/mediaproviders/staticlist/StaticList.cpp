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

#include "StaticList.h"
#include <QtPlugin>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QUrl>

Q_EXPORT_PLUGIN2(org.kesq.staticlist, StaticList);

StaticList::StaticList() :
    QObject()
{
}

StaticList::~StaticList()
{
}

void StaticList::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    Q_UNUSED(mainDataDir);
    Q_UNUSED(userDataDir);

    if (config != NULL) {
        QDomElement root(config->documentElement());
        if (root.tagName() == "StaticList") {
            for (QDomNode n(root.firstChild()); !n.isNull(); n = n.nextSibling()) {
                if (n.isElement()) {
                    QDomElement e(n.toElement());
                    QStandardItemModel* model = new QStandardItemModel(this);
                    loadModel(e, model->invisibleRootItem());
                    m_models.append(qMakePair(e.attribute("label"), model));
                }
            }
        }
    }
}

QAbstractItemModel* StaticList::model(int i) const
{
    if (i < m_models.count()) {
        return m_models[i].second;
    }
    return NULL;
}

QString StaticList::mainMenuLabel(int i) const
{
    if (i < m_models.count()) {
        return m_models[i].first;
    }
    return QString::null;
}

int StaticList::modelCount() const
{
    return m_models.count();
}

bool StaticList::isActive(int i) const
{
    Q_UNUSED(i);
    return true;
}

void StaticList::loadModel(const QDomElement& elt, QStandardItem* parent)
{
    for (QDomNode n(elt.firstChild()); !n.isNull(); n = n.nextSibling()) {
        if (n.isElement()) {
            QDomElement e(n.toElement());
            if (e.tagName() == "Item") {
                QStandardItem* item = new QStandardItem(e.attribute("label"));
                item->setData(e.attribute("provides"), Qt::UserRole + 1);
                parent->appendRow(item);
            } else if (e.tagName() == "Menu") {
                QStandardItem* item = new QStandardItem(e.attribute("label"));
                parent->appendRow(item);
                loadModel(e, item);
            }
        }
    }
}

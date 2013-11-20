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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>

class QDomDocument;

namespace Kesq
{

class Plugin : public QObject
{
    Q_OBJECT
public:
    Plugin(QObject* parent = NULL);
    virtual ~Plugin();

    bool wrap(QObject* plugin);

public slots:
    void setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir);

private:
    bool checkMethod(const QMetaMethod* method, const QMetaObject* candidate, QList<QByteArray>* missingList);

protected:
    QObject* m_wrapped;
};

}

#endif // PLUGIN_H

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

#ifndef QLIRCINPUT_H
#define QLIRCINPUT_H

#include <QObject>

class QSocketNotifier;
typedef struct lirc_config;

class QlircInput : public QObject
{
    Q_OBJECT
public:
    static QlircInput* instance();
    bool init(const QString& configFilePath = QString::null);

signals:
    void keyPressed(const QString& id);

private slots:
    void readKey(int d);

private:
    QlircInput();
    virtual ~QlircInput();
    void reset();
    static void cleanup();

private:
    QSocketNotifier* m_notifier;
    struct lirc_config* m_config;
    static QlircInput* m_instance;
};

#endif // QLIRCINPUT_H

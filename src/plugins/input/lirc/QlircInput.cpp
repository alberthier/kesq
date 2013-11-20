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

#include "QlircInput.h"
#include <QSocketNotifier>
#include <QCoreApplication>
#include <QFileInfo>
#include <lirc/lirc_client.h>

QlircInput* QlircInput::m_instance = NULL;

QlircInput::QlircInput() :
    QObject(),
    m_notifier(NULL),
    m_config(NULL)
{
}

QlircInput::~QlircInput()
{
    reset();
}

QlircInput* QlircInput::instance()
{
    if (m_instance == NULL) {
        m_instance = new QlircInput();
        qAddPostRoutine(QlircInput::cleanup);
    }
    return m_instance;
}

bool QlircInput::init(const QString& configFilePath)
{
    reset();

    QFileInfo executable(QCoreApplication::instance()->applicationFilePath());

    int d = lirc_init(executable.fileName().toAscii().data(), 0);
    if (d != -1) {
        if (lirc_readconfig(configFilePath.toAscii().data(), &m_config, NULL) == 0) {
            m_notifier = new QSocketNotifier(d, QSocketNotifier::Read, this);
            connect(m_notifier, SIGNAL(activated(int)), this, SLOT(readKey(int)));
            return true;
        }
        lirc_deinit();
    }
    return false;
}

void QlircInput::readKey(int d)
{
    Q_UNUSED(d);

    char *code = NULL;

    if (lirc_nextcode(&code) == 0)
    {
        if(code != NULL) {
            char *c = NULL;
            int ret = lirc_code2char(m_config, code, &c);
            while(ret == 0 && c != NULL) {
                emit keyPressed(QString(c));
                ret = lirc_code2char(m_config, code, &c);
            }
            free(code);
        }
    }
}

void QlircInput::reset()
{
    lirc_deinit();
    lirc_freeconfig(m_config);
    m_config = NULL;
    delete m_notifier;
    m_notifier = NULL;
}

void QlircInput::cleanup()
{
    if (m_instance != NULL) {
        delete m_instance;
        m_instance = NULL;
    }
}

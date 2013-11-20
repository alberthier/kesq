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

#include "Plugin.h"
#include <QMetaObject>
#include <QMetaMethod>

using namespace Kesq;

Plugin::Plugin(QObject* parent) :
    QObject(parent),
    m_wrapped(NULL)
{
}

Plugin::~Plugin()
{
}

bool Plugin::wrap(QObject* plugin)
{
    const QMetaObject* interfaceMetaObject = metaObject();
    const QMetaObject* wrappedMetaObject = plugin->metaObject();

    int max = interfaceMetaObject->methodCount();
    QObject o;
    int min = o.metaObject()->methodCount();
    int nbInterfaceMethods = 0;
    QList<QByteArray> missingSignals;
    QList<QByteArray> missingSlots;
    QByteArray signalCode(QByteArray::number(QSIGNAL_CODE));
    for (int i = min; i < max; ++i) {
        QMetaMethod method(interfaceMetaObject->method(i));
        switch (method.methodType()) {
            case QMetaMethod::Signal:
            {
                ++nbInterfaceMethods;
                if (checkMethod(&method, wrappedMetaObject, &missingSignals)) {
                    QByteArray connectSignature = signalCode + method.signature();
                    connect(plugin, connectSignature, this, connectSignature);
                }
                break;
            }
            case QMetaMethod::Slot:
            {
                ++nbInterfaceMethods;
                checkMethod(&method, wrappedMetaObject, &missingSlots);
                break;
            }
            default:
                break;
        }
    }
    bool ok = missingSignals.isEmpty() && missingSlots.isEmpty();
    if (ok) {
        m_wrapped = plugin;
    } else {
        int missingMethods = missingSignals.count() + missingSlots.count();
        if (missingMethods > 0 && missingMethods < nbInterfaceMethods - 1) {
            // Interface parially defined.
            qWarning(tr("%1 only partially implements interface %2.").arg(plugin->objectName()).arg(interfaceMetaObject->className()).toAscii());
            if (!missingSignals.isEmpty()) {
                qWarning(tr("\tMissing signals:").toAscii());
                foreach(const char* signal, missingSignals) {
                    QString s("\t\t");
                    s += signal;
                    qWarning(s.toAscii());
                }
            }
            if (!missingSlots.isEmpty()) {
                qWarning(tr("Missing slots:").toAscii());
                foreach(const char* slot, missingSlots) {
                    QString s("\t\t");
                    s += slot;
                    qWarning(s.toAscii());
                }
            }
        }
    }
    return ok;
}

void Plugin::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    if (m_wrapped != NULL) {
        QMetaObject::invokeMethod(m_wrapped, "setConfiguration", Q_ARG(QDomDocument*, config), Q_ARG(QString, mainDataDir), Q_ARG(QString, userDataDir));
    }
}

bool Plugin::checkMethod(const QMetaMethod* method, const QMetaObject* candidate, QList<QByteArray>* missingList)
{
    bool ok = false;
    int index = -1;
    switch (method->methodType()) {
        case QMetaMethod::Signal:
            index = candidate->indexOfSignal(method->signature());
            break;
        case QMetaMethod::Slot:
            index = candidate->indexOfSlot(method->signature());
            break;
        default:
            break;
    }
    if (index == -1) {
        ok = false;
    } else {
        QByteArray returnType(candidate->method(index).typeName());
        ok = returnType == method->typeName();
    }
    if (!ok) {
        QByteArray returnType(method->typeName());
        if (returnType.isEmpty()) {
            returnType = "void";
        }
        missingList->append(returnType + " " + method->signature());
    }
    return ok;
}

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

#include "Gui.h"
#include <QtPlugin>
#include <QWidget>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include <QUiLoader>
#include <QTime>
#include <QListView>
#include <QLabel>
#include <QSlider>
#include <QApplication>

Q_EXPORT_PLUGIN2(org.kesq.gui, Gui);

Gui::Gui() :
    QObject(),
    m_widget(NULL),
    m_fullscreen(false),
    m_listView(NULL),
    m_title(NULL),
    m_parentTitle(NULL),
    m_artistAlbum(NULL),
    m_currentTime(NULL),
    m_totalTime(NULL),
    m_image(NULL),
    m_timeSlider(NULL)
{
    QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
}

Gui::~Gui()
{
    delete m_widget;
}

void Gui::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    QString themeDir;
    if (config != NULL) {
        QDomElement elt = config->documentElement();
        if (!elt.isNull() && elt.tagName() == "Gui") {
            for (QDomNode n = elt.firstChild(); !n.isNull(); n = n.nextSibling()) {
                if (n.isElement()) {
                    QDomElement e = n.toElement();
                    if (e.tagName() == "Theme") {
                        QString themeName(e.attribute("name"));
                        themeDir = userDataDir + "/" + themeName;
                        if (!QFile::exists(themeDir)) {
                            themeDir = mainDataDir + "/" + themeName;
                            if (!QFile::exists(themeDir)) {
                                themeDir = QString::null;
                            }
                        }
                    } else if (e.tagName() == "Fullscreen") {
                        m_fullscreen = e.attribute("value") == "true";
                    }
                }
            }
        }
    }
    if (!themeDir.isNull()) {
        loadTheme(themeDir);
    }
}

void Gui::setModel(QAbstractItemModel* model, const QString& label)
{
    if (m_listView != NULL) {
        m_listView->setModel(model);
    }
    m_label = label;
    if (m_parentTitle != NULL) {
        m_parentTitle->setText(m_label);
        m_parentTitle->show();
    }
}

void Gui::setSelectionModel(QItemSelectionModel* selection)
{
    if (m_listView != NULL) {
        QItemSelectionModel* previous = m_listView->selectionModel();
        if (previous != NULL) {
            disconnect(previous, SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(currentItemChanged(const QModelIndex&, const QModelIndex&)));
        }
        m_listView->setSelectionModel(selection);
        if (selection != NULL) {
            connect(selection, SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(currentItemChanged(const QModelIndex&, const QModelIndex&)));
        }
    }
}

void Gui::setMediaInfo(const QString& artist, const QString& album, const QString& title, const QTime& length)
{
    if (m_artistAlbum != NULL) {
        if (!artist.isNull() && !album.isNull()) {
            m_artistAlbum->setText(tr("<b>%1</b> - <b>%2</b>").arg(artist).arg(album));
            m_artistAlbum->show();
        } else if (!artist.isNull()) {
            m_artistAlbum->setText(tr("<b>%1</b>").arg(artist));
            m_artistAlbum->show();
        } else if (!album.isNull()) {
            m_artistAlbum->setText(tr("<b>%1</b>").arg(album));
            m_artistAlbum->show();
        } else {
            m_artistAlbum->setText(QString::null);
            m_artistAlbum->hide();
        }
    }
    if (m_title != NULL) {
        if (!title.isNull()) {
            m_title->setText(title);
            m_title->show();
        } else {
            m_title->setText(QString::null);
            m_title->hide();
        }
    }
    if (m_totalTime != NULL) {
        if (length.isValid()) {
            QString format("m:ss");
            if (length.hour() != 0) {
                format = "h:mm:ss";
            }
            m_totalTime->setText(length.toString(format));
            m_totalTime->show();
            QTime t(0, 0, 0);
            m_timeSlider->setMaximum(t.secsTo(length));
            m_timeSlider->show();
        } else {
            m_totalTime->setText(QString::null);
            m_totalTime->hide();
            m_timeSlider->setMaximum(0);
            m_timeSlider->hide();
        }
    }
}

void Gui::setCurrentTime(const QTime& currentTime)
{
    if (m_currentTime != NULL) {
        if (currentTime.isValid()) {
            QString format("m:ss");
            if (currentTime.hour() != 0) {
                format = "h:mm:ss";
            }
            m_currentTime->setText(currentTime.toString(format));
            m_currentTime->show();
            QTime t(0, 0, 0);
            m_timeSlider->setValue(t.secsTo(currentTime));
        } else {
            m_currentTime->setText(QString::null);
            m_currentTime->hide();
            m_timeSlider->setValue(0);
        }
    }
}

void Gui::loadTheme(const QString& themeDir)
{
    QString uiPath(themeDir + "/mainwindow.ui");
    QString cssPath(themeDir + "/mainwindow.css");

    QUiLoader loader;
    QFile uiFile(uiPath);
    if (uiFile.open(QFile::ReadOnly)) {
        m_widget = loader.load(&uiFile);
        uiFile.close();
        if (m_widget != NULL) {
            QFile cssFile(cssPath);
            if (cssFile.open(QFile::ReadOnly)) {
                QTextStream stream(&cssFile);
                QString css(stream.readAll());
                cssFile.close();
                m_widget->setStyleSheet(css);
            }
            m_listView = qFindChild<QListView*>(m_widget, "listView");
            m_title = qFindChild<QLabel*>(m_widget, "title");
            if (m_title != NULL) {
                m_title->hide();
                m_title->setText(QString::null);
            }
            m_parentTitle = qFindChild<QLabel*>(m_widget, "parentTitle");
            if (m_parentTitle != NULL) {
                m_parentTitle->hide();
                m_parentTitle->setText(QString::null);
            }
            m_artistAlbum = qFindChild<QLabel*>(m_widget, "artistAlbum");
            if (m_artistAlbum != NULL) {
                m_artistAlbum->hide();
                m_artistAlbum->setText(QString::null);
            }
            m_currentTime = qFindChild<QLabel*>(m_widget, "currentTime");
            if (m_currentTime != NULL) {
                m_currentTime->hide();
                m_currentTime->setText(QString::null);
            }
            m_totalTime = qFindChild<QLabel*>(m_widget, "totalTime");
            if (m_totalTime != NULL) {
                m_totalTime->hide();
                m_totalTime->setText(QString::null);
            }
            m_image =  qFindChild<QLabel*>(m_widget, "image");
            m_timeSlider = qFindChild<QSlider*>(m_widget, "timeSlider");
            if (m_timeSlider != NULL) {
                m_timeSlider->hide();
                m_timeSlider->setMaximum(0);
                m_timeSlider->setValue(0);
            }
            if (m_fullscreen) {
                m_widget->showFullScreen();
            } else {
                m_widget->show();
            }
        }
    }
}

void Gui::currentItemChanged(const QModelIndex& current, const QModelIndex& previous)
{
    if (m_listView != NULL && current.parent() != previous.parent()) {
        m_listView->setRootIndex(current.parent());
        m_listView->scrollTo(current);
        if (m_image != NULL) {
            m_image->setPixmap(current.parent().data(Qt::DecorationRole).value<QIcon>().pixmap(QSize(128, 128))); //(m_image->width(), m_image->height()));
        }
        if (m_parentTitle != NULL) {
            QString label(current.parent().data(Qt::DisplayRole).toString());
            if (!label.isNull()) {
                m_parentTitle->setText(label);
            } else {
                m_parentTitle->setText(m_label);
            }
            m_parentTitle->show();
        }
    }
}

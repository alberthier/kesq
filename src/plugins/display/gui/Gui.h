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

#ifndef GUI_H
#define GUI_H

#include <QObject>

class QAbstractItemModel;
class QItemSelectionModel;
class QModelIndex;
class QDomDocument;
class QTime;
class QWidget;
class QListView;
class QLabel;
class QSlider;

class Gui : public QObject
{
    Q_OBJECT
public:
    Gui();
    virtual ~Gui();

public slots:
    void setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir);
    void setModel(QAbstractItemModel* model, const QString& label);
    void setSelectionModel(QItemSelectionModel* selection);
    void setMediaInfo(const QString& artist, const QString& album, const QString& title, const QTime& length);
    void setCurrentTime(const QTime& currentTime);

private:
    void loadTheme(const QString& themeDir);

private slots:
    void currentItemChanged(const QModelIndex& current, const QModelIndex& previous);

private:
    QWidget* m_widget;
    bool m_fullscreen;
    QListView* m_listView;
    QLabel* m_title;
    QLabel* m_parentTitle;
    QLabel* m_artistAlbum;
    QLabel* m_currentTime;
    QLabel* m_totalTime;
    QLabel* m_image;
    QSlider* m_timeSlider;
    QString m_label;
};

#endif // GUI_H

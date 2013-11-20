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

#ifndef MPLAYER_H
#define MPLAYER_H

#include <QObject>
#include <QStringList>
#include <QUrl>
#include <QTime>

class QDomDocument;
class QProcess;
class QWidget;

class MPlayer : public QObject
{
    Q_OBJECT

public:
    MPlayer();
    virtual ~MPlayer();

public slots:
    void setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir);
    bool handles(const QUrl& media);
    void setMedia(const QUrl& media);
    void togglePlayback();
    void stop();
    void fastForward();
    void fastRewind();
    int volume();
    void setVolume(int v);
    QString artist() const;
    QString album() const;
    QString title() const;
    QTime length() const;
    QTime currentTime() const;

signals:
    void playbackFinished();

private:
    bool isAudio(const QUrl& media);
    bool isVideo(const QUrl& media);

private slots:
    void readStandardOutput();
    void finished();
    void getTimePosRequest();

private:
    QWidget* m_videoWidget;
    QString m_mplayerPath;
    QStringList m_audioTypes;
    QStringList m_videoTypes;
    QProcess* m_process;
    QUrl m_url;
    int m_volume;
    bool m_paused;
    QString m_artist;
    QString m_album;
    QString m_title;
    QTime m_length;
    QTime m_currentTime;
};

#endif // MPLAYER_H

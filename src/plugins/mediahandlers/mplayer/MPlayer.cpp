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

#include "MPlayer.h"
#include <QtPlugin>
#include <QWidget>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QProcess>
#include <QRegExp>
#include <QFileInfo>
#include <QTimer>

Q_EXPORT_PLUGIN2(org.kesq.mplayer, MPlayer);

MPlayer::MPlayer() :
    QObject(),
    m_videoWidget(NULL),
    m_process(NULL),
    m_volume(50),
    m_paused(false)
{
    /*m_videoWidget = new QWidget();
    m_videoWidget->setFocusPolicy(Qt::NoFocus);
    m_videoWidget->setWindowState(Qt::WindowFullScreen);*/
}

MPlayer::~MPlayer()
{
    stop();
    //delete m_videoWidget;
}

void MPlayer::setConfiguration(QDomDocument* config, const QString& mainDataDir, const QString& userDataDir)
{
    Q_UNUSED(mainDataDir);
    Q_UNUSED(userDataDir);

    if (config != NULL) {
        QDomElement root(config->documentElement());
        if (root.tagName() == "MPlayerConfig") {
            for (QDomNode n(root.firstChild()); !n.isNull(); n = n.nextSibling()) {
                if (n.isElement()) {
                    QDomElement e(n.toElement());
                    if (e.tagName() == "Executable") {
                        m_mplayerPath = e.text();
                    } else if (e.tagName() == "AudioFormats") {
                        for (QDomNode an(e.firstChild()); !an.isNull(); an = an.nextSibling()) {
                            if (an.isElement()) {
                                QDomElement ae(an.toElement());
                                if (ae.tagName() == "Type") {
                                    m_audioTypes.append(ae.text());
                                }
                            }
                        }
                    } else if (e.tagName() == "VideoFormats") {
                        for (QDomNode an(e.firstChild()); !an.isNull(); an = an.nextSibling()) {
                            if (an.isElement()) {
                                QDomElement ae(an.toElement());
                                if (ae.tagName() == "Type") {
                                    m_videoTypes.append(ae.text());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool MPlayer::handles(const QUrl& media)
{
    if (isAudio(media)) {
        return true;
    }
    return isVideo(media);
}

void MPlayer::setMedia(const QUrl& media)
{
    m_url = media;
}

void MPlayer::togglePlayback()
{
    if (m_process == NULL) {
        bool audio = isAudio(m_url);
        bool video = isVideo(m_url);
        if (audio || video) {
            m_process = new QProcess(this);
            QStringList args;
            args.append("-noconsolecontrols");
            args.append("-slave");
            args.append("-quiet");
            if (m_url.scheme() == "file") {
                args.append(m_url.path());
            } else if (m_url.scheme() == "dvd") {
                args.append("dvd://");
            } else if (m_url.scheme() == "cdda") {
                args.append("cdda://");
            } else if (m_url.scheme() == "cddb") {
                args.append("cddb://");
            } else {
                args.append(m_url.toString());
            }
            connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished()));
            if (audio) {
                connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()));
            } else if (video) {
                QFileInfo fi(m_url.path());
                m_title = fi.completeBaseName();
                /*args.append("-wid");
                args.append(QString::number(m_videoWidget->winId()));
                m_videoWidget->show();*/
                args.append("-fs");
            }
            m_process->setReadChannelMode(QProcess::MergedChannels);
            m_process->setReadChannel(QProcess::StandardOutput);
            m_process->start(m_mplayerPath, args);
            if (!m_process->waitForStarted()) {
                m_process->kill();
                delete m_process;
                m_process = NULL;
            } else {
                setVolume(m_volume);
                m_process->write("get_time_length\n");
                getTimePosRequest();
            }
        }
    } else {
        if (!m_paused) {
            m_process->write("osd 4\n");
            m_process->write("pause\n");
            m_paused = true;
        } else {
            m_process->write("osd 1\n");
            m_paused = false;
        }
    }
}

void MPlayer::stop()
{
    if (m_process != NULL) {
        m_process->write("quit\n");
        m_process->waitForFinished();
    }
}

void MPlayer::fastForward()
{
    if (m_process != NULL) {
        m_process->write("seek +30 0\n");
    }
}

void MPlayer::fastRewind()
{
    if (m_process != NULL) {
        m_process->write("seek -30 0\n");
    }
}

int MPlayer::volume()
{
    return m_volume;
}

void MPlayer::setVolume(int v)
{
    if (m_process != NULL) {
        QByteArray cmd("volume ");
        cmd += QByteArray::number(v) + " 1\n";
        m_process->write(cmd);
    }
    m_volume = v;
}

QString MPlayer::artist() const
{
    return m_artist;
}

QString MPlayer::album() const
{
    return m_album;
}

QString MPlayer::title() const
{
    return m_title;
}

QTime MPlayer::length() const
{
    return m_length;
}

QTime MPlayer::currentTime() const
{
    return m_currentTime;
}

bool MPlayer::isAudio(const QUrl& media)
{
    QString m(media.toString());
    foreach (const QString& type, m_audioTypes) {
        QRegExp regexp(type, Qt::CaseInsensitive, QRegExp::Wildcard);
        if (regexp.exactMatch(m)) {
            return true;
        }
    }
    return false;
}

bool MPlayer::isVideo(const QUrl& media)
{
    QString m(media.toString());
    foreach (const QString& type, m_videoTypes) {
        QRegExp regexp(type, Qt::CaseInsensitive, QRegExp::Wildcard);
        if (regexp.exactMatch(m)) {
            return true;
        }
    }
    return false;
}

void MPlayer::readStandardOutput()
{
    if (m_process != NULL) {
        while (m_process->canReadLine()) {
            QString line(m_process->readLine());
            if (line.startsWith(" Artist: ")) {
                m_artist = line.right(line.length() - 9);
            } else if (line.startsWith(" Album: ")) {
                m_album = line.right(line.length() - 8).trimmed();
            } else if (line.startsWith(" Title: ")) {
                m_title = line.right(line.length() - 8).trimmed();
            } else if (line.startsWith(" Name: ")) {
                m_title = line.right(line.length() - 7).trimmed();
            } else if (line.startsWith("ANS_LENGTH=")) {
                QString tmp(line.right(line.length() - 11).trimmed());
                bool ok = false;
                float t = tmp.toFloat(&ok);
                if (ok) {
                    m_length.setHMS(0, 0, 0);
                    m_length = m_length.addMSecs((int) (t * 1000.0));
                } else {
                    m_length = QTime();
                }
            } else if (line.startsWith("ANS_TIME_POSITION=")) {
                QString tmp(line.right(line.length() - 18).trimmed());
                bool ok = false;
                float t = tmp.toFloat(&ok);
                if (ok) {
                    m_currentTime.setHMS(0, 0, 0);
                    m_currentTime = m_currentTime.addMSecs((int) (t * 1000.0));
                } else {
                    m_currentTime = QTime();
                }
                QTimer::singleShot(100, this, SLOT(getTimePosRequest()));
            }
        }
    }
}

void MPlayer::finished()
{
    m_process->deleteLater();
    m_process = NULL;
    m_paused = false;
    m_artist = QString::null;
    m_album = QString::null;
    m_title = QString::null;
    m_length = QTime();
    m_currentTime = QTime();
    //m_videoWidget->hide();
    emit playbackFinished();
}

void MPlayer::getTimePosRequest()
{
    if (m_process != NULL) {
        m_process->write("get_time_pos\n");
    }
}

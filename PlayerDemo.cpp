/**
 * @file
 * @brief Source file for Demo QtPlayer application
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @ref License
 */

/* LICENSE
 *
 * Copyright (c) 2008-2019 OpenShot Studios, LLC
 * <http://www.openshotstudios.com/>. This file is part of
 * OpenShot Library (libopenshot), an open-source project dedicated to
 * delivering high quality video editing and animation solutions to the
 * world. For more information visit <http://www.openshot.org/>.
 *
 * OpenShot Library (libopenshot) is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * OpenShot Library (libopenshot) is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenShot Library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdio.h"
#include <QtPlayer.h>
#include <FFmpegReader.h>
#include <Timeline.h>
#include <PlayerDemo.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>


PlayerDemo::PlayerDemo(QWidget *parent)
    : QWidget(parent)
    , vbox(new QVBoxLayout(this))
    , menu(new QMenuBar(this))
    , video(new VideoRenderWidget(this))
    , player(new openshot::QtPlayer(video->GetRenderer()))
{
    setWindowTitle("OpenShot Player");

    menu->setNativeMenuBar(false);

    QAction *action = NULL;
    action = menu->addAction("Choose File");
    connect(action, SIGNAL(triggered(bool)), this, SLOT(open(bool)));

    vbox->addWidget(menu, 0);
    vbox->addWidget(video, 1);

    vbox->setMargin(0);
    vbox->setSpacing(0);
    resize(600, 480);

    // Accept keyboard event
    setFocusPolicy(Qt::StrongFocus);

    m_timeline = new openshot::Timeline(1280, 720,
                          openshot::Fraction(25, 1), 44100,
                          2, openshot::ChannelLayout::LAYOUT_STEREO);

    player->Reader(m_timeline);

	m_positionThread.reset(new std::thread(loopPositionThread, this));
}

void PlayerDemo::setPosition(int pos) {
    if (player) {
        int64_t position = pos * m_frameNumber / 100;
        qDebug()<<"setPosition:"<<position<<", frame number:"<<m_frameNumber<<endl;
        player->Seek(position);
    }
}

void PlayerDemo::loopPositionThread(PlayerDemo *p) {
	PlayerDemo *pThis = (PlayerDemo*)p;
	if(!pThis){
		std::cout<<"failed error"<<std::endl;
		return;
	}

	pThis->m_stop_positionThread = false;

	uint64 current_frame = 0;
	openshot::PlaybackMode current_mode = openshot::PLAYBACK_STOPPED;
	while (!pThis->m_stop_positionThread && pThis->player) {
		 if (current_frame != pThis->player->Position()) {
             current_frame = pThis->player->Position();
			 //emit PositionChanged(current_frame);
			 std::cout<<"current_frame:"<<current_frame<<std::endl;
			 QCoreApplication::processEvents();
		 }

		 if (pThis->player->Mode() != current_mode) {
             current_mode = pThis->player->Mode();
			 std::cout<<"current_mode:"<<current_mode<<std::endl;
             //emit ModeChanged(current_mode);
		 }

#ifdef __APPLE__
         usleep(50000);
#else
		 Sleep(50);
#endif
         QCoreApplication::processEvents();
	}
}

PlayerDemo::~PlayerDemo()
{
	m_stop_positionThread = true;
	m_positionThread.reset();
    if (m_timeline) {
        m_timeline->Close();
        delete m_timeline;
        m_timeline = nullptr;
    }

	if (vbox) {
		delete vbox;
		vbox = nullptr;
	}

    if (menu) {
		delete menu;
		menu = nullptr;
	}

    if (video) {
		delete video;
		video = nullptr;
    }

    if (player) {
		delete player;
		player = nullptr;
    }
}

void PlayerDemo::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
	// Close window, stop player, and quit
	QWidget *pWin = QApplication::activeWindow();
	pWin->hide();
	player->Stop();
	QApplication::quit();
}

void PlayerDemo::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Space || event->key() == Qt::Key_K) {

		if (player->Mode() == openshot::PLAYBACK_PAUSED)
		{
			// paused, so start playing again
			player->Play();

		}
		else if (player->Mode() == openshot::PLAYBACK_PLAY)
		{

			if (player->Speed() == 0)
				// already playing, but speed is zero... so just speed up to normal
				player->Speed(1);
			else
				// already playing... so pause
				player->Pause();

		}

	}
	else if (event->key() == Qt::Key_J) {
		std::cout << "BACKWARD" << player->Speed() - 1 << std::endl;
		if (player->Speed() - 1 != 0)
			player->Speed(player->Speed() - 1);
		else
			player->Speed(player->Speed() - 2);

		if (player->Mode() == openshot::PLAYBACK_PAUSED)
			player->Play();
	}
	else if (event->key() == Qt::Key_L) {
		std::cout << "FORWARD" << player->Speed() + 1 << std::endl;
		if (player->Speed() + 1 != 0)
			player->Speed(player->Speed() + 1);
		else
			player->Speed(player->Speed() + 2);

		if (player->Mode() == openshot::PLAYBACK_PAUSED)
			player->Play();

	}
	else if (event->key() == Qt::Key_Left) {
		std::cout << "FRAME STEP -1" << std::endl;
		if (player->Speed() != 0)
			player->Speed(0);
		player->Seek(player->Position() - 1);
	}
	else if (event->key() == Qt::Key_Right) {
		std::cout << "FRAME STEP +1" << std::endl;
        if (player->Speed() != 0)
            player->Speed(0);
		player->Seek(player->Position() + 1);
	}
	else if (event->key() == Qt::Key_Escape) {
		std::cout << "QUIT PLAYER" << std::endl;
		QWidget *pWin = QApplication::activeWindow();
		pWin->hide();

		player->Stop();

		QApplication::quit();
	}

	event->accept();
	QWidget::keyPressEvent(event);
}

void PlayerDemo::openInCache(const std::string &source,
                             openshot::Timeline **pTimeline,
                             openshot::ReaderInfo &info) {
    openshot::FFmpegReader ffreader(source);
    info = ffreader.info;

    *pTimeline = new openshot::Timeline(ffreader.info.width, ffreader.info.height,
                          ffreader.info.fps, ffreader.info.sample_rate,
                          ffreader.info.channels, ffreader.info.channel_layout);
    openshot::Clip *c = new openshot::Clip(source);
    (*pTimeline)->info = info;
    (*pTimeline)->AddClip(c);
    (*pTimeline)->Open();
}

void PlayerDemo::open(const std::string &source) {
    std::cout<<source<<std::endl;

    if (m_timeline) {
        std::list<openshot::Clip*> clips = m_timeline->Clips();
        std::list<openshot::Clip*>::iterator it;
        for (it=clips.begin(); it != clips.end(); it++){
            m_timeline->RemoveClip(*it);
        }

        m_timeline->ClearAllCache();
    }

    openshot::FFmpegReader ffreader(source);
    /*if (!m_timeline) {
        m_timeline = new openshot::Timeline(ffreader.info.width, ffreader.info.height,
                                        ffreader.info.fps, ffreader.info.sample_rate,
                                        ffreader.info.channels, ffreader.info.channel_layout);

        player->Reader(m_timeline);
    }*/

    openshot::Clip *c = new openshot::Clip(source);
    c->Position(0);
    m_timeline->info = ffreader.info;
    m_timeline->AddClip(c);
    m_timeline->Open();
    //player->Seek(100);
	
    // Set aspect ratio of widget
    video->SetAspectRatio(m_timeline->info.display_ratio, m_timeline->info.pixel_ratio);
    
    // Play video
    player->Play();
    //player->Seek(100);

	//player->Pause();
}

void PlayerDemo::open(bool checked)
{
    Q_UNUSED(checked);
	// Get filename of media files
    const QString filename = QFileDialog::getOpenFileName(this, "Open Video File");
    if (filename.isEmpty()) return;

    open(filename.toStdString());
}

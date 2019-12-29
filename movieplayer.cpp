#include <QtPlayer.h>
#include <Timeline.h>
#include "MoviePlayer.h"

MoviePlayer::MoviePlayer()
{

}

MoviePlayer::~MoviePlayer(){
    if (m_timeline) {
        m_timeline->ClearAllCache();
        m_timeline->Close();
        delete m_timeline;
        m_timeline = nullptr;
    }
}

bool MoviePlayer::open(const std::string &source, const VideoRenderer &render) {
    openshot::FFmpegReader ffreader(source);
    m_info = ffreader.info;

    if (!m_timeline) {
        m_timeline = new openshot::Timeline(ffreader.info.width, ffreader.info.height,
                              ffreader.info.fps, ffreader.info.sample_rate,
                              ffreader.info.channels, ffreader.info.channel_layout);
        openshot::Clip *c = new openshot::Clip(source);
        m_timeline->AddClip(c);
        m_timeline->Open();
    }

    //this->r
}

void MoviePlayer::stop() {
}

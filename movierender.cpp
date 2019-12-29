#include "MovieRender.h"

MovieRender::MovieRender(QWidget *parent)
    : QWidget(parent)
    , m_video(new VideoRenderWidget(this))

{

}

bool MovieRender::open(const std::string &source){
     QHash<std::string, MoviePlayer*>::Iterator it = m_players.find(source);
     MoviePlayer *player = nullptr;

     if (it != m_players.end()) {
        player = it->second;
     } else {
         player = new MoviePlayer();
     }

     if (player) {
         player->open(source, m_video->GetRenderer());
     }
}

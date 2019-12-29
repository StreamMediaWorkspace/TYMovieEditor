#ifndef MOVIEPLAYER_H
#define MOVIEPLAYER_H


#include <PlayerBase.h>
#include "VideoRenderer.h"

namespace openshot {
    class QtPlayer;
    class FFmpegReader;
    class Timeline;
    class ReaderInfo;
}

class MoviePlayer : public openshot::QtPlayer
{
public:
    MoviePlayer();
    ~MoviePlayer();

    bool open(const std::string &source, const VideoRenderer &render);
    void stop();

private:
    openshot::ReaderInfo m_info;
    openshot::Timeline *m_timeline = nullptr;

};

#endif // MOVIEPLAYER_H

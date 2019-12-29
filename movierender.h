#ifndef MOVIERENDER_H
#define MOVIERENDER_H

#include <QWidget>
#include <QHash>
#include "movieplayer.h"
#include "VideoRenderWidget.h"

namespace openshot {
    class QtPlayer;
    class FFmpegReader;
    class Timeline;
    class ReaderInfo;
}

class MovieRender : public QWidget
{
public:
    MovieRender(QWidget *parent = 0);

    bool open(const std::string &source);

private:
    VideoRenderWidget *m_video = nullptr;
    QHash<std::string, MoviePlayer*> m_players;
};

#endif // MOVIERENDER_H

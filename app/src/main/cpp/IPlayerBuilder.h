//
// Created by zx on 2019-08-24.
//

#ifndef XPLAY_IPLAYERBUILDER_H
#define XPLAY_IPLAYERBUILDER_H

#include "IPlayer.h"
class IPlayerBuilder {
public:
    virtual IPlayer *BuilderPlayer(unsigned char index = 0);
protected:
    virtual IDemux *CreateDemux() = 0;
    virtual IDecode *CreateDecode() = 0;
    virtual IResample *CreateResample() = 0;
    virtual IVideoView *CreateVideoView() = 0;
    virtual IAudioPlay *CreateAudioPlay() = 0;
    virtual IPlayer *CreatePlay(unsigned char index = 0) = 0;
};


#endif //XPLAY_IPLAYERBUILDER_H

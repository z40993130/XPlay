//
// Created by zx on 2019-08-23.
//

#ifndef XPLAY_IPLAYER_H
#define XPLAY_IPLAYER_H


#include <mutex>
#include "XThread.h"
#include "XParameter.h"

class IDemux;
class IDecode;
class IResample;
class IVideoView;
class IAudioPlay;

class IPlayer : public XThread {
public:
    static IPlayer *Get(unsigned char index = 0);
    virtual bool Open(const char *path);
    virtual void InitView(void *win);
    virtual bool Start();
    virtual void Close();

    // 是否硬解码
    bool isHardDecode = true;

    XParameter outPara;
    IDemux *demux = 0;
    IDecode *vdecode = 0;
    IDecode *adecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;
protected:
    // 用作音视频同步
    void Main();
    IPlayer(){};
    std::mutex mux;
};


#endif //XPLAY_IPLAYER_H

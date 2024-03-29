//
// Created by z4099 on 2019/7/29.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H


#include "IDemux.h"
struct AVFormatContext;

class FFDemux : public IDemux {
public:
// 打开文件,或者流媒体 rmtp http trsp
    virtual bool Open(const char *url);
    // seek 位置 pos 0.0 ~ 1.0
    virtual bool Seek(double pos);
    virtual void Close();

    virtual XParameter GetVPara();

    // 获取音频参数
    virtual XParameter GetAPara();

    // 读取一帧数据，数据由调用清理
    virtual XData Read();

    FFDemux();
private:
    AVFormatContext *ic = 0;
    std::mutex mux;
    int audioStream = 1;
    int videoStream = 0;
};




#endif //XPLAY_FFDEMUX_H

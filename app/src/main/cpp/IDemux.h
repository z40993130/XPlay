//
// Created by z4099 on 2019/7/29.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H
#include "XData.h"


class IDemux {
public:
    // 打开文件,或者流媒体 rmtp http trsp
    virtual bool Open(const char *url) = 0;

    // 读取一帧数据，数据由调用清理
    virtual XData Read() = 0;

    // 总时长 ms
    int totalMs = 0;
};



#endif //XPLAY_IDEMUX_H

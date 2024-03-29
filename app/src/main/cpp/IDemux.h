//
// Created by z4099 on 2019/7/29.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H
#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"


class IDemux : public IObserver{
public:
    // 打开文件,或者流媒体 rmtp http trsp
    virtual bool Open(const char *url) = 0;
    // seek 位置 pos 0.0-1.0
    virtual bool Seek(double pos) = 0;
    virtual void Close() = 0;

    // 获取视频参数
    virtual XParameter GetVPara() = 0;
    // 获取音频参数
    virtual XParameter GetAPara() = 0;

    // 读取一帧数据，数据由调用清理
    virtual XData Read() = 0;

    // 总时长 ms
    int totalMs = 0;

protected:
    virtual void Main();
};



#endif //XPLAY_IDEMUX_H

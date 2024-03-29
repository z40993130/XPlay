//
// Created by z4099 on 2019/8/5.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "IObserver.h"
#include <list>

// 解码接口，支持硬解码
class IDecode : public IObserver{
public:
    // 打开解码器
    virtual bool Open(XParameter para, bool isHard = false) = 0;

    virtual void Close() = 0;

    virtual void Clear();

    // future 模型 发送数据到线程解码
    virtual bool SendPacket(XData pkt) = 0;

    // 从线程中获取解码结果, 再次调用会复用上次空间，线程不安全
    virtual XData RecvFrame() = 0;

    // 由主体notify的数据 阻塞
    virtual void Update(XData pkt);

    bool isAudio = false;

    // 最大的队列缓冲
    int maxList = 100;

    // 同步时间，再次打开文件要清理
    int syncPts = 0;

    int pts = 0;

protected:
    virtual void Main();
    std::list<XData> packs;
    std::mutex packsMutex;
};


#endif //XPLAY_IDECODE_H

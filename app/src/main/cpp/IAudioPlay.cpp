//
// Created by zx on 2019-08-18.
//

#include "IAudioPlay.h"
#include "XLog.h"
XData IAudioPlay::GetData() {
    XData d;
    while (!isExit) {
        framesMutes.lock();
        if (!frames.empty()) {
            d = frames.front();
            frames.pop_front();
            framesMutes.unlock();
            return d;
        }
        framesMutes.unlock();
        XSleep(1);
    }
    return d;
}
void IAudioPlay::Update(XData data) {
    XLOGE("IAudioPlay::Update %d", data.size);
    // 压入缓冲队列
    if (data.size <= 0 || !data.data)
    {
        return;
    }
    while (!isExit) {
        framesMutes.lock();
        if (frames.size() > maxFrame) {
            framesMutes.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        framesMutes.unlock();
        break;
    }
}
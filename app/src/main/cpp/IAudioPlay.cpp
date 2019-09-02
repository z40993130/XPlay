//
// Created by zx on 2019-08-18.
//

#include "IAudioPlay.h"
#include "XLog.h"
void IAudioPlay::Clear() {
    framesMutes.lock();
    while (!frames.empty()) {
        frames.front().Drop();
        frames.pop_front();
    }
    framesMutes.unlock();
}
XData IAudioPlay::GetData() {
    XData d;
    isRunning = true;
    while (!isExit) {
        if (IsPause()) {
            XSleep(2);
            continue;
        }
        framesMutes.lock();
        if (!frames.empty()) {
            // 有数据返回
            d = frames.front();
            frames.pop_front();
            framesMutes.unlock();
            pts = d.pts;
            return d;
        }
        framesMutes.unlock();
        XSleep(1);
    }
    isRunning = false;
    // 为获取数据
    return d;
}
void IAudioPlay::Update(XData data) {
    // XLOGE("IAudioPlay::Update %d", data.size);
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
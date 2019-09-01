//
// Created by z4099 on 2019/8/5.
//

#include "IDecode.h"
#include "XLog.h"

// 由主体notify的数据
void IDecode::Update(XData pkt) {
    if (pkt.isAudio != isAudio) {
        return;
    }
    while (!isExit) {
        packsMutex.lock();
        // 阻塞
        if (packs.size() < maxList) {
            packs.push_back(pkt);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        XSleep(1);
    }
}

void IDecode::Clear() {
    packsMutex.lock();
    while (!packs.empty()) {
        packs.front().Drop();
        packs.pop_front();
    }
    pts = 0;
    syncPts = 0;
    packsMutex.unlock();
}
void IDecode::Main() {
    while (!isExit) {
        if (IsPause()) {
            XSleep(2);
            continue;
        }
        packsMutex.lock();

        // 判断音视频同步
//        XLOGI("syncPts:%d, pts:%d", syncPts, pts);
        if (!isAudio && syncPts > 0) {
            if (syncPts < pts)
            {
                packsMutex.unlock();
//                XLOGI("video sleep");
                XSleep(1);
                continue;
            }
        }


        if (packs.empty()) {
            packsMutex.unlock();
            XSleep(1);
            continue;
        }
        // 取出packet
        XData pack = packs.front();
        packs.pop_front();

        // 发送数据到解码线程, 一个数据包，可能解码多个结果
        if (this->SendPacket(pack))
        {
            while (!isExit) {
                // 获取解码数据
                XData frame = RecvFrame();
                if (!frame.data)
                {
                    break;
                }
//                XLOGE("RecvFrame size: %d", frame.size);
                pts = frame.pts;
                this->Notify(frame);
            }
        }
        pack.Drop();
        packsMutex.unlock();
    }
}
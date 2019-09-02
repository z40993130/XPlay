//
// Created by zx on 2019-08-23.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "IResample.h"
#include "XLog.h"
#include "FFDecode.h"

IPlayer *IPlayer::Get(unsigned char index) {
    static IPlayer p[256];
    return &p[index];
}

void IPlayer::Main() {
    while (!isExit) {
        mux.lock();
        if (!audioPlay || !vdecode) {
            mux.unlock();
            XSleep(2);
            continue;
        }

        // 同步
        // 获取音频的pts 告诉视频
        int apts = audioPlay->pts;
//        XLOGI("apts = %d", apts);
        vdecode->syncPts = apts;
        mux.unlock();
        XSleep(2);
    }
}

void IPlayer::Close() {
    // 1 先关闭主体线程， 再清理观察者
    // 同步线程
    mux.lock();
    XThread::Stop();
    // 解封装
    if (demux) {
        demux->Stop();
    }
    // 解码
    if (vdecode) {
        vdecode->Stop();
    }
    if (adecode) {
        adecode->Stop();
    }
    if (audioPlay) {
        audioPlay->Stop();
    }

    // 2 清理缓冲队列
    if (vdecode) {
        vdecode->Clear();
    }
    if (adecode) {
        adecode->Clear();
    }
    if (audioPlay) {
        audioPlay->Clear();
    }

    // 3 清理资源
    if (audioPlay) {
        audioPlay->Close();
    }
    if (videoView) {
        videoView->Close();
    }
    if (vdecode) {
        vdecode->Close();
    }
    if (adecode) {
        adecode->Close();
    }
    if (demux) {
        demux->Close();
    }
    mux.unlock();
}

double IPlayer::PlayPos() {
    double pos = 0.0;
    mux.lock();
    int total = 0;
    if (demux) {
        total = demux->totalMs;
    }
    if (total > 0) {
        if (vdecode) {
            pos = (double) vdecode->pts / (double) total;
        }
    }
    mux.unlock();
    return pos;

}
void IPlayer::SetPause(bool isP) {
    mux.lock();
    XThread::SetPause(isP);
    if (demux) {
        demux->SetPause(isP);
    }
    if (vdecode) {
        vdecode->SetPause(isP);
    }
    if (adecode) {
        adecode->SetPause(isP);
    }
    if (audioPlay) {
        audioPlay->SetPause(isP);
    }
    mux.unlock();
}

bool IPlayer::Seek(double pos) {
    bool re = false;
    if (!demux)
    {
        return false;
    }
    // 暂停所有线程
    SetPause(true);
    mux.lock();
    // 清理缓冲
    if (vdecode) {
        vdecode->Clear(); // 清理缓冲队列，清理FFmpeg的缓冲
    }
    if (adecode) {
        adecode->Clear();
    }
    if (audioPlay) {
        audioPlay->Clear();
    }

    re = demux->Seek(pos); // seek 跳转到关键帧

    if (!vdecode) {
        mux.unlock();
        SetPause(false);
        return re;
    }
    // 解码到实际需要显示的帧
    int seekPts = pos * demux->totalMs;
    while (!isExit) {
        XData pkt = demux->Read();
        if (pkt.size <= 0) {
            break;
        }
        if (pkt.isAudio) {
            if (pkt.pts < seekPts) {
                pkt.Drop();
                continue;
            }
            // 写入缓冲队列
            demux->Notify(pkt);
            continue;
        }
        vdecode->SendPacket(pkt);
        pkt.Drop();
        XData data = vdecode->RecvFrame();
        if (data.size <= 0) {
            continue;
        }
        if (data.pts >= seekPts) {

//            vdecode->Notify(data);
            break;
        }

    }

    mux.unlock();
    SetPause(false);
    return re;
}

bool IPlayer::Open(const char *path) {
    Close();
    mux.lock();
    // 解封装
    if (!demux || !demux->Open(path)) {
        mux.unlock();
        XLOGE("demux->Open %s failed!", path);
        return false;
    }
    // 解码 解码可能不需要，如果解封之后就是原始数据
    if (!vdecode || !vdecode->Open(demux->GetVPara(), isHardDecode)) {
        XLOGE("vdecode->Open %s failed!", path);
        // return false;
    }
    if (!adecode || !adecode->Open(demux->GetAPara())) {
        XLOGE("adecode->Open %s failed!", path);
        // return false;
    }

    // 重采样，可能不需要，解码后或者解封装后可能是直接能播放的数据
//    if (outPara.sample_rate <= 0) {
//    }
    outPara = demux->GetAPara();
    if (!resample || !resample->Open(demux->GetAPara(), outPara)) {
        XLOGE("resample->Open %s failed!", path);

    }
    mux.unlock();
    return true;
}

bool IPlayer::Start() {
    mux.lock();

    // 重要！！！
    // 线程启动顺序不同会导致视频丢掉一部分，后面多次启动场景无法播放。（与视频中讲的顺序不一样）

    if (vdecode) {
        vdecode->Start();
    }

    if (!demux || !demux->Start()) {
        mux.unlock();
        XLOGE("demux->Start failed!");
        return false;
    }
    if (adecode) {
        adecode->Start();
    }
    if (audioPlay) {
        audioPlay->StartPlay(outPara);
    }


//    if (!demux || !demux->Start()) {
//        mux.unlock();
//        XLOGE("demux->Start failed!");
//        return false;
//    }
//    if (adecode) {
//        adecode->Start();
//    }
//    if (audioPlay) {
//        audioPlay->StartPlay(outPara);
//    }
//    if (vdecode) {
//        vdecode->Start();
//    }
    XThread::Start();
    mux.unlock();
    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView) {
        videoView->Close(); // 每次打开前关闭上次，解决多次打开视频不正常问题
        videoView->SetRender(win);
    }
}



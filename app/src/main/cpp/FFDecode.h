//
// Created by z4099 on 2019/8/5.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include "IDecode.h"
struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:
    static void InitHard(void *vm);
    virtual bool Open(XParameter para, bool isHard = false);
    virtual void Close();
    virtual void Clear();
    // future 模型 发送数据到线程解码
    virtual bool SendPacket(XData pkt);

    // 从线程中获取解码结果
    virtual XData RecvFrame();



protected:
    AVCodecContext *codec = 0;
    AVFrame *frame = 0;
    std::mutex mux;
};


#endif //XPLAY_FFDECODE_H

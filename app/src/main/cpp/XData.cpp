//
// Created by z4099 on 2019/7/29.
//


#include "XData.h"
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

void XData::Drop() {
    if (!data) return;
    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}
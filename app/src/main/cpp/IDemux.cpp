//
// Created by z4099 on 2019/7/29.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    while (!isExit) {
        XData d = Read();
//        XLOGI("IDemux Read %d", d.size);

        if (d.size > 0) {
            Notify(d);
        }
//        XLOGI("IDemux Read %d", d.size);
//        if (d.size <= 0) {
//            break;
//        }
    }
}
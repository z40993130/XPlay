//
// Created by z4099 on 2019/8/1.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>

using namespace std;

// 启动线程
void XThread::Start() {
    thread th(&XThread::ThreadMain, this);
    th.detach();

}

void XThread::ThreadMain()
{
    XLOGI("线程函数进入");
    Main();
    XLOGI("线程函数退出");

}

// 通过控制isExit安全停止线程（不一定成功）
void XThread::Stop(){}
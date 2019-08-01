//
// Created by z4099 on 2019/8/1.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H


class XThread {
public:
    // 启动线程
    virtual void Start();

    // 通过控制isExit安全停止线程（不一定成功）
    virtual void Stop();

    // 入门主函数
    virtual void Main(){}

private:
    void ThreadMain();

};


#endif //XPLAY_XTHREAD_H

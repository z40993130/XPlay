//
// Created by z4099 on 2019/8/1.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H


// sleep 毫秒
void XSleep(int mis);

class XThread {
public:
    // 启动线程
    virtual bool Start();

    // 通过控制isExit安全停止线程（不一定成功）
    virtual void Stop();

    // 入门主函数
    virtual void Main(){}

    virtual void SetPause(bool isP);
    virtual bool IsPause()
    {
        isPausing = isPause;
        return isPause;
    }

protected:
    bool isExit = false;
    bool isRunning = false;
    bool isPause = false;
    bool isPausing = false;

private:
    void ThreadMain();

};


#endif //XPLAY_XTHREAD_H

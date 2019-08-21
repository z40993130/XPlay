//
// Created by zx on 2019-08-18.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver {
public:
    // 缓冲后注释
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;
    // 最大缓冲
    int maxFrame = 100;

protected:
    std::list <XData> frames;
    std::mutex framesMutes;
};


#endif //XPLAY_IAUDIOPLAY_H

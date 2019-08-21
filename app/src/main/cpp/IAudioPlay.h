//
// Created by zx on 2019-08-18.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver {
public:
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;
};


#endif //XPLAY_IAUDIOPLAY_H

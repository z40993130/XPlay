//
// Created by zx on 2019-08-11.
//

#ifndef XPLAY_XEGL_H
#define XPLAY_XEGL_H


#include <mutex>

class XEGL {
public:
    virtual bool Init(void *win) = 0;
    virtual void Close() = 0;
    virtual void Draw() = 0;
    static XEGL *Get();
protected:
    XEGL(){}

};


#endif //XPLAY_XEGL_H

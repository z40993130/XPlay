//
// Created by zx on 2019-08-24.
//

#ifndef XPLAY_IPLAYERPROZY_H
#define XPLAY_IPLAYERPROZY_H


#include <mutex>
#include "IPlayer.h"

class IPlayerProxy : public IPlayer {
public:
    static IPlayerProxy* Get()
    {
        static IPlayerProxy proxy;
        return &proxy;
    }
    void Init(void *vm);
    virtual bool Open(const char *path);
    virtual void InitView(void *win);
    virtual bool Start();

protected:
    IPlayerProxy(){};
    IPlayer *player = 0;
    std::mutex mux;
};


#endif //XPLAY_IPLAYERPROZY_H

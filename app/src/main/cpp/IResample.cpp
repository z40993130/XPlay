//
// Created by zx on 2019-08-15.
//

#include "IResample.h"
void IResample::Update(XData data)
{
    XData d = this->Resample(data);
    if (d.size > 0)
    {
        this->Notify(d);
    }
}
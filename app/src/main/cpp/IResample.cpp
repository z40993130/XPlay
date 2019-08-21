//
// Created by zx on 2019-08-15.
//

#include "IResample.h"
#include "XLog.h"

void IResample::Update(XData data)
{
    XData d = this->Resample(data);
    XLOGE("his->Resample(data) %d", d.size);
    if (d.size > 0)
    {
        this->Notify(d);
    }
}
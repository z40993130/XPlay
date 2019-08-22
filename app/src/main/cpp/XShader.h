//
// Created by zx on 2019-08-11.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H

enum XShaderType
{
    XSHADER_YUV420P = 0,
    XSHADER_NV12 = 25,
    XSHADER_NV21 = 26
};

class XShader {
public:
    virtual bool Init(XShaderType type = XSHADER_YUV420P);

    // 获取材质并映射到内存
    virtual void GetTexture(unsigned int index, int width, int height, unsigned char *buf, bool isa = false);
    virtual void Draw();
protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = { 0 };
};


#endif //XPLAY_XSHADER_H

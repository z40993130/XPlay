#include <jni.h>
#include <string>
#include <android/native_window_jni.h>

#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"

class TestObs:public IObserver
{
public:
    void Update(XData data){
//        XLOGI("TestObs Updata data size id %d", data);
    }
};
IVideoView *view = NULL;

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res)
{
    FFDecode::InitHard(vm);

    /////////////////////////
    // 测试用代码
    TestObs *tobs = new TestObs();
    IDemux *de = new FFDemux();
//    de->AddObs(tobs);
//    de->Open("/sdcard/1080.mp4");

    IDecode *vdecode = new FFDecode();
//    vdecode->Open(de->GetVPara(), true);

    IDecode *adecode = new FFDecode();
//    adecode->Open(de->GetAPara());
    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample *resample = new FFResample();
//    XParameter outPara = de->GetAPara();

//    resample->Open(de->GetAPara(), outPara);
    adecode->AddObs(resample);

    IAudioPlay *audioPlay = new SLAudioPlay();
//    audioPlay->StartPlay(outPara);
    resample->AddObs(audioPlay);

    IPlayer::Get()->demux = de;
    IPlayer::Get()->adecode = adecode;
    IPlayer::Get()->vdecode = vdecode;
    IPlayer::Get()->videoView = view;
    IPlayer::Get()->resample = resample;
    IPlayer::Get()->audioPlay = audioPlay;

    IPlayer::Get()->Open("/sdcard/v1080.mp4");
    IPlayer::Get()->Start();


//    vdecode->Open();
//    de->Start();
//    vdecode->Start();
//    adecode->Start();
//    XSleep(3000);
//    de->Stop();
//    for (;;) {
//        XData d = de->Read();
//        XLOGI("Read data size is %d", d.size);
//    }



    return JNI_VERSION_1_4;
}



extern "C" JNIEXPORT jstring JNICALL
Java_com_example_zx_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";



    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_zx_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayer::Get()->InitView(win);
//    view->SetRender(win);
//    XEGL::Get()->Init(win);
//    XShader shader;
//    shader.Init();

}
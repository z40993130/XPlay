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
#include "FFPlayerBuilder.h"

class TestObs:public IObserver
{
public:
    void Update(XData data){
//        XLOGI("TestObs Updata data size id %d", data);
    }
};
static IPlayer *player = NULL;
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res)
{
    // FFDecode::InitHard(vm);
    FFPlayerBuilder::InitHard(vm);
    // 测试代码
    player = FFPlayerBuilder::Get()->BuilderPlayer();

    player->Open("/sdcard/v1080.mp4");
    player->Start();

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
    if (player) {
        player->InitView(win);
    }
//    view->SetRender(win);
//    XEGL::Get()->Init(win);
//    XShader shader;
//    shader.Init();

}
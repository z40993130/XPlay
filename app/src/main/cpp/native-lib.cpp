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
#include "IPlayerProxy.h"

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res) {
    IPlayerProxy::Get()->Init(vm);
//    IPlayerProxy::Get()->Open("/sdcard/v1080.mp4");
//    IPlayerProxy::Get()->Start();
//
//    IPlayerProxy::Get()->Open("/sdcard/1080.mp4"); // 多次打开有概率导致闪退，目前原因未知。
//    IPlayerProxy::Get()->Start();
    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_zx_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayerProxy::Get()->InitView(win);
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_zx_xplay_Openurl_Open(JNIEnv *env, jobject instance, jstring url_) {
    const char *url = env->GetStringUTFChars(url_, 0);

    IPlayerProxy::Get()->Open(url);
    IPlayerProxy::Get()->Start();


    env->ReleaseStringUTFChars(url_, url);
}extern "C"
JNIEXPORT jdouble JNICALL
Java_com_example_zx_xplay_MainActivity_PlayPos(JNIEnv *env, jobject instance) {
    return IPlayerProxy::Get()->PlayPos();
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_zx_xplay_MainActivity_Seek(JNIEnv *env, jobject instance, jdouble pos) {
    IPlayerProxy::Get()->Seek(pos);

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_zx_xplay_XPlay_PlayOrPause(JNIEnv *env, jobject instance) {
    IPlayerProxy::Get()->SetPause(!IPlayerProxy::Get()->IsPause());
}
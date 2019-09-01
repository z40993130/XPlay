package com.example.zx.xplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.View;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback, GLSurfaceView.Renderer, View.OnClickListener {

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);

        // android8.0 需要设置
        setRenderer(this);
        setOnClickListener(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        InitView(holder.getSurface()); // 初始化openGl 显示


    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {

    }

    public native void InitView(Object surface);

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {

    }

    @Override
    public void onDrawFrame(GL10 gl10) {

    }

    @Override
    public void onClick(View view) {
        PlayOrPause();
    }

    public native void PlayOrPause();
}


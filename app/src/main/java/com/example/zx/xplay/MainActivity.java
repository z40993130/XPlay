package com.example.zx.xplay;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.SeekBar;


public class MainActivity extends AppCompatActivity implements Runnable {

    private static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    private Button btn_open;
    private SeekBar seek;
    private Thread th;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //去掉标题栏
        supportRequestWindowFeature( Window.FEATURE_NO_TITLE);
        // 全屏，隐藏状态
        getWindow().setFlags( WindowManager.LayoutParams.FLAG_FULLSCREEN ,
                WindowManager.LayoutParams.FLAG_FULLSCREEN
        );
        // 屏幕为横屏
        setRequestedOrientation( ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE );

        setContentView(R.layout.activity_main);
        btn_open = findViewById(R.id.open_button);
        seek = findViewById(R.id.aplayseek);
        seek.setMax(1000);
        btn_open.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i(TAG, "open onClick");
                Intent intent = new Intent(MainActivity.this, Openurl.class);
                startActivity(intent);
            }
        });


        th = new Thread(this);
        th.start();
    }

    // 播放进度显示
    @Override
    public void run() {
        for (; ; ) {
            seek.setProgress((int)(PlayPos() * 1000));
            try {
                Thread.sleep(40);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public native double PlayPos();
}

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


public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    private Button btn_open;

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
        btn_open.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.i(TAG, "open onClick");
                Intent intent = new Intent(MainActivity.this, Openurl.class);
                startActivity(intent);
            }
        });

    }


}

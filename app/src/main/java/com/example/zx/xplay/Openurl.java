package com.example.zx.xplay;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class Openurl extends AppCompatActivity {
    private Button btfile;
    private Button btrtmp;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.openurl);
        btfile = findViewById(R.id.playVideo);
        btrtmp = findViewById(R.id.playRtmp);
        btfile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText et = findViewById(R.id.fileurl);
                Open(et.getText().toString());
                finish();
            }
        });

        btrtmp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText editText = findViewById(R.id.rtmpurl);
                Open(editText.getText().toString());
                finish();
            }
        });
    }

    public native void Open(String url);
}

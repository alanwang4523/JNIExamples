package com.alan.jniexamples;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.alan.jniexamples.dynamic.NativeDynamic;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("JNI Examples");

        testDynamicJNIs();
    }

    private void testDynamicJNIs() {
        NativeDynamic.nativeSetBasicArgs(2, 3.2f, 1000L, true);
        NativeDynamic.nativeSetStringArgs("Hello Alan From Java!");
    }
}

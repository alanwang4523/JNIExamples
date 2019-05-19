package com.alan.jniexamples;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.alan.jniexamples.dynamic.MediaServerDynamic;
import com.alan.jniexamples.dynamic.NativeDynamic;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("JNI Examples");

        testDynamicJNIs();
        testMediaServerDynamic();
    }

    private void testDynamicJNIs() {
        NativeDynamic.nativeSetBasicArgs(2, 3.2f, 1000L, true);
        NativeDynamic.nativeSetStringArgs("Hello Alan From Java!");
    }

    private void testMediaServerDynamic() {
        MediaServerDynamic mediaServerDynamic_01 = new MediaServerDynamic("MS_001");
        mediaServerDynamic_01.config(1);
        Log.e(TAG, "mediaServerDynamic_01 getName from native--->>" + mediaServerDynamic_01.getName());

        MediaServerDynamic mediaServerDynamic_02 = new MediaServerDynamic("MS_002");
        mediaServerDynamic_02.config(2);
        Log.e(TAG, "mediaServerDynamic_02 getName from native--->>" + mediaServerDynamic_02.getName());
    }
}

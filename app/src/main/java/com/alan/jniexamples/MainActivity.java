package com.alan.jniexamples;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.alan.jniexamples.common.MediaParam;
import com.alan.jniexamples.dynamic.MediaServerDynamic;
import com.alan.jniexamples.dynamic.NativeDynamic;
import com.alan.jniexamples.jnistatic.MediaServerStatic;
import com.alan.jniexamples.jnistatic.NativeStatic;

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

        testStaticJNIs();
        testMediaServerStatic();
    }

    private void testDynamicJNIs() {
        Log.e(TAG, "/////////////////// testDynamicJNIs ///////////////////");
        NativeDynamic.nativeSetBasicArgs(2, 3.2f, 1000L, true);
        NativeDynamic.nativeSetStringArgs("Hello Alan From Java!");
    }

    private void testMediaServerDynamic() {
        Log.e(TAG, "/////////////////// testMediaServerDynamic ///////////////////");
        MediaServerDynamic mediaServerDynamic_01 = new MediaServerDynamic("MSD_001");
        mediaServerDynamic_01.config(1);
        Log.d(TAG, "mediaServerDynamic_01 getName from native--->>" + mediaServerDynamic_01.getName());
        mediaServerDynamic_01.release();

        MediaServerDynamic mediaServerDynamic_02 = new MediaServerDynamic("MSD_002");
        mediaServerDynamic_02.config(2);
        Log.d(TAG, "mediaServerDynamic_02 getName from native--->>" + mediaServerDynamic_02.getName());
        mediaServerDynamic_02.release();
    }

    private void testStaticJNIs() {
        Log.e(TAG, "/////////////////// testStaticJNIs ///////////////////");
        NativeStatic.nativeSetBasicArgs(3, 2.2f, 60000L, false);
        NativeStatic.nativeSetStringArgs("String From Java Static Test!");
    }

    private void testMediaServerStatic() {
        Log.e(TAG, "/////////////////// testMediaServerStatic ///////////////////");
        MediaServerStatic mediaServerStatic_01 = new MediaServerStatic("MSS_001");
        mediaServerStatic_01.config(3);

        MediaParam mediaParam = MediaParam.build()
                .setPath("/sdcard/Alan/audio/test.m4a")
                .setStartTime(0L)
                .setEndTime(15 * 1000L)
                .setEnableLoop(true);
        mediaServerStatic_01.setMediaParam(mediaParam);

        Log.d(TAG, "mediaServerStatic_01 getName from native--->>" + mediaServerStatic_01.getName());
        mediaServerStatic_01.release();

        MediaServerStatic mediaServerStatic_02 = new MediaServerStatic("MSS_002");
        mediaServerStatic_02.config(5);
        Log.d(TAG, "mediaServerStatic_02 getName from native--->>" + mediaServerStatic_02.getName());
        mediaServerStatic_02.release();
    }
}

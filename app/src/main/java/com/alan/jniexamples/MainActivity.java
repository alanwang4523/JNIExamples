package com.alan.jniexamples;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

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
        NativeDynamic.nativeSetBasicArgs(2, 3.2f, 1000L, true);
        NativeDynamic.nativeSetStringArgs("Hello Alan From Java!");
    }

    private void testMediaServerDynamic() {
        MediaServerDynamic mediaServerDynamic_01 = new MediaServerDynamic("MSD_001");
        mediaServerDynamic_01.config(1);
        Log.e(TAG, "mediaServerDynamic_01 getName from native--->>" + mediaServerDynamic_01.getName());

        MediaServerDynamic mediaServerDynamic_02 = new MediaServerDynamic("MSD_002");
        mediaServerDynamic_02.config(2);
        Log.e(TAG, "mediaServerDynamic_02 getName from native--->>" + mediaServerDynamic_02.getName());
    }

    private void testStaticJNIs() {
        NativeStatic.nativeSetBasicArgs(3, 2.2f, 60000L, false);
        NativeStatic.nativeSetStringArgs("String From Java Static Test!");
    }

    private void testMediaServerStatic() {
        MediaServerStatic mediaServerStatic_01 = new MediaServerStatic("MSS_001");
        mediaServerStatic_01.config(3);
        Log.e(TAG, "mediaServerStatic_01 getName from native--->>" + mediaServerStatic_01.getName());
        mediaServerStatic_01.release();

        MediaServerStatic mediaServerStatic_02 = new MediaServerStatic("MSS_002");
        mediaServerStatic_02.config(5);
        Log.e(TAG, "mediaServerStatic_02 getName from native--->>" + mediaServerStatic_02.getName());
        mediaServerStatic_02.release();


    }
}

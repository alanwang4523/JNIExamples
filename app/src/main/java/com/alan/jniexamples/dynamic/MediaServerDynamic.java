package com.alan.jniexamples.dynamic;

/**
 * Author: AlanWang4523.
 * Date: 19/5/19 22:13.
 * Mail: alanwang4523@gmail.com
 */
public class MediaServerDynamic {

    private static native final void native_init();

    static {
        System.loadLibrary("media_jni");
        native_init();
    }
    private long mNativeContext;

    public MediaServerDynamic(String name) {
        native_create(name);
    }

    public void config(int type) {
        native_config(type);
    }

    private native final void native_create(String name);

    private native final void native_config(int type);

}

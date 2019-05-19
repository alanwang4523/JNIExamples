package com.alan.jniexamples.dynamic;

/**
 * Author: AlanWang4523.
 * Date: 19/5/19 22:13.
 * Mail: alanwang4523@gmail.com
 */
public class MediaServerDynamic {

    private static native final void native_init();

    static {
        System.loadLibrary("jni_example");
        native_init();
    }
    // 该成员变量名不要改名，与底层保持一致，用于关联底层实例与 java 实例
    private long mNativeContext;

    public MediaServerDynamic(String name) {
        native_create(name);
    }

    public void config(int type) {
        native_config(type);
    }

    public String getName() {
        return native_getName();
    }

    private native final void native_create(String name);

    private native final void native_config(int type);

    private native final String native_getName();

}

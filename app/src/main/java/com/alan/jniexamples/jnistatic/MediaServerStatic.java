package com.alan.jniexamples.jnistatic;

/**
 * Author: AlanWang4523.
 * Date: 19/5/22 23:13.
 * Mail: alanwang4523@gmail.com
 */
public class MediaServerStatic {

    // javah -classpath app/build/intermediates/javac/debug/compileDebugJavaWithJavac/classes com.alan.jniexamples.jnistatic.MediaServerStatic

    /**
     * 生成 JNI  头文件命令，在项目根目录执行，即 JNIExamples 目录下执行（先 rebuild 一下生成 class 文件）：
     * javah -classpath app/build/intermediates/javac/debug/compileDebugJavaWithJavac/classes com.alan.jniexamples.jnistatic.MediaServerStatic
     */
    static {
        System.loadLibrary("jni_example");
    }

    private long mNativeContext;

    public MediaServerStatic(String name) {
        mNativeContext = native_create(name);
    }

    public void config(int type) {
        native_config(mNativeContext, type);
    }

    public String getName() {
        return native_getName(mNativeContext);
    }

    public void release() {
        native_release(mNativeContext);
    }

    private native final long native_create(String name);

    private native final void native_config(long instanceId, int type);

    private native final String native_getName(long instanceId);

    private native final void native_release(long instanceId);
}

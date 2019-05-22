package com.alan.jniexamples.jnistatic;

/**
 * Author: AlanWang4523.
 * Date: 19/5/22 23:13.
 * Mail: alanwang4523@gmail.com
 */
public class MediaServerStatic {
    /*
     * 生成 JNI  头文件命令，在项目根目录执行，即 JNIExamples 目录下执行（先 rebuild 一下生成 class 文件）：
     * javah -classpath app/build/intermediates/javac/debug/compileDebugJavaWithJavac/classes com.alan.jniexamples.jnistatic.MediaServerStatic
     */

    static {
        System.loadLibrary("jni_example");
    }

    private long mNativeContext;

    public MediaServerStatic(String name) {
        mNativeContext = nativeCreate(name);
    }

    public void config(int type) {
        nativeConfig(mNativeContext, type);
    }

    public String getName() {
        return nativeGetName(mNativeContext);
    }

    public void release() {
        nativeRelease(mNativeContext);
    }

    /////////////////////////// Native functions ///////////////////////////

    private native final long nativeCreate(String name);

    private native final void nativeConfig(long instanceId, int type);

    private native final String nativeGetName(long instanceId);

    private native final void nativeRelease(long instanceId);
}

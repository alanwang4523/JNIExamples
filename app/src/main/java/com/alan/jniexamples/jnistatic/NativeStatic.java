package com.alan.jniexamples.jnistatic;

/**
 * Author: AlanWang4523.
 * Date: 19/5/21 21:04.
 * Mail: alanwang4523@gmail.com
 */
public class NativeStatic {

    static {
        System.loadLibrary("jni_example");
    }

    public static native int nativeSetBasicArgs(int iArg, float fArg, long lArg, boolean bArg);

    public static native void nativeSetStringArgs(String str);
}

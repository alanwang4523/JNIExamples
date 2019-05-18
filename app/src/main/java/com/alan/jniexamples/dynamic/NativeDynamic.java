package com.alan.jniexamples.dynamic;

/**
 * Author: AlanWang4523.
 * Date: 19/5/18 11:14.
 * Mail: alanwang4523@gmail.com
 */
public class NativeDynamic {
    static {
        System.loadLibrary("jni_example");
    }

    public native int nativeSetBasicArgs(int iArg, float fArg, long lArg, boolean bArg);

}

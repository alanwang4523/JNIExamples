/*
 * Copyright (c) 2019-present AlanWang4523 <alanwang4523@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.alan.jniexamples.jnistatic;

import android.util.Log;

import com.alan.jniexamples.common.MediaInfo;
import com.alan.jniexamples.common.MediaParam;
import com.alan.jniexamples.common.MediaServerCallback;

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

    public void setMediaParam(MediaParam mediaParam) {
        int errCode = nativeSetMediaParam(mNativeContext, mediaParam);
        if (errCode != 0) {
            Log.e("MediaServerStatic", "setMediaParam error : " + errCode);
        }
    }

    public void setMediaServerCallback(MediaServerCallback callback) {
        nativeSetCallback(mNativeContext, callback);
    }

    public String getName() {
        return nativeGetName(mNativeContext);
    }

    public MediaInfo getMediaInfo() {
        return nativeGetMediaInfo(mNativeContext);
    }

    public void release() {
        nativeRelease(mNativeContext);
    }

    /////////////////////////// Native functions ///////////////////////////

    private native final long nativeCreate(String name);

    private native final void nativeConfig(long instanceId, int type);

    private native final int nativeSetMediaParam(long instanceId, MediaParam mediaParam);

    private native final void nativeSetCallback(long instanceId, MediaServerCallback callback);

    private native final String nativeGetName(long instanceId);

    private native final MediaInfo nativeGetMediaInfo(long instanceId);

    private native final void nativeRelease(long instanceId);
}

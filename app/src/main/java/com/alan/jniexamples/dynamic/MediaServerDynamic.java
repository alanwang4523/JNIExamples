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
package com.alan.jniexamples.dynamic;

import android.util.Log;

import com.alan.jniexamples.common.MediaInfo;
import com.alan.jniexamples.common.MediaParam;

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

    public void setMediaParam(MediaParam mediaParam) {
        int errCode = native_setMediaParam(mediaParam);
        if (errCode != 0) {
            Log.e("MediaServerDynamic", "setMediaParam error : " + errCode);
        }
    }

    public String getName() {
        return native_getName();
    }

    public MediaInfo getMediaInfo() {
        return native_getMediaInfo();
    }

    public void release() {
        native_release();
    }

    /////////////////////////// Native functions ///////////////////////////

    private native final void native_create(String name);

    private native final void native_config(int type);

    private native final int native_setMediaParam(MediaParam mediaParam);

    private native final String native_getName();

    private native final MediaInfo native_getMediaInfo();

    private native final void native_release();

}

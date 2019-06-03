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
 /**
 * Author: AlanWang4523.
 * Date: 19/5/19 22:22.
 * Mail: alanwang4523@gmail.com
 */

#include <jni.h>
#include "common/JNIHelper.h"
#include "common/Log.h"
#include "business/MediaServer.h"

struct fields_t {
    jfieldID context;
};
static fields_t gFields;

// Java 层声明 native 方法的类的全路径
static const char *className = "com/alan/jniexamples/dynamic/MediaServerDynamic";

static int MediaServer_native_init(JNIEnv *env) {
    LOGD("MediaServerDynamicJNI", "MediaServer_native_init()-->>\n");

    jclass clazz = (env)->FindClass(className);
    if (clazz == NULL) {
        LOGE("MediaServerDynamicJNI", "Unable to find class\n");
        return -1;
    }

    gFields.context = env->GetFieldID(clazz, "mNativeContext", "J");
    return 0;
}

static void MediaServer_native_create(JNIEnv *env, jobject obj,jstring strArg) {
    jboolean isCopy;
    // 这里不能直接使用 strArg，需要将其通过 GetStringUTFChars 接口将其转成 UTF-8 的 字符串的指针
    char *cStr = (char *) env->GetStringUTFChars(strArg, &isCopy);

    // 创建底层实例，并与上层实例关联，即将底层实例的地址赋值给上层实例的成员变量 mNativeContext
    MediaServer * mediaServer = new MediaServer(cStr);
    env->SetLongField(obj, gFields.context, (jlong)mediaServer);

    // 最后需要释放，否则可能导致内存泄漏
    env->ReleaseStringUTFChars(strArg, cStr);
}

static int MediaServer_native_config(JNIEnv *env, jobject obj, jint type) {
    // 通过上层实例的成员变量获取对应的底层实例
    MediaServer * mediaServer = (MediaServer *)env->GetLongField(obj, gFields.context);
    if (mediaServer) {
        return mediaServer->config(type);
    } else {
        return ERROR_PARAM;
    }
}

static int MediaServer_native_setMediaParam(JNIEnv *env, jobject obj, jobject jniParamObj) {
    // 通过上层实例的成员变量获取对应的底层实例
    MediaServer * mediaServer = (MediaServer *)env->GetLongField(obj, gFields.context);
    if (!mediaServer) {
        return ERROR_PARAM;
    }

    int errCode = SUCCESS;

    jclass jclsParamClass = NULL;
    jmethodID jmid = NULL;
    jstring jsFilePath = NULL;

    MediaParam mediaParam;
    mediaParam.path = NULL;

    if ((NULL == env) || (jniParamObj == NULL)) {
        errCode = ERROR_PARAM;
        goto exit;
    }

    jclsParamClass = env->GetObjectClass(jniParamObj);
    if (NULL == jclsParamClass) {
        errCode = ERROR_PARAM;
        goto exit;
    }

    //获取文件路径
    jmid = env->GetMethodID(jclsParamClass, "getPath", "()Ljava/lang/String;");
    if (NULL == jmid) {
        errCode = ERROR_PARAM;
        goto exit;
    }
    jsFilePath = (jstring) env->CallObjectMethod(jniParamObj, jmid);
    if (NULL != jsFilePath) {
        mediaParam.path = env->GetStringUTFChars(jsFilePath, NULL);
    }

    jmid = env->GetMethodID(jclsParamClass, "getStartTime", "()J");
    if (NULL == jmid) {
        errCode = ERROR_PARAM;
        goto exit;
    }
    mediaParam.start_time = env->CallLongMethod(jniParamObj, jmid);

    jmid = env->GetMethodID(jclsParamClass, "getEndTime", "()J");
    if (NULL == jmid) {
        errCode = ERROR_PARAM;
        goto exit;
    }
    mediaParam.end_time = env->CallLongMethod(jniParamObj, jmid);

    jmid = env->GetMethodID(jclsParamClass, "isEnableLoop", "()Z");
    if (NULL == jmid) {
        errCode = ERROR_PARAM;
        goto exit;
    }
    mediaParam.enable_loop = env->CallBooleanMethod(jniParamObj, jmid);

    errCode = mediaServer->setMediaParam(&mediaParam);

exit:
    if (jclsParamClass) {
        env->DeleteLocalRef(jclsParamClass);
    }
    //释放文件路径相关的内存
    if (mediaParam.path) {
        env->ReleaseStringUTFChars(jsFilePath, mediaParam.path);
    }
    if (jsFilePath) {
        env->DeleteLocalRef(jsFilePath);
    }
    return errCode;
}

static jstring MediaServer_native_getName(JNIEnv *env, jobject obj) {
    MediaServer * mediaServer = (MediaServer *)env->GetLongField(obj, gFields.context);
    if (mediaServer) {
        const char *c_name = mediaServer->getName().c_str();
        return env->NewStringUTF(c_name);
    } else {
        return nullptr;
    }
}

static jobject MediaServer_native_getMediaInfo(JNIEnv *env, jobject obj) {
    MediaServer * mediaServer = (MediaServer *)env->GetLongField(obj, gFields.context);
    if (!mediaServer) {
        return nullptr;
    }

    // 找到要创建的 Java 类
    jclass jclMediaInfo = env->FindClass("com/alan/jniexamples/common/MediaInfo");
    // 获取 Java 类的构造函数及相关方法
    jmethodID jmidConstructor = env->GetMethodID(jclMediaInfo, "<init>", "()V");
    jmethodID jmidSetSampleRate = env->GetMethodID(jclMediaInfo, "setSampleRate", "(I)V");
    jmethodID jmidSetChanelCount = env->GetMethodID(jclMediaInfo, "setChanelCount", "(I)V");
    jmethodID jmidSetDuration = env->GetMethodID(jclMediaInfo, "setDuration", "(J)V");

    // 通过构造函数创建 Java 实例
    jobject jobjMediaInfo = env->NewObject(jclMediaInfo, jmidConstructor);

    // 从 C/C++ 的业务实例获取 Java 层要获取的信息
    pMediaInfo mediaInfo = mediaServer->getMediaInfo();

    // 通过相应的方法给创建的 Java 实例赋值
    env->CallVoidMethod(jobjMediaInfo, jmidSetSampleRate, mediaInfo->sample_rate);
    env->CallVoidMethod(jobjMediaInfo, jmidSetChanelCount, mediaInfo->chanel_count);
    env->CallVoidMethod(jobjMediaInfo, jmidSetDuration, mediaInfo->duration);

    return jobjMediaInfo;
}

static void MediaServer_native_release(JNIEnv *env, jobject obj, jint type) {
    // 通过上层实例的成员变量获取对应的底层实例
    MediaServer * mediaServer = (MediaServer *)env->GetLongField(obj, gFields.context);
    if (mediaServer) {
        delete mediaServer;
    }
    env->SetLongField(obj, gFields.context, (jlong)0);
}

static JNINativeMethod gJni_Methods[] = {
        {"native_init", "()V", (void*)MediaServer_native_init},
        {"native_create", "(Ljava/lang/String;)V", (void*)MediaServer_native_create},
        {"native_config", "(I)V", (void*)MediaServer_native_config},
        {"native_setMediaParam", "(Lcom/alan/jniexamples/common/MediaParam;)I", (void*)MediaServer_native_setMediaParam},
        {"native_getName", "()Ljava/lang/String;", (void*)MediaServer_native_getName},
        {"native_getMediaInfo", "()Lcom/alan/jniexamples/common/MediaInfo;", (void*)MediaServer_native_getMediaInfo},
        {"native_release", "()V", (void*)MediaServer_native_release},
};

int register_MediaServerDynamic(JNIEnv* env) {
    return jniRegisterNativeMethods(env, className, gJni_Methods, NELEM(gJni_Methods));
}
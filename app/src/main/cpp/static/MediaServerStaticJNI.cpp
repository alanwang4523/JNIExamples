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
 * Date: 19/5/22 23:30.
 * Mail: alanwang4523@gmail.com
 */

#include <memory.h>
#include "MediaServerStaticJNI.h"
#include "MediaServer.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeCreate
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeCreate
        (JNIEnv *env, jobject obj, jstring jsName) {
    jboolean isCopy;
    // 这里不能直接使用 jsName，需要将其通过 GetStringUTFChars 接口将其转成 UTF-8 的 字符串的指针
    char *cStrName = (char *) env->GetStringUTFChars(jsName, &isCopy);

    MediaServer * mediaServer = new MediaServer(cStrName);

    // 最后需要释放，否则可能导致内存泄漏
    env->ReleaseStringUTFChars(jsName, cStrName);

    // 将底层创建的 mediaServer 指针地址返回给上层，后续调用该实例的方法时将该地址传下来，
    // 从而使 java 层的 MediaServerStatic 实例和底层 MediaServe 实例一一对应
    // （也可参考动态注册中的实现方式，直接 JNI 层通过 FieldID 给上层的成员变量赋值，从而不需要每个方法都要传 instanceId）
    return (jlong)mediaServer;
}

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeConfig
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeConfig
(JNIEnv *env, jobject obj, jlong instanceId, jint type) {
    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (mediaServer) {
        mediaServer->config(type);
    }
}

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeSetMediaParam
 * Signature: (JLcom/alan/jniexamples/common/MediaParam;)I
 */
JNIEXPORT jint JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetMediaParam
        (JNIEnv *env, jobject jobj, jlong instanceId, jobject jniParamObj) {

    MediaServer * mediaServer = (MediaServer *)instanceId;
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

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeSetCallback
 * Signature: (JLcom/alan/jniexamples/common/MediaServerCallback;)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetCallback
        (JNIEnv *env, jobject obj, jlong instanceId, jobject jCallback) {
    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (!mediaServer) {
        return;
    }

    memset(mediaServer->getCallbackContext(), 0, sizeof(CallbackContext));
    env->GetJavaVM(&mediaServer->getCallbackContext()->jvm);
    mediaServer->getCallbackContext()->jniCallbackObj = env->NewGlobalRef(jCallback);
    jclass cbkClass = env->GetObjectClass(jCallback);
    mediaServer->getCallbackContext()->jmidGetImageTexture = env->GetMethodID(cbkClass, "getImageTexture", "(Ljava/lang/String;)I");
    mediaServer->getCallbackContext()->jmidOnError = env->GetMethodID(cbkClass, "onError", "(I)V");
}

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeGetName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeGetName
        (JNIEnv *env, jobject obj, jlong instanceId) {
    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (mediaServer) {
        const char *c_name = mediaServer->getName().c_str();
        return env->NewStringUTF(c_name);
    }
    return env->NewStringUTF("");
}

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeGetMediaInfo
 * Signature: (J)Lcom/alan/jniexamples/common/MediaInfo;
 */
JNIEXPORT jobject JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeGetMediaInfo
        (JNIEnv *env, jobject ojb, jlong instanceId) {
    MediaServer * mediaServer = (MediaServer *)instanceId;
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

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeRelease
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeRelease
(JNIEnv *env, jobject obj, jlong instanceId) {
    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (mediaServer) {
        if (mediaServer->getCallbackContext()->jvm != NULL
            && mediaServer->getCallbackContext()->jniCallbackObj != NULL) {
            env->DeleteGlobalRef(mediaServer->getCallbackContext()->jniCallbackObj);
        }

        delete mediaServer;
    }
}

#ifdef __cplusplus
}
#endif
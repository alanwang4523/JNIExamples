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
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_alan_jniexamples_jnistatic_MediaServerStatic */

#ifndef _Included_com_alan_jniexamples_jnistatic_MediaServerStatic
#define _Included_com_alan_jniexamples_jnistatic_MediaServerStatic
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeCreate
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeCreate
        (JNIEnv *, jobject, jstring);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeConfig
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeConfig
        (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeSetMediaParam
 * Signature: (JLcom/alan/jniexamples/common/MediaParam;)I
 */
JNIEXPORT jint JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetMediaParam
        (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeSetCallback
 * Signature: (JLcom/alan/jniexamples/common/MediaServerCallback;)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetCallback
        (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeGetName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeGetName
        (JNIEnv *, jobject, jlong);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeGetMediaInfo
 * Signature: (J)Lcom/alan/jniexamples/common/MediaInfo;
 */
JNIEXPORT jobject JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeGetMediaInfo
        (JNIEnv *, jobject, jlong);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeRelease
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeRelease
        (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif

/**
 * Author: AlanWang4523.
 * Date: 19/5/22 23:30.
 * Mail: alanwang4523@gmail.com
 */

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
 * Signature: (JLcom/alan/jniexamples/common/MediaParam;)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetMediaParam
        (JNIEnv *env, jobject jobj, jlong instanceId, jobject jParam) {

    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (mediaServer) {

    }
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
 * Method:    nativeRelease
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeRelease
(JNIEnv *env, jobject obj, jlong instanceId) {
    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (mediaServer) {
        delete mediaServer;
    }
}

#ifdef __cplusplus
}
#endif
/**
 * Author: AlanWang4523.
 * Date: 19/5/19 22:22.
 * Mail: alanwang4523@gmail.com
 */

#include <jni.h>
#include "common/JNIHelper.h"
#include "common/common.h"

static int MediaServer_native_init(JNIEnv *env, jobject obj) {
    LOGD("MediaServerDynamicJNI", "MediaServer_native_init()-->>\n");
    return 0;
}

static void MediaServer_native_create(JNIEnv *env, jobject obj,jstring strArg) {
    jboolean isCopy;
    // 这里不能直接使用 strArg，需要将其通过 GetStringUTFChars 接口将其转成 UTF-8 的 字符串的指针
    char *cStr = (char *) env->GetStringUTFChars(strArg, &isCopy);
    LOGD("MediaServerDynamicJNI", "MediaServer_native_create()--->cStr = %s", cStr);
    // 最后需要释放，否则可能导致内存泄漏
    env->ReleaseStringUTFChars(strArg, cStr);
}

static int MediaServer_native_config(JNIEnv *env, jobject obj, jint type) {
    LOGD("MediaServerDynamicJNI", "MediaServer_native_config()-->>type = %d\n", type);
    return 0;
}

// Java 层声明 native 方法的类的全路径
static const char *className = "com/alan/jniexamples/dynamic/MediaServerDynamic";

static JNINativeMethod gJni_Methods[] = {
        {"native_init", "()V", (void*)MediaServer_native_init},
        {"native_create", "(Ljava/lang/String;)V", (void*)MediaServer_native_create},
        {"native_config", "(I)V", (void*)MediaServer_native_config},
};

int register_MediaServerDynamic(JNIEnv* env) {
    return jniRegisterNativeMethods(env, className, gJni_Methods, NELEM(gJni_Methods));
}
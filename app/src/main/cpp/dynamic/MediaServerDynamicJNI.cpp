/**
 * Author: AlanWang4523.
 * Date: 19/5/19 22:22.
 * Mail: alanwang4523@gmail.com
 */

#include <jni.h>
#include "common/JNIHelper.h"
#include "common/common.h"
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
        return -1;
    }
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
        {"native_getName", "()Ljava/lang/String;", (void*)MediaServer_native_getName},
        {"native_release", "()V", (void*)MediaServer_native_release},
};

int register_MediaServerDynamic(JNIEnv* env) {
    return jniRegisterNativeMethods(env, className, gJni_Methods, NELEM(gJni_Methods));
}
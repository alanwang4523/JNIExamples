/**
 * Author: AlanWang4523.
 * Date: 19/5/19 23:17.
 * Mail: alanwang4523@gmail.com
 */

#include <jni.h>
#include "common/common.h"

extern int register_NativeDynamic(JNIEnv* env);
extern int register_MediaServerDynamic(JNIEnv* env);

jint JNI_OnLoad(JavaVM* jvm, void* reserved){
    JNIEnv* env = NULL;
    jint result = -1;

    if (jvm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    LOGD("JNIOnLoad", "JNI_OnLoad()--->register_NativeDynamic");
    if (register_NativeDynamic(env) < 0) {
        return result;
    }

    LOGD("JNIOnLoad", "JNI_OnLoad()--->register_MediaServerDynamic");
    if (register_MediaServerDynamic(env) < 0) {
        return result;
    }

    LOGD("JNIOnLoad", "JNI_OnLoad()--->success");
    return JNI_VERSION_1_4;
}
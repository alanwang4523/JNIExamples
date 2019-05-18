

/**
 * Author: AlanWang4523.
 * Date: 19/5/18 14:43.
 * Mail: alanwang4523@gmail.com
 */

#include <jni.h>
#include "common/JNIHelper.h"
#include "common/common.h"

#ifdef __cplusplus
extern "C" {
#endif

static int JNISetBasicArgs(JNIEnv *env, jobject obj,
                                          jint iArg, jfloat fArg, jlong lArg, jboolean bArg) {
    LOGE("NativeDynamicJNI", "JNISetBasicArgs()-->>iArg = %d, fArg = %f, lArg = %ld, bArg = %d\n",
            iArg, fArg, lArg, bArg);
    return 0;
}

static const char *className = "com/alan/jniexamples/dynamic/NativeDynamic";

static JNINativeMethod gJni_Methods[] = {
        {"nativeSetBasicArgs", "(IFJZ)I", (void*)JNISetBasicArgs},
};

jint JNI_OnLoad(JavaVM* jvm, void* reserved){

    JNIEnv* env = NULL;
    jint result = -1;

    if (jvm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    jniRegisterNativeMethods(env, className, gJni_Methods, NELEM(gJni_Methods));

    return JNI_VERSION_1_4;
}

#ifdef __cplusplus
}
#endif
/**
 * Author: AlanWang4523.
 * Date: 19/5/18 14:43.
 * Mail: alanwang4523@gmail.com
 */

#include <jni.h>
#include "common/JNIHelper.h"
#include "common/common.h"

static int JNISetBasicArgs(JNIEnv *env, jobject obj,
                                          jint iArg, jfloat fArg, jlong lArg, jboolean bArg) {
    LOGD("NativeDynamicJNI", "JNISetBasicArgs()-->>iArg = %d, fArg = %f, lArg = %ld, bArg = %d\n",
            iArg, fArg, lArg, bArg);
    return 0;
}

static void JNISetStringArgs(JNIEnv *env, jobject obj,jstring strArg) {
    jboolean iscopy;
    // 这里不能直接使用 strArg，需要将其通过 GetStringUTFChars 接口将其转成 UTF-8 的 字符串的指针
    char *cStr = (char *) env->GetStringUTFChars(strArg, &iscopy);
    LOGD("NativeDynamicJNI", "JNISetStringArgs()--->cStr = %s", cStr);
    // 最后需要释放，否则可能导致内存泄漏
    env->ReleaseStringUTFChars(strArg, cStr);
}

// Java 层声明 native 方法的类的全路径
static const char *className = "com/alan/jniexamples/dynamic/NativeDynamic";

static JNINativeMethod gJni_Methods[] = {
        // 如： nativeSetBasicArgs 是 Java 声明的方法
        // "(IFJZ)I" 是函数签名
        // JNISetBasicArgs 是 C/C++ 声明的方法
        {"nativeSetBasicArgs", "(IFJZ)I", (void*)JNISetBasicArgs},
        {"nativeSetStringArgs", "(Ljava/lang/String;)V", (void*)JNISetStringArgs},
};

int register_NativeDynamic(JNIEnv* env) {
    return jniRegisterNativeMethods(env, className, gJni_Methods, NELEM(gJni_Methods));
}
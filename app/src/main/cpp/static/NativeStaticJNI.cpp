/**
 * Author: AlanWang4523.
 * Date: 19/5/21 21:21.
 * Mail: alanwang4523@gmail.com
 */

#include "common/common.h"
#include "NativeStaticJNI.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_alan_jniexamples_jnistatic_NativeStatic
 * Method:    nativeSetBasicArgs
 * Signature: (IFJZ)I
 */
JNIEXPORT jint JNICALL Java_com_alan_jniexamples_jnistatic_NativeStatic_nativeSetBasicArgs
        (JNIEnv *env, jclass obj, jint iArg, jfloat fArg, jlong lArg, jboolean bArg) {

    LOGD("NativeStaticJNI", "nativeSetBasicArgs()-->>iArg = %d, fArg = %f, lArg = %ld, bArg = %d\n",
         iArg, fArg, lArg, bArg);
    return 0;
}

/*
 * Class:     com_alan_jniexamples_jnistatic_NativeStatic
 * Method:    nativeSetStringArgs
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_NativeStatic_nativeSetStringArgs
(JNIEnv *env, jclass obj, jstring strArg) {
    jboolean iscopy;
    // 这里不能直接使用 strArg，需要将其通过 GetStringUTFChars 接口将其转成 UTF-8 的 字符串的指针
    char *cStr = (char *) env->GetStringUTFChars(strArg, &iscopy);
    LOGD("NativeStaticJNI", "nativeSetStringArgs()--->cStr = %s", cStr);
    // 最后需要释放，否则可能导致内存泄漏
    env->ReleaseStringUTFChars(strArg, cStr);
}

#ifdef __cplusplus
}
#endif
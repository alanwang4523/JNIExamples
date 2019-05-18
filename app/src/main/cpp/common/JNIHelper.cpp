/**
 * Author: AlanWang4523.
 * Date: 19/5/18 12:08.
 * Mail: alanwang4523@gmail.com
 */

#include "JNIHelper.h"
#include "common.h"


int jniRegisterNativeMethods(JNIEnv* env, const char* className, const JNINativeMethod* gMethods, int numMethods) {

    LOGD("JNIHelper", "Start registering %s native methods.\n", className);
    jclass clazz = (env)->FindClass(className);
    if (clazz == NULL) {
        LOGE("JNIHelper", "Native registration unable to find class '%s'.\n", className);
        return -1;
    }

    int result = 0;
    if ((env)->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        LOGE("JNIHelper", "RegisterNatives failed for '%s'.\n", className);
        result = -1;
    }

    (env)->DeleteLocalRef(clazz);
    return result;
}
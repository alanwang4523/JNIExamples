/**
 * Author: AlanWang4523.
 * Date: 19/5/18 12:08.
 * Mail: alanwang4523@gmail.com
 */

#ifndef JNIEXAMPLES_JNIHELPER_H
#define JNIEXAMPLES_JNIHELPER_H

#include <jni.h>

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Register one or more native methods with a particular class.
 * "className" looks like "java/lang/String". Aborts on failure.
 */
int jniRegisterNativeMethods(JNIEnv* env, const char* className, const JNINativeMethod* gMethods, int numMethods);

#ifdef __cplusplus
}
#endif


#endif //JNIEXAMPLES_JNIHELPER_H

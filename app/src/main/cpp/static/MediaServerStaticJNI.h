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
 * Method:    native_create
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_native_1create
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    native_config
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_native_1config
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    native_getName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_native_1getName
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    native_release
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_native_1release
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
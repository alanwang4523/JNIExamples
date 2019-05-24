/**
 * Author: AlanWang4523.
 * Date: 19/5/18 11:42.
 * Mail: alanwang4523@gmail.com
 */

#ifndef JNIEXAMPLES_LOG_H
#define JNIEXAMPLES_LOG_H

#ifdef __ANDROID__
#include <android/log.h>

#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG  , TAG, __VA_ARGS__)
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR  , TAG, __VA_ARGS__)
#endif

#endif //JNIEXAMPLES_LOG_H


/**
 * Author: AlanWang4523.
 * Date: 19/5/24 23:31.
 * Mail: alanwang4523@gmail.com
 */

#ifndef JNIEXAMPLES_COMMON_H
#define JNIEXAMPLES_COMMON_H

typedef struct _MediaParam {
    const char * path;
    long start_time;
    long end_time;
    bool enable_loop;
} MediaParam, *pMediaParam;

#endif //JNIEXAMPLES_COMMON_H

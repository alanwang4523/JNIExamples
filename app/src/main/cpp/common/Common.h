/*
 * Copyright (c) 2019-present AlanWang4523 <alanwang4523@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * Author: AlanWang4523.
 * Date: 19/5/24 23:31.
 * Mail: alanwang4523@gmail.com
 */

#ifndef JNIEXAMPLES_COMMON_H
#define JNIEXAMPLES_COMMON_H


enum {
    SUCCESS = 0,
    ERROR_PARAM = -1001,
};

typedef struct _MediaParam {
    const char * path;
    long start_time;
    long end_time;
    bool enable_loop;
} MediaParam, *pMediaParam;

typedef struct _MediaInfo {
    int sample_rate;
    int chanel_count;
    long duration;
} MediaInfo, *pMediaInfo;

#endif //JNIEXAMPLES_COMMON_H

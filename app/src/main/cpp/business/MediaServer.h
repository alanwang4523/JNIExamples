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
 * Date: 19/5/19 23:49.
 * Mail: alanwang4523@gmail.com
 */

#ifndef JNIEXAMPLES_MEDIASERVER_H
#define JNIEXAMPLES_MEDIASERVER_H

#include <string>
#include "Common.h"

class MediaServer {
public:
    MediaServer(const char * name);
    ~MediaServer();

public:
    int config(int type);
    int setMediaParam(pMediaParam mediaParam);
    std::string getName();
    pMediaInfo getMediaInfo();

private:
    std::string m_name;
    MediaInfo mediaInfo;
};


#endif //JNIEXAMPLES_MEDIASERVER_H

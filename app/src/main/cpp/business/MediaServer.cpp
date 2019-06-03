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

#include "MediaServer.h"
#include "common/Log.h"

MediaServer::MediaServer(const char *name) {
    m_name = name;
    LOGD("MediaServer", "New a MediaServer, name is %s\n", name);
}

MediaServer::~MediaServer() {
    LOGD("MediaServer", "Delete the MediaServer\n");
}

int MediaServer::config(int type) {
    LOGD("MediaServer", "config()-->>instance = %p, type = %d\n", this, type);
    return SUCCESS;
}

int MediaServer::setMediaParam(pMediaParam mediaParam) {
    LOGD("MediaServer", "setMediaParam()-->>instance = %p, path = %s, start_time = %ld, end_time = %ld, enable_loop = %d\n",
            this, mediaParam->path, mediaParam->start_time, mediaParam->end_time, mediaParam->enable_loop);

    // 根据参数或去 media info，也可以在这个方法中返回 mediaInfo
    mediaInfo.sample_rate = 48000;
    mediaInfo.chanel_count = 2;
    mediaInfo.duration = 120 * 1000L;
    return SUCCESS;
}

std::string MediaServer::getName() {
    return m_name;
}

pMediaInfo MediaServer::getMediaInfo()
{
    return &mediaInfo;
}
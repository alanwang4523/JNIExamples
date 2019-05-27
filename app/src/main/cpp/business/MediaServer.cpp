

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
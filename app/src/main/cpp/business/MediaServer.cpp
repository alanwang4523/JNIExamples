

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
    return SUCCESS;
}

std::string MediaServer::getName() {
    return m_name;
}
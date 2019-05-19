

/**
 * Author: AlanWang4523.
 * Date: 19/5/19 23:49.
 * Mail: alanwang4523@gmail.com
 */

#include "MediaServer.h"
#include "common/common.h"

MediaServer::MediaServer(const char *name)
{
    LOGD("MediaServer", "New a MediaServer, name is %s\n", name);
}

MediaServer::~MediaServer()
{
    LOGD("MediaServer", "Delete the MediaServer\n");
}

int MediaServer::config(int type)
{
    LOGD("MediaServer", "config()-->>type = %d\n", type);
    return 0;
}
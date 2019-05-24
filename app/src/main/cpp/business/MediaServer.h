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

private:
    std::string m_name;
};


#endif //JNIEXAMPLES_MEDIASERVER_H

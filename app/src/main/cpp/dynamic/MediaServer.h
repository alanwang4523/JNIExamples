/**
 * Author: AlanWang4523.
 * Date: 19/5/19 23:49.
 * Mail: alanwang4523@gmail.com
 */

#ifndef JNIEXAMPLES_MEDIASERVER_H
#define JNIEXAMPLES_MEDIASERVER_H


class MediaServer {
public:
    MediaServer(const char * name);
    ~MediaServer();

public:
    int config(int type);
};


#endif //JNIEXAMPLES_MEDIASERVER_H

package com.alan.jniexamples.common;

import android.support.annotation.Keep;

/**
 * Author: AlanWang4523.
 * Date: 19/5/24 23:09.
 * Mail: alanwang4523@gmail.com
 */
@Keep
public class MediaParam {
    private String path;
    private long startTimeMs;
    private long endTimeMs;
    private boolean enableLoop;

    public static MediaParam build() {
        return new MediaParam();
    }

    private MediaParam() {
    }

    @Keep
    public String getPath() {
        return path;
    }

    public MediaParam setPath(String path) {
        this.path = path;
        return this;
    }

    @Keep
    public long getStartTimeMs() {
        return startTimeMs;
    }

    public MediaParam setStartTimeMs(long startTimeMs) {
        this.startTimeMs = startTimeMs;
        return this;
    }

    @Keep
    public long getEndTimeMs() {
        return endTimeMs;
    }

    public MediaParam setEndTimeMs(long endTimeMs) {
        this.endTimeMs = endTimeMs;
        return this;
    }

    @Keep
    public boolean isEnableLoop() {
        return enableLoop;
    }

    public MediaParam setEnableLoop(boolean enableLoop) {
        this.enableLoop = enableLoop;
        return this;
    }

    @Override
    public String toString() {
        return "MediaParam{" +
                "path='" + path + '\'' +
                ", startTimeMs=" + startTimeMs +
                ", endTimeMs=" + endTimeMs +
                ", enableLoop=" + enableLoop +
                '}';
    }
}

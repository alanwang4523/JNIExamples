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
    private long startTime;
    private long endTime;
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
    public long getStartTime() {
        return startTime;
    }

    public MediaParam setStartTime(long startTime) {
        this.startTime = startTime;
        return this;
    }

    @Keep
    public long getEndTime() {
        return endTime;
    }

    public MediaParam setEndTime(long endTime) {
        this.endTime = endTime;
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
                ", startTime=" + startTime +
                ", endTime=" + endTime +
                ", enableLoop=" + enableLoop +
                '}';
    }
}

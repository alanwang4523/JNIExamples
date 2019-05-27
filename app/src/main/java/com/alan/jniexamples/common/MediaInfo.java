package com.alan.jniexamples.common;

import android.support.annotation.Keep;

/**
 * Author: AlanWang4523.
 * Date: 19/5/27 21:25.
 * Mail: alanwang4523@gmail.com
 */
@Keep
public class MediaInfo {

    private int sampleRate;
    private int chanelCount;
    private long duration;

    public int getSampleRate() {
        return sampleRate;
    }

    @Keep
    public void setSampleRate(int sampleRate) {
        this.sampleRate = sampleRate;
    }

    public int getChanelCount() {
        return chanelCount;
    }

    @Keep
    public void setChanelCount(int chanelCount) {
        this.chanelCount = chanelCount;
    }

    public long getDuration() {
        return duration;
    }

    @Keep
    public void setDuration(long duration) {
        this.duration = duration;
    }

    @Override
    public String toString() {
        return "MediaInfo{" +
                "sampleRate=" + sampleRate +
                ", chanelCount=" + chanelCount +
                ", duration=" + duration +
                '}';
    }
}

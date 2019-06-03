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

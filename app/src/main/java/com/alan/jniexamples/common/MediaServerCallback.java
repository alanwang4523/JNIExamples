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

/**
 * Author: AlanWang4523.
 * Date: 19/6/3 23:43.
 * Mail: alanwang4523@gmail.com
 */
public interface MediaServerCallback {

    /**
     * @param path
     * @return
     */
    int getImageTexture(String path);

    /**
     * @param errorCode
     */
    void onError(int errorCode);
}

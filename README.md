

# JNIExamples

Examples for JNI (Java Native Interface)



### include:



#### Dynamic registration native methods

```java
    private static native final void native_init();

    static {
        System.loadLibrary("jni_example");
        native_init();
    }
    // 该成员变量名不要改名，与底层保持一致，用于关联底层实例与 java 实例
    private long mNativeContext;

    private native final void native_create(String name);

    private native final void native_config(int type);

    private native final int native_setMediaParam(MediaParam mediaParam);

    private native final void native_setCallback(MediaServerCallback callback);

    private native final String native_getName();

    private native final MediaInfo native_getMediaInfo();

    private native final void native_release();
```

```c
static JNINativeMethod gJni_Methods[] = {
        {"native_init", "()V", (void*)MediaServer_native_init},
        {"native_create", "(Ljava/lang/String;)V", (void*)MediaServer_native_create},
        {"native_config", "(I)V", (void*)MediaServer_native_config},
        {"native_setMediaParam", "(Lcom/alan/jniexamples/common/MediaParam;)I", (void*)MediaServer_native_setMediaParam},
        {"native_setCallback", "(Lcom/alan/jniexamples/common/MediaServerCallback;)V", (void*)MediaServer_native_setCallback},
        {"native_getName", "()Ljava/lang/String;", (void*)MediaServer_native_getName},
        {"native_getMediaInfo", "()Lcom/alan/jniexamples/common/MediaInfo;", (void*)MediaServer_native_getMediaInfo},
        {"native_release", "()V", (void*)MediaServer_native_release},
};

int register_MediaServerDynamic(JNIEnv* env) {
    return jniRegisterNativeMethods(env, className, gJni_Methods, NELEM(gJni_Methods));
}
```



#### Static registration native methods

```java
    private native final long nativeCreate(String name);

    private native final void nativeConfig(long instanceId, int type);

    private native final int nativeSetMediaParam(long instanceId, MediaParam mediaParam);

    private native final void nativeSetCallback(long instanceId, MediaServerCallback callback);

    private native final String nativeGetName(long instanceId);

    private native final MediaInfo nativeGetMediaInfo(long instanceId);

    private native final void nativeRelease(long instanceId);
```

```c
/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeCreate
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeCreate
        (JNIEnv *, jobject, jstring);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeConfig
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeConfig
        (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeSetMediaParam
 * Signature: (JLcom/alan/jniexamples/common/MediaParam;)I
 */
JNIEXPORT jint JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetMediaParam
        (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeSetCallback
 * Signature: (JLcom/alan/jniexamples/common/MediaServerCallback;)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetCallback
        (JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeGetName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeGetName
        (JNIEnv *, jobject, jlong);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeGetMediaInfo
 * Signature: (J)Lcom/alan/jniexamples/common/MediaInfo;
 */
JNIEXPORT jobject JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeGetMediaInfo
        (JNIEnv *, jobject, jlong);

/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeRelease
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeRelease
        (JNIEnv *, jobject, jlong);
```



#### Transfer object to native

**Set java object to native**

```c
/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeSetMediaParam
 * Signature: (JLcom/alan/jniexamples/common/MediaParam;)I
 */
JNIEXPORT jint JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetMediaParam
        (JNIEnv *env, jobject jobj, jlong instanceId, jobject jniParamObj) {

    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (!mediaServer) {
        return ERROR_PARAM;
    }

    int errCode = SUCCESS;

    jclass jclsParamClass = NULL;
    jmethodID jmid = NULL;
    jstring jsFilePath = NULL;

    MediaParam mediaParam;
    mediaParam.path = NULL;

    if ((NULL == env) || (jniParamObj == NULL)) {
        errCode = ERROR_PARAM;
        goto exit;
    }

    jclsParamClass = env->GetObjectClass(jniParamObj);
    if (NULL == jclsParamClass) {
        errCode = ERROR_PARAM;
        goto exit;
    }

    //获取文件路径
    jmid = env->GetMethodID(jclsParamClass, "getPath", "()Ljava/lang/String;");
    if (NULL == jmid) {
        errCode = ERROR_PARAM;
        goto exit;
    }
    jsFilePath = (jstring) env->CallObjectMethod(jniParamObj, jmid);
    if (NULL != jsFilePath) {
        mediaParam.path = env->GetStringUTFChars(jsFilePath, NULL);
    }

    jmid = env->GetMethodID(jclsParamClass, "getStartTime", "()J");
    if (NULL == jmid) {
        errCode = ERROR_PARAM;
        goto exit;
    }
    mediaParam.start_time = env->CallLongMethod(jniParamObj, jmid);

    jmid = env->GetMethodID(jclsParamClass, "getEndTime", "()J");
    if (NULL == jmid) {
        errCode = ERROR_PARAM;
        goto exit;
    }
    mediaParam.end_time = env->CallLongMethod(jniParamObj, jmid);

    jmid = env->GetMethodID(jclsParamClass, "isEnableLoop", "()Z");
    if (NULL == jmid) {
        errCode = ERROR_PARAM;
        goto exit;
    }
    mediaParam.enable_loop = env->CallBooleanMethod(jniParamObj, jmid);

    errCode = mediaServer->setMediaParam(&mediaParam);
exit:
    if (jclsParamClass) {
        env->DeleteLocalRef(jclsParamClass);
    }
    //释放文件路径相关的内存
    if (mediaParam.path) {
        env->ReleaseStringUTFChars(jsFilePath, mediaParam.path);
    }
    if (jsFilePath) {
        env->DeleteLocalRef(jsFilePath);
    }
    return errCode;
}
```

**Return java object from native to java**

```c
/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeGetMediaInfo
 * Signature: (J)Lcom/alan/jniexamples/common/MediaInfo;
 */
JNIEXPORT jobject JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeGetMediaInfo
        (JNIEnv *env, jobject ojb, jlong instanceId) {
    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (!mediaServer) {
        return NULL;
    }

    // 找到要创建的 Java 类
    jclass jclMediaInfo = env->FindClass("com/alan/jniexamples/common/MediaInfo");
    // 获取 Java 类的构造函数及相关方法
    jmethodID jmidConstructor = env->GetMethodID(jclMediaInfo, "<init>", "()V");
    jmethodID jmidSetSampleRate = env->GetMethodID(jclMediaInfo, "setSampleRate", "(I)V");
    jmethodID jmidSetChanelCount = env->GetMethodID(jclMediaInfo, "setChanelCount", "(I)V");
    jmethodID jmidSetDuration = env->GetMethodID(jclMediaInfo, "setDuration", "(J)V");

    // 通过构造函数创建 Java 实例
    jobject jobjMediaInfo = env->NewObject(jclMediaInfo, jmidConstructor);

    // 从 C/C++ 的业务实例获取 Java 层要获取的信息
    pMediaInfo mediaInfo = mediaServer->getMediaInfo();

    // 通过相应的方法给创建的 Java 实例赋值
    env->CallVoidMethod(jobjMediaInfo, jmidSetSampleRate, mediaInfo->sample_rate);
    env->CallVoidMethod(jobjMediaInfo, jmidSetChanelCount, mediaInfo->chanel_count);
    env->CallVoidMethod(jobjMediaInfo, jmidSetDuration, mediaInfo->duration);

    return jobjMediaInfo;
}
```



#### Set callbck to native

```c
/*
 * Class:     com_alan_jniexamples_jnistatic_MediaServerStatic
 * Method:    nativeSetCallback
 * Signature: (JLcom/alan/jniexamples/common/MediaServerCallback;)V
 */
JNIEXPORT void JNICALL Java_com_alan_jniexamples_jnistatic_MediaServerStatic_nativeSetCallback
        (JNIEnv *env, jobject obj, jlong instanceId, jobject jCallback) {
    MediaServer * mediaServer = (MediaServer *)instanceId;
    if (!mediaServer) {
        return;
    }

    memset(mediaServer->getCallbackContext(), 0, sizeof(CallbackContext));
    env->GetJavaVM(&mediaServer->getCallbackContext()->jvm);
    mediaServer->getCallbackContext()->jniCallbackObj = env->NewGlobalRef(jCallback);
    jclass cbkClass = env->GetObjectClass(jCallback);
    mediaServer->getCallbackContext()->jmidGetImageTexture = env->GetMethodID(cbkClass, "getImageTexture", "(Ljava/lang/String;)I");
    mediaServer->getCallbackContext()->jmidOnError = env->GetMethodID(cbkClass, "onError", "(I)V");
}
```



#### Native callback java method

```c
int MediaServer::callbackGetImageTexture(std::string path)
{
    int textureId = -1;
    if (callbackContext.jvm != NULL) {
        JNIEnv *env;
        jint res = callbackContext.jvm->GetEnv((void **) &env, JNI_VERSION_1_4);
        LOGD("MediaServer", "callbackGetImageTexture()-->jvm->GetEnv-->>res = %d", res);
        if (JNI_OK == res) {
            textureId = env->CallIntMethod(callbackContext.jniCallbackObj,
                    callbackContext.jmidGetImageTexture, env->NewStringUTF(path.c_str()));
        } else {
            res = callbackContext.jvm->AttachCurrentThread(&env, NULL);
            LOGD("MediaServer", "callbackGetImageTexture()jvm->AttachCurrentThread-->>res = %d", res);
            if (JNI_OK == res) {
                textureId = env->CallIntMethod(callbackContext.jniCallbackObj,
                        callbackContext.jmidGetImageTexture, env->NewStringUTF(path.c_str()));
                callbackContext.jvm->DetachCurrentThread();
            } else {
                LOGE("MediaServer", "callbackGetImageTexture failed");
            }
        }
    }

    return textureId;
}
```


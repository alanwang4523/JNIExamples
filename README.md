# JNIExamples
Examples for JNI (Java Native Interface)



### include:

- **Static registration native methods** 


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



- **Dynamic registration native methods**

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

- **Transfer basic type to native**
- **Transfer object to native**
- **Set callbck to native**
- **Native callback java method**
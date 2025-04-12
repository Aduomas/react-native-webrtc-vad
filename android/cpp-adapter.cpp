#include <jni.h>
#include "react-native-webrtc-vad.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_webrtcvad_WebrtcVadModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return webrtcvad::multiply(a, b);
}

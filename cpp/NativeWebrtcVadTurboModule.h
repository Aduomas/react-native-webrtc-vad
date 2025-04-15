#pragma once

#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>
#include <string>

// Include WebRTC VAD header
#include "webrtc/common_audio/vad/include/webrtc_vad.h"

// Include Codegen Spec
#if __has_include(<React-Codegen/RNWebrtcVadSpecJSI.h>)
#include <React-Codegen/RNWebrtcVadSpecJSI.h>
#elif __has_include("RNWebrtcVadSpecJSI.h") // Fallback for different build setups
#include "RNWebrtcVadSpecJSI.h"
#else
#error "Could not find RNWebrtcVadSpecJSI.h - Codegen needs to be run"
#endif

namespace facebook::react {

class NativeWebrtcVadTurboModule : public NativeWebrtcVadTurboModuleCxxSpec<NativeWebrtcVadTurboModule> {
public:
    static constexpr const char* kModuleName = "WebrtcVad";
    
    NativeWebrtcVadTurboModule(std::shared_ptr<CallInvoker> jsInvoker);
    ~NativeWebrtcVadTurboModule();
    
    // Simplified interface methods
    jsi::Value processPcm(jsi::Runtime &rt, std::string pcmDataBase64, double sampleRate);
    jsi::Value processMultiplePcm(jsi::Runtime &rt, std::string pcmDataBase64, double sampleRate, double chunkSize);

private:
    // Base64 utility functions
    static std::string base64_encode(const uint8_t* input, size_t length);
    static size_t base64_decode(const std::string& input, uint8_t* output, size_t max_length);
    
    // WebRTC VAD instance (singleton)
    VadInst* vadInst = nullptr;
    bool isInitialized = false;
    
    // Initialize VAD with mode 3 (aggressive) and 16kHz sample rate
    void initializeVAD();
};

} // namespace facebook::react 
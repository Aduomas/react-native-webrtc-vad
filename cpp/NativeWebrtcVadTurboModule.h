#pragma once

#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>
#include <string>

// Include WebRTC VAD header
#include "webrtc/common_audio/vad/include/webrtc_vad.h"

// Include Codegen Spec
#if __has_include(<React-Codegen/RNWebrtcVadSpec.h>)
#include <React-Codegen/RNWebrtcVadSpec.h>
#elif __has_include("RNWebrtcVadSpec.h") // Fallback for different build setups
#include "RNWebrtcVadSpec.h"
#else
#error "Could not find RNWebrtcVadSpec.h - Codegen needs to be run"
#endif

namespace facebook::react {

class NativeWebrtcVadTurboModule : public NativeWebrtcVadSpecCxxSpec<NativeWebrtcVadTurboModule> {
public:
    static constexpr const char* kModuleName = "WebrtcVad";
    
    NativeWebrtcVadTurboModule(std::shared_ptr<CallInvoker> jsInvoker);
    ~NativeWebrtcVadTurboModule();
    
    // Required interface methods (vadId removed)
    jsi::Value createVad(jsi::Runtime &rt, double mode);
    jsi::Value processVadPcm(jsi::Runtime &rt, std::string pcmDataBase64, double sampleRate);
    jsi::Value processMultipleVadPcm(jsi::Runtime &rt, std::string pcmDataBase64, double sampleRate, double chunkSize);
    jsi::Value destroyVad(jsi::Runtime &rt);
    
    // Opus-related methods (stubs - not implemented, vadId removed)
    jsi::Value processVadOpus(jsi::Runtime &rt, std::string opusDataBase64, double decoderId, double sampleRate);
    jsi::Value processMultipleVadOpus(jsi::Runtime &rt, std::string opusDataBase64, double decoderId, double sampleRate, double chunkSize);

private:
    // Base64 utility functions
    static std::string base64_encode(const uint8_t* input, size_t length);
    static size_t base64_decode(const std::string& input, uint8_t* output, size_t max_length);
    
    // WebRTC VAD instance (singleton)
    VadInst* vadInst;
    bool isInitialized;
    
    // Initialize VAD with mode 3 (aggressive) and 16kHz sample rate
    void initializeVAD();
};

} // namespace facebook::react 
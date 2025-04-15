#include "NativeWebrtcVadTurboModule.h"
#include <chrono>

namespace facebook::react {

// Constructor - initialize member variables
NativeWebrtcVadTurboModule::NativeWebrtcVadTurboModule(std::shared_ptr<CallInvoker> jsinvoker)
    : vadInst(nullptr), isInitialized(false) {}

// Destructor - clean up VAD instance
NativeWebrtcVadTurboModule::~NativeWebrtcVadTurboModule() {
    if (vadInst) {
        WebRtcVad_Free(vadInst);
        vadInst = nullptr;
    }
}

// Initialize VAD with mode 3 (aggressive) and 16kHz sample rate
void NativeWebrtcVadTurboModule::initializeVAD() {
    if (!isInitialized) {
        WebRtcVad_Create(&vadInst);
        WebRtcVad_Init(vadInst);
        WebRtcVad_set_mode(vadInst, 3); // Aggressive mode
        // Note: Sample rate is set per process call in WebRTC VAD
        isInitialized = true;
    }
}

// Base64 encoding utility
std::string NativeWebrtcVadTurboModule::base64_encode(const uint8_t* input, size_t length) {
    static const char* encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    static const int mod_table[] = {0, 2, 1};
    
    size_t output_length = 4 * ((length + 2) / 3);
    
    std::string encoded_data(output_length, '\0');
    size_t i, j;
    
    for (i = 0, j = 0; i < length;) {
        uint32_t octet_a = i < length ? input[i++] : 0;
        uint32_t octet_b = i < length ? input[i++] : 0;
        uint32_t octet_c = i < length ? input[i++] : 0;
        
        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;
        
        encoded_data[j++] = encoding_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = encoding_table[triple & 0x3F];
    }
    
    for (i = 0; i < mod_table[length % 3]; i++)
        encoded_data[output_length - 1 - i] = '=';
    
    return encoded_data;
}

// Base64 decoding utility
size_t NativeWebrtcVadTurboModule::base64_decode(const std::string& input, uint8_t* output, size_t max_length) {
    static const int decoding_table[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1,
        -1, -1, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
        29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };
    
    size_t input_length = input.size();
    if (input_length % 4 != 0) return 0;
    
    size_t output_length = input_length / 4 * 3;
    if (input.length() >= 1 && input[input_length - 1] == '=') output_length--;
    if (input.length() >= 2 && input[input_length - 2] == '=') output_length--;
    
    if (output_length > max_length) return 0;
    
    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = input[i] == '=' ? 0 & i++ : decoding_table[static_cast<int>(input[i++])];
        uint32_t sextet_b = input[i] == '=' ? 0 & i++ : decoding_table[static_cast<int>(input[i++])];
        uint32_t sextet_c = input[i] == '=' ? 0 & i++ : decoding_table[static_cast<int>(input[i++])];
        uint32_t sextet_d = input[i] == '=' ? 0 & i++ : decoding_table[static_cast<int>(input[i++])];
        
        uint32_t triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + sextet_d;
        
        if (j < output_length) output[j++] = (triple >> 16) & 0xFF;
        if (j < output_length) output[j++] = (triple >> 8) & 0xFF;
        if (j < output_length) output[j++] = triple & 0xFF;
    }
    
    return output_length;
}

// ProcessPcm implementation (renamed from processVadPcm)
jsi::Value NativeWebrtcVadTurboModule::processPcm(jsi::Runtime &rt, std::string pcmDataBase64, double sampleRate) {
    int fs = static_cast<int>(sampleRate);
    jsi::Object result = jsi::Object(rt);
    
    // Initialize the VAD if not already initialized
    initializeVAD();
    
    // Check if VAD instance is initialized
    if (!vadInst) {
        result.setProperty(rt, "success", false);
        result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, "VAD instance not initialized"));
        return result;
    }
    
    // Start timer for performance measurement
    auto startTime = std::chrono::high_resolution_clock::now();
    
    try {
        // Allocate a buffer for decoded PCM data (reasonable maximum size)
        const size_t MAX_PCM_SIZE = 1024 * 1024; // 1MB should be plenty for audio chunks
        uint8_t* decodedData = new uint8_t[MAX_PCM_SIZE];
        
        // Decode base64 to PCM data
        size_t decodedSize = base64_decode(pcmDataBase64, decodedData, MAX_PCM_SIZE);
        
        if (decodedSize == 0) {
            delete[] decodedData;
            result.setProperty(rt, "success", false);
            result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, "Empty or invalid base64 input"));
            return result;
        }
        
        // Convert bytes to int16_t samples
        size_t numSamples = decodedSize / sizeof(int16_t);
        const int16_t* samples = reinterpret_cast<const int16_t*>(decodedData);
        
        // Validate sample rate and frame length (Using 16000Hz for validation as per initializeVAD)
        if (WebRtcVad_ValidRateAndFrameLength(16000, numSamples) != 0) {
            delete[] decodedData;
            result.setProperty(rt, "success", false);
            result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, "Invalid frame length for 16kHz"));
            return result;
        }
        
        // Process audio frame for voice activity (Using actual sample rate)
        int vadResult = WebRtcVad_Process(vadInst, fs, samples, numSamples);
        
        // Clean up allocated memory
        delete[] decodedData;
        
        if (vadResult < 0) {
            result.setProperty(rt, "success", false);
            result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, "VAD processing error"));
            return result;
        }
        
        // End timer and calculate processing time
        auto endTime = std::chrono::high_resolution_clock::now();
        double processingTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        
        // Return results
        result.setProperty(rt, "success", true);
        result.setProperty(rt, "isVoice", vadResult == 1);
        result.setProperty(rt, "processingTimeMs", processingTime);
        
    } catch (const std::exception& e) {
        result.setProperty(rt, "success", false);
        result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, e.what()));
    }
    
    return result;
}

// ProcessMultiplePcm implementation (renamed from processMultipleVadPcm)
jsi::Value NativeWebrtcVadTurboModule::processMultiplePcm(jsi::Runtime &rt, std::string pcmDataBase64, double sampleRate, double chunkSize) {
    int fs = static_cast<int>(sampleRate);
    int chunkSizeBytes = static_cast<int>(chunkSize);
    jsi::Object result = jsi::Object(rt);
    
    // Initialize the VAD if not already initialized
    initializeVAD();
    
    // Check if VAD instance is initialized
    if (!vadInst) {
        result.setProperty(rt, "success", false);
        result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, "VAD instance not initialized"));
        return result;
    }
    
    // Start timer for performance measurement
    auto startTime = std::chrono::high_resolution_clock::now();
    
    try {
        // Allocate a buffer for decoded PCM data
        const size_t MAX_PCM_SIZE = 10 * 1024 * 1024; // 10MB should be plenty
        uint8_t* decodedData = new uint8_t[MAX_PCM_SIZE];
        
        // Decode base64 to PCM data
        size_t decodedSize = base64_decode(pcmDataBase64, decodedData, MAX_PCM_SIZE);
        
        if (decodedSize == 0) {
            delete[] decodedData;
            result.setProperty(rt, "success", false);
            result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, "Empty or invalid base64 input"));
            return result;
        }
        
        // Calculate the number of samples per chunk
        int samplesPerChunk = chunkSizeBytes / sizeof(int16_t);
        
        // Validate sample rate and frame length (Using 16000Hz for validation)
        if (WebRtcVad_ValidRateAndFrameLength(16000, samplesPerChunk) != 0) {
            delete[] decodedData;
            result.setProperty(rt, "success", false);
            result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, "Invalid frame length for 16kHz"));
            return result;
        }
        
        // Precalculate the number of chunks
        size_t numChunks = decodedSize / chunkSizeBytes;
        
        // Create results array
        jsi::Array resultsArray = jsi::Array(rt, numChunks);
        
        for (size_t i = 0; i < numChunks; i++) {
            size_t offset = i * chunkSizeBytes;
            
            // Get pointer to the current chunk
            const int16_t* chunkSamples = reinterpret_cast<const int16_t*>(decodedData + offset);
            
            // Process audio frame for voice activity (Using actual sample rate)
            int vadResult = WebRtcVad_Process(vadInst, fs, chunkSamples, samplesPerChunk);
            
            if (vadResult < 0) {
                // Just set false for chunks with errors
                resultsArray.setValueAtIndex(rt, i, false);
            } else {
                resultsArray.setValueAtIndex(rt, i, vadResult == 1);
            }
        }
        
        // Clean up allocated memory
        delete[] decodedData;
        
        // End timer and calculate processing time
        auto endTime = std::chrono::high_resolution_clock::now();
        double processingTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        
        // Return results
        result.setProperty(rt, "success", true);
        result.setProperty(rt, "results", resultsArray);
        result.setProperty(rt, "processingTimeMs", processingTime);
        
    } catch (const std::exception& e) {
        result.setProperty(rt, "success", false);
        result.setProperty(rt, "error", jsi::String::createFromUtf8(rt, e.what()));
    }
    
    return result;
}

} // namespace facebook::react 
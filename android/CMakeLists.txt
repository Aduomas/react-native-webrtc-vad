cmake_minimum_required(VERSION 3.13)
project(react-native-webrtc-vad)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(
    -fexceptions
    -frtti
    -std=c++17
)

get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../" ABSOLUTE)
set(SHARED_DIR "${PROJECT_ROOT}/cpp")
set(WEBRTC_DIR "${SHARED_DIR}/webrtc")

# Compile WebRTC VAD source files with C99 standard
file(GLOB WEBRTC_SOURCES 
    "${WEBRTC_DIR}/common_audio/vad/*.c"
    "${WEBRTC_DIR}/common_audio/signal_processing/*.c"
)

# Create the webrtc library
add_library(webrtc STATIC ${WEBRTC_SOURCES})

# Set C99 standard specifically for WebRTC C files and add a system include path for webrtc/ prefix resolution
set_source_files_properties(${WEBRTC_SOURCES} PROPERTIES 
    COMPILE_FLAGS "-std=c99 -Wno-implicit-function-declaration -Wno-deprecated-declarations -I${SHARED_DIR}")

# Define Android platform for WebRTC
target_compile_definitions(webrtc PUBLIC WEBRTC_ANDROID)

# Include directories for webrtc
target_include_directories(webrtc PUBLIC
    ${WEBRTC_DIR}
    ${WEBRTC_DIR}/common_audio/vad/include
    ${WEBRTC_DIR}/common_audio/signal_processing/include
)

# Create the main module library
add_library(react-native-webrtc-vad STATIC
    ${SHARED_DIR}/NativeWebrtcVadTurboModule.cpp
)

# Include directories for the main module
target_include_directories(react-native-webrtc-vad PUBLIC
    ${SHARED_DIR}
    ${WEBRTC_DIR}
)

# Link libraries
target_link_libraries(react-native-webrtc-vad
    webrtc
    jsi
    react_codegen_RNWebrtcVadSpec
)
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

file(GLOB_RECURSE WEBRTC_SOURCES "${WEBRTC_DIR}/*.cpp" "${WEBRTC_DIR}/*.c")

add_library(webrtc STATIC
    ${WEBRTC_SOURCES}
)

add_library(react-native-webrtc-vad STATIC
    ${SHARED_DIR}/NativeWebrtcVadTurboModule.cpp
)

target_include_directories(webrtc
    PUBLIC
    ${WEBRTC_DIR}
)

target_include_directories(react-native-webrtc-vad
    PUBLIC
    ${SHARED_DIR}
)

target_link_libraries(react-native-webrtc-vad
    webrtc
    jsi
    react_codegen_RNWebrtcVadSpec
)
require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))
folly_compiler_flags = '-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1 -Wno-comma -Wno-shorten-64-to-32'

Pod::Spec.new do |s|
  s.name         = "react-native-webrtc-vad"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => min_ios_version_supported }
  s.source       = { :git => "https://github.com/Aduomas/react-native-webrtc-vad.git", :tag => "#{s.version}" }

  # Split source files to handle C files separately
  s.source_files = "ios/**/*.{h,m,mm}", "cpp/**/*.{hpp,cpp,h}"
  
  # Handle C files separately with appropriate flags
  s.preserve_paths = "cpp/**/*.c"
  
  # Add WebRTC defines and paths
  s.pod_target_xcconfig = {
    "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/cpp\" \"$(PODS_TARGET_SRCROOT)/cpp/webrtc\"",
    "CLANG_WARN_DOCUMENTATION_COMMENTS" => "NO",
    "GCC_PREPROCESSOR_DEFINITIONS" => "WEBRTC_POSIX=1"
  }
  
  # Create a subspec for the C files with specific compiler flags
  s.subspec 'webrtc' do |ss|
    ss.source_files = "cpp/**/*.c"
    ss.compiler_flags = "-std=c99 -Wno-implicit-function-declaration -Wno-deprecated-declarations"
    ss.pod_target_xcconfig = {
      "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/cpp/webrtc/common_audio/vad/include\" \"$(PODS_TARGET_SRCROOT)/cpp/webrtc/common_audio/signal_processing/include\""
    }
  end

  # Use install_modules_dependencies helper to install the dependencies if React Native version >=0.71.0.
  if respond_to?(:install_modules_dependencies, true)
    s.compiler_flags = folly_compiler_flags + " -std=c++17"
    install_modules_dependencies(s)
  else
    s.dependency "React-Core"

    # Don't install the dependencies when we run `pod install` in the old architecture.
    if ENV['RCT_NEW_ARCH_ENABLED'] == '1' then
      s.compiler_flags = folly_compiler_flags + " -DRCT_NEW_ARCH_ENABLED=1"
      s.pod_target_xcconfig    = {
          "HEADER_SEARCH_PATHS" => "\"$(PODS_ROOT)/boost\" \"$(PODS_TARGET_SRCROOT)/cpp\" \"$(PODS_TARGET_SRCROOT)/cpp/webrtc\"",
          "OTHER_CPLUSPLUSFLAGS" => "-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1",
          "CLANG_CXX_LANGUAGE_STANDARD" => "c++17",
          "GCC_PREPROCESSOR_DEFINITIONS" => "WEBRTC_POSIX=1"
      }
      s.dependency "React-Codegen"
      s.dependency "RCT-Folly"
      s.dependency "RCTRequired"
      s.dependency "RCTTypeSafety"
      s.dependency "ReactCommon/turbomodule/core"
    end
  end
end
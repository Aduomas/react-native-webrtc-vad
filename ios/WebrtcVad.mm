#import "NativeWebrtcVadTurboModule.h"
#import <Foundation/Foundation.h>
#import <ReactCommon/CxxTurboModuleUtils.h>

@interface WebrtcVadModuleLoader: NSObject
@end

@implementation WebrtcVadModuleLoader

+(void) load {
    facebook::react::registerCxxModuleToGlobalModuleMap(
                                                        std::string(facebook::react::NativeWebrtcVadTurboModule::kModuleName),
                                                        [](std::shared_ptr<facebook::react::CallInvoker> jsInvoker) {
                                                            return std::make_shared<facebook::react::NativeWebrtcVadTurboModule>(jsInvoker);
                                                        }
                                                        );
}

@end
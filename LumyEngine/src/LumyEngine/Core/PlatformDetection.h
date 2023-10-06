#pragma once

#if defined(_WIN32)
    #if defined(_WIN64)
        #define LM_PLATFORM_WINDOWS
        #error "Windows is not supported!"
    #else
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>

    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define LM_PLATFORM_IOS
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #define LM_PLATFORM_MACOS
    #else
        #error "Unknown Apple platform!"
    #endif
#elif defined(__ANDROID__)
    #define LM_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__linux__)
    #define LM_PLATFORM_LINUX
    #error "Linux is not supported!"
#else
    #error "Unknown platform!"
#endif
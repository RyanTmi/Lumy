#pragma once

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define LM_PLATFORM_WINDOWS
    #ifndef _WIN64
        #error "64-bit is required on Windows!"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    // Linux OS
    #define LM_PLATFORM_LINUX
    #if defined(__ANDROID__)
        #define LM_PLATFORM_ANDROID
    #endif
#elif defined(__unix__)
    // Catch anything not caught by the above.
    #define LM_PLATFORM_UNIX
#elif defined(_POSIX_VERSION)
    // Posix
    #define LM_PLATFORM_POSIX
#elif __APPLE__
    // Apple platforms
    #define LM_PLATFORM_APPLE
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
        #define LM_PLATFORM_IOS
        #define LM_PLATFORM_IOS_SIMULATOR
    #elif TARGET_OS_IPHONE
        #define LM_PLATFORM_IOS
    // iOS device
    #elif TARGET_OS_MAC
        #define LM_PLATFORM_MACOS
    #else
        #error "Unknown Apple platform"
    #endif
#else
    #error "Unknown platform!"
#endif

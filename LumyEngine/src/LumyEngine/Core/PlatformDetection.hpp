/**
 * @file PlatformDetection.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Platform detection macros for the game engine.
 * 
 * This file provides macros to detect the target platform during compilation.
 * It defines platform-specific macros such as LM_PLATFORM_WINDOWS, LM_PLATFORM_IOS,
 * LM_PLATFORM_MACOS, LM_PLATFORM_ANDROID, LM_PLATFORM_LINUX, based on the target environment.
 * Additionally, it includes error directives to inform about unsupported platforms.
 * 
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

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


/**
 * @file Assert.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Assertion macros for the game engine.
 * 
 * This file defines assertion macros for the game engine. Assertions are
 * used for runtime checks to catch potential issues during development.
 * The file includes platform-specific debug break functionality for enhanced
 * debugging on supported platforms.
 * 
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#include "LumyEngine/Core/Foundation.hpp"

/**
 * @def LM_DEBUGBREAK
 * @brief Platform-specific debug break macro.
 * @details Triggers a debug break during debugging sessions on supported platforms.
 */
#if defined(LM_DEBUG)
    #if defined(LM_PLATFORM_WINDOWS)
        #define LM_DEBUGBREAK() __debugbreak()
    #else
        #define LM_DEBUGBREAK() __builtin_trap()
    #endif
    #define LM_ASSERTS_ENABLED
#else
    #define LM_DEBUGBREAK()
#endif

#if defined(LM_ASSERTS_ENABLED)
    #define LM_ENGINE_ASSERT(cond)          \
        {                                   \
            if (cond) {                     \
            } else {                        \
                Lumy::Log::Error("Assertion failed : '{}' in {} at line {}", #cond, __FILE__, __LINE__);   \
                LM_DEBUGBREAK();            \
            }                               \
        }
#else
    #define LM_ENGINE_ASSERT(cond)
#endif

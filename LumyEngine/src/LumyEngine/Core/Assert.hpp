/**
 * @file Assert.h
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

/**
 * @def LM_CORE_ASSERT
 * @brief Core assertion macro for runtime checks.
 * @details Checks the specified condition and triggers a debug break on failure
 * if assertions are enabled. Logs an error message with file and line information.
 * @param cond The condition to check.
 */
#if defined(LM_ASSERTS_ENABLED)
    #define LM_CORE_ASSERT(cond)            \
        {                                   \
            if (cond) {                     \
            } else {                        \
                LM_CORE_LOG_ERROR("Assertion failed : '{}' in {} at line {}", #cond, __FILE__, __LINE__);   \
                LM_DEBUGBREAK();            \
            }                               \
        }
#else
    #define LM_CORE_ASSERT(cond)
#endif

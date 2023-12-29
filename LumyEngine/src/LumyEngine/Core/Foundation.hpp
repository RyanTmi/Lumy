/**
 * @file Foundation.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Core foundation header for the game engine.
 *
 * This file serves as the central foundation header for the game engine,
 * including essential components such as platform detection, fundamental types,
 * logging, and assertions.
 * 
 * @version 0.2
 * @date 2023-11-18
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#if defined(LM_EXPORT)
    #if defined(_MSC_VER)
        #define LUMY_API __declspec(dllexport)
    #else
        #define LUMY_API __attribute__((visibility("default")))
    #endif
#else
    #if defined(_MSC_VER)
        #define LUMY_API __declspec(dllimport)
    #else
        #define LUMY_API
    #endif
#endif

// TODO: temporary
#include "Memory/Memory.hpp"

#include "Containers/Array.hpp"
#include "Containers/Vector.hpp"
#include "Containers/Map.hpp"
#include "Containers/Set.hpp"
#include "Containers/String.hpp"

#include "PlatformDetection.hpp"
#include "Types.hpp"

#include "Logging/Log.hpp"
#include "Assert.hpp"




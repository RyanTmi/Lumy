#pragma once

#include "PlatformDetection.h"

#if defined(LM_DEBUG)
    #if defined(LM_PLATFORM_WINDOWS)
        #define LM_DEBUGBREAK() __debugbreak()
    #else
        #define LM_DEBUGBREAK() __builtin_trap()
    #endif
    #define LM_ENABLE_ASSERTS
#else
    #define LM_DEBUGBREAK()
#endif

#define BIT(x) (1 << x)

#include "LumyEngine/Core/DataTypes.h"

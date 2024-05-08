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

#include <iostream>

namespace lumy
{
    LUMY_API auto lumy_engine() -> void;
}

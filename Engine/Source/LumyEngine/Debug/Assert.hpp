#pragma once

#include "LumyEngine/Debug/Log.hpp"

#if defined(_MSC_VER)
    #define LM_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__)
    #define LM_DEBUG_BREAK() __builtin_debugtrap()
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
    #define LM_DEBUG_BREAK() __asm__ volatile("int $0x03")
#elif defined(__GNUC__) && defined(__thumb__)
    #define LM_DEBUG_BREAK() __asm__ volatile(".inst 0xde01")
#elif defined(__GNUC__) && defined(__arm__) && !defined(__thumb__)
    #define LM_DEBUG_BREAK() __asm__ volatile(".inst 0xe7f001f0")
#else
    #define LM_DEBUG_BREAK()
#endif

namespace Lumy
{
#ifdef LM_DEBUG
    static constexpr bool Debug = true;
#else
    static constexpr bool Debug = false;
#endif

    inline constexpr auto Assert(const bool condition) -> void
    {
        if constexpr (Debug)
        {
            if (!condition)
            {
                LM_DEBUG_BREAK();
            }
        }
    }

    template <typename... Args>
    inline constexpr auto Assert(const bool condition, std::format_string<Args...> format, Args&&... args) -> void
    {
        if constexpr (Debug)
        {
            if (!condition)
            {
                Log::Error(format, std::forward<Args>(args)...);
                LM_DEBUG_BREAK();
            }
        }
    }
}

#pragma once

#include "LumyEngine/Core/Event/Event.hpp"
#include "LumyEngine/Core/Input/KeyCode.hpp"

#include <format>

namespace Lumy
{
    //==================================================================================================================
    // Struct : KeyPressEvent
    //==================================================================================================================

    struct KeyPressEvent final
    {
        static constexpr EventType Type = EventType::KeyPress;

        const KeyCode Key;

        explicit KeyPressEvent(const KeyCode key)
            : Key(key)
        {}
    };

    //==================================================================================================================
    // Struct : KeyReleaseEvent
    //==================================================================================================================

    struct KeyReleaseEvent final
    {
        static constexpr EventType Type = EventType::KeyRelease;

        const KeyCode Key;

        explicit KeyReleaseEvent(const KeyCode key)
            : Key(key)
        {}
    };
}

namespace std
{
    //==================================================================================================================
    // Struct : KeyPressEvent
    //==================================================================================================================

    template <>
    struct formatter<Lumy::KeyPressEvent>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::KeyPressEvent& e, auto& context) const
        {
            return std::format_to(context.out(), "KeyPressEvent: {}", static_cast<int>(e.Key));
        }
    };

    //==================================================================================================================
    // Struct : KeyReleaseEvent
    //==================================================================================================================

    template <>
    struct formatter<Lumy::KeyReleaseEvent>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::KeyReleaseEvent& e, auto& context) const
        {
            return std::format_to(context.out(), "KeyReleaseEvent: {}", static_cast<int>(e.Key));
        }
    };
}

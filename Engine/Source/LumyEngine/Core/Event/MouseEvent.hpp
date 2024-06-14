#pragma once

#include "LumyEngine/Core/Event/Event.hpp"
#include "LumyEngine/Core/Input/MouseButton.hpp"

#include <format>

namespace Lumy
{
    //==================================================================================================================
    // Struct : MouseButtonPressEvent
    //==================================================================================================================

    struct MouseButtonPressEvent final
    {
        static constexpr EventType Type = EventType::MousePress;

        const MouseButton Button;

        explicit MouseButtonPressEvent(const MouseButton button)
            : Button(button)
        {}
    };

    //==================================================================================================================
    // Struct : MouseButtonReleaseEvent
    //==================================================================================================================

    struct MouseButtonReleaseEvent final
    {
        static constexpr EventType Type = EventType::MouseRelease;

        const MouseButton Button;

        explicit MouseButtonReleaseEvent(const MouseButton button)
            : Button(button)
        {}
    };

    //==================================================================================================================
    // Struct : MouseMoveEvent
    //==================================================================================================================

    struct MouseMoveEvent final
    {
        static constexpr EventType Type = EventType::MouseMove;

        const Float64 X = 0.0;
        const Float64 Y = 0.0;

        MouseMoveEvent(const Float64 x, const Float64 y)
            : X(x), Y(y)
        {}
    };

    //==================================================================================================================
    // Struct : MouseScrollEvent
    //==================================================================================================================

    struct MouseScrollEvent final
    {
        static constexpr EventType Type = EventType::MouseScroll;

        const Float64 XOffset = 0.0;
        const Float64 YOffset = 0.0;

        MouseScrollEvent(const Float64 xOffset, const Float64 yOffset)
            : XOffset(xOffset), YOffset(yOffset)
        {}
    };
}

namespace std
{
    //==================================================================================================================
    // Struct : MouseButtonPressEvent
    //==================================================================================================================

    template <>
    struct formatter<Lumy::MouseButtonPressEvent>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::MouseButtonPressEvent& e, auto& context) const
        {
            return std::format_to(context.out(), "MouseButtonPressEvent: {}", static_cast<int>(e.Button));
        }
    };

    //==================================================================================================================
    // Struct : MouseButtonReleaseEvent
    //==================================================================================================================

    template <>
    struct formatter<Lumy::MouseButtonReleaseEvent>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::MouseButtonReleaseEvent& e, auto& context) const
        {
            return std::format_to(context.out(), "MouseButtonReleaseEvent: {}", static_cast<int>(e.Button));
        }
    };

    //==================================================================================================================
    // Struct : MouseMoveEvent
    //==================================================================================================================

    template <>
    struct formatter<Lumy::MouseMoveEvent>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::MouseMoveEvent& e, auto& context) const
        {
            return std::format_to(context.out(), "MouseMoveEvent: ({}, {})", e.X, e.Y);
        }
    };

    //==================================================================================================================
    // Struct : MouseScrollEvent
    //==================================================================================================================

    template <>
    struct formatter<Lumy::MouseScrollEvent>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::MouseScrollEvent& e, auto& context) const
        {
            return std::format_to(context.out(), "MouseScrollEvent: ({}, {})", e.XOffset, e.YOffset);
        }
    };
}

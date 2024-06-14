#pragma once

#include "LumyEngine/Core/Event/Event.hpp"

#include <format>

namespace Lumy
{
    //==================================================================================================================
    // Struct : WindowResizeEvent
    //==================================================================================================================

    struct WindowResizeEvent final
    {
        static constexpr EventType Type = EventType::WindowResize;

        const UInt32 Width;
        const UInt32 Height;

        WindowResizeEvent(const UInt32 width, const UInt32 height)
            : Width(width), Height(height)
        {}
    };

    //==================================================================================================================
    // Struct : WindowCloseEvent
    //==================================================================================================================

    struct WindowCloseEvent final
    {
        static constexpr EventType Type = EventType::WindowClose;
    };
}

namespace std
{
    //==================================================================================================================
    // Struct : WindowResizeEvent
    //==================================================================================================================

    template <>
    struct formatter<Lumy::WindowResizeEvent>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::WindowResizeEvent& e, auto& context) const
        {
            return std::format_to(context.out(), "WindowResize: ({}, {})", e.Width, e.Height);
        }
    };

    //==================================================================================================================
    // Struct : WindowCloseEvent
    //==================================================================================================================

    template <>
    struct formatter<Lumy::WindowCloseEvent>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::WindowCloseEvent& e, auto& context) const
        {
            return std::format_to(context.out(), "WindowClose");
        }
    };
}

#pragma once

#include "Event.hpp"

namespace Lumy
{
    struct WindowResizeEvent final : public Event
    {
        WindowResizeEvent(UInt16 width, UInt16 height);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;

        const UInt16 Width;
        const UInt16 Height;
    };

    struct WindowCloseEvent final : public Event
    {
        WindowCloseEvent() = default;

        EventType Type() const override;
        const char* Name() const override;
    };
}

#include "WindowEvent.inl"

#pragma once

#include "Event.hpp"

namespace Lumy
{
    struct MouseButtonEvent : public Event
    {
        const UInt16 Button;

        MouseButtonEvent() = delete;
    protected:
        explicit MouseButtonEvent(UInt16 button);
    };

    struct MouseButtonPressedEvent final : public MouseButtonEvent
    {
        explicit MouseButtonPressedEvent(UInt16 button);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;
    };

    struct MouseButtonReleasedEvent final : public MouseButtonEvent
    {
        explicit MouseButtonReleasedEvent(UInt16 button);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;
    };

    struct MouseMovedEvent final : public Event
    {
        MouseMovedEvent(Float32 mouseX, Float32 mouseY);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;

        const Float32 MouseX;
        const Float32 MouseY;
    };

    struct MouseScrolledEvent final : public Event
    {
        MouseScrolledEvent(Float32 xOffset, Float32 yOffset);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;

        const Float32 XOffset;
        const Float32 YOffset;
    };
}

#include "MouseEvent.inl"

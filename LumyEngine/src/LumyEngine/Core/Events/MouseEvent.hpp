#pragma once

#include "Event.hpp"

namespace Lumy
{

#pragma region MouseButtonEvent

    struct MouseButtonEvent : public Event
    {
        const UInt16 Button;

        MouseButtonEvent() = delete;
    protected:
        explicit MouseButtonEvent(UInt16 button);
    };

#pragma endregion MouseButtonEvent

#pragma region MouseButtonPressedEvent

    struct MouseButtonPressedEvent final : public MouseButtonEvent
    {
        explicit MouseButtonPressedEvent(UInt16 button);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;
    };

#pragma endregion MouseButtonPressedEvent

#pragma region MouseButtonReleasedEvent

    struct MouseButtonReleasedEvent final : public MouseButtonEvent
    {
        explicit MouseButtonReleasedEvent(UInt16 button);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;
    };

#pragma endregion MouseButtonReleasedEvent

#pragma region MouseMovedEvent

    struct MouseMovedEvent final : public Event
    {
        MouseMovedEvent(Float32 mouseX, Float32 mouseY);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;

        const Float32 MouseX;
        const Float32 MouseY;
    };

#pragma endregion MouseMovedEvent

#pragma region MouseScrolledEvent

    struct MouseScrolledEvent final : public Event
    {
        MouseScrolledEvent(Float32 xOffset, Float32 yOffset);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;

        const Float32 XOffset;
        const Float32 YOffset;
    };

#pragma endregion MouseScrolledEvent

}

#include "MouseEvent.inl"

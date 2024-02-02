#pragma once

#include "LumyEngine/Core/Input/KeyCode.hpp"
#include "LumyEngine/Core/Input/MouseButton.hpp"

#include "Event.hpp"

namespace Lumy
{
#pragma region MouseButtonEvent

    struct MouseButtonEvent : public Event
    {
        const MouseButton Button;

        MouseButtonEvent() = delete;
    protected:
        explicit MouseButtonEvent(MouseButton button);
    };

#pragma endregion MouseButtonEvent

#pragma region MouseButtonPressedEvent

    struct MouseButtonPressedEvent final : public MouseButtonEvent
    {
        explicit MouseButtonPressedEvent(MouseButton button);

        EventType Type() const override;
        const char* Name() const override;
        String ToString() const override;
    };

#pragma endregion MouseButtonPressedEvent

#pragma region MouseButtonReleasedEvent

    struct MouseButtonReleasedEvent final : public MouseButtonEvent
    {
        explicit MouseButtonReleasedEvent(MouseButton button);

        EventType Type() const override;
        const char* Name() const override;
        String ToString() const override;
    };

#pragma endregion MouseButtonReleasedEvent

#pragma region MouseMovedEvent

    struct MouseMovedEvent final : public Event
    {
        MouseMovedEvent(Float32 mouseX, Float32 mouseY);

        EventType Type() const override;
        const char* Name() const override;
        String ToString() const override;

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
        String ToString() const override;

        const Float32 XOffset;
        const Float32 YOffset;
    };

#pragma endregion MouseScrolledEvent

#pragma region MouseButtonEvent

    inline MouseButtonEvent::MouseButtonEvent(MouseButton button)
        : Button(button)
    {
    }

#pragma endregion MouseButtonEvent

#pragma region MouseButtonPressedEvent

    inline MouseButtonPressedEvent::MouseButtonPressedEvent(MouseButton button)
        : MouseButtonEvent(button)
    {
    }

    inline EventType MouseButtonPressedEvent::Type() const
    {
        return EventType::MouseButtonPress;
    }

    inline const char* MouseButtonPressedEvent::Name() const
    {
        return "MouseButtonPressedEvent";
    }

    inline String MouseButtonPressedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "MouseButtonPressedEvent : " << static_cast<UInt16>(Button);
        return oss.str();
    }

#pragma endregion MouseButtonPressedEvent

#pragma region MouseButtonReleasedEvent

    inline MouseButtonReleasedEvent::MouseButtonReleasedEvent(MouseButton button)
        : MouseButtonEvent(button) {}

    inline EventType MouseButtonReleasedEvent::Type() const
    {
        return EventType::MouseButtonRelease;
    }

    inline const char* MouseButtonReleasedEvent::Name() const
    {
        return "MouseButtonReleasedEvent";
    }

    inline String MouseButtonReleasedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "MouseButtonReleasedEvent : " << static_cast<UInt16>(Button);
        return oss.str();
    }

#pragma endregion MouseButtonReleasedEvent

#pragma region MouseMovedEvent

    inline MouseMovedEvent::MouseMovedEvent(Float32 mouseX, Float32 mouseY)
        : MouseX(mouseX), MouseY(mouseY)
    {
    }

    inline EventType MouseMovedEvent::Type() const
    {
        return EventType::MouseMove;
    }

    inline const char* MouseMovedEvent::Name() const
    {
        return "MouseMoveEvent";
    }

    inline String MouseMovedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "MouseMoveEvent : " << MouseX << ", " << MouseY;
        return oss.str();
    }

#pragma endregion MouseMovedEvent

#pragma region MouseScrolledEvent

    inline MouseScrolledEvent::MouseScrolledEvent(Float32 xOffset, Float32 yOffset)
        : XOffset(xOffset), YOffset(yOffset)
    {
    }

    inline EventType MouseScrolledEvent::Type() const
    {
        return EventType::MouseScroll;
    }

    inline const char* MouseScrolledEvent::Name() const
    {
        return "MouseScrolledEvent";
    }

    inline String MouseScrolledEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "MouseScrolledEvent : " << XOffset << ", " << YOffset;
        return oss.str();
    }

#pragma endregion MouseScrolledEvent
}

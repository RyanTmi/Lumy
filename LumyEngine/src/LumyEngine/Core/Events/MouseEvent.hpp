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


namespace Lumy
{

#pragma region MouseButtonEvent

    inline MouseButtonEvent::MouseButtonEvent(UInt16 button)
        : Button(button)
    {
    }

#pragma endregion MouseButtonEvent

#pragma region MouseButtonPressedEvent

    inline MouseButtonPressedEvent::MouseButtonPressedEvent(UInt16 button)
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

    inline std::string MouseButtonPressedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "MouseButtonPressedEvent : " << Button;
        return oss.str();
    }

#pragma endregion MouseButtonPressedEvent

#pragma region MouseButtonReleasedEvent

    inline MouseButtonReleasedEvent::MouseButtonReleasedEvent(UInt16 button)
        : MouseButtonEvent(button) {}

    inline EventType MouseButtonReleasedEvent::Type() const
    {
        return EventType::MouseButtonRelease;
    }

    inline const char* MouseButtonReleasedEvent::Name() const
    {
        return "MouseButtonReleasedEvent";
    }

    inline std::string MouseButtonReleasedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "MouseButtonReleasedEvent : " << Button;
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

    inline std::string MouseMovedEvent::ToString() const
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

    inline std::string MouseScrolledEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "MouseScrolledEvent : " << XOffset << ", " << YOffset;
        return oss.str();
    }

#pragma endregion MouseScrolledEvent

}

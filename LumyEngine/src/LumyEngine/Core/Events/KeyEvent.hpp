#pragma once

#include "Event.hpp"

namespace Lumy
{

#pragma region KeyEvent

    struct KeyEvent : public Event
    {
        const UInt16 KeyCode;

    protected:
        explicit KeyEvent(UInt16 keycode);
    };

#pragma endregion KeyEvent

#pragma region KeyPressedEvent

    struct KeyPressedEvent final : public KeyEvent
    {
        explicit KeyPressedEvent(UInt16 keycode);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;
    };

#pragma endregion KeyPressedEvent

#pragma region KeyReleasedEvent

    struct KeyReleasedEvent final : public KeyEvent
    {
        explicit KeyReleasedEvent(UInt16 keycode);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;
    };

#pragma endregion KeyReleasedEvent

}

namespace Lumy
{

#pragma region KeyEvent

    inline KeyEvent::KeyEvent(UInt16 keycode)
        : KeyCode(keycode)
    {
    }

#pragma endregion KeyEvent

#pragma region KeyPressedEvent

    inline KeyPressedEvent::KeyPressedEvent(UInt16 keycode)
        : KeyEvent(keycode) {}

    inline EventType KeyPressedEvent::Type() const
    {
        return EventType::KeyPress;
    }

    inline const char* KeyPressedEvent::Name() const
    {
        return "KeyPressEvent";
    }

    inline std::string KeyPressedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "KeyPressEvent : " << KeyCode;
        return oss.str();
    }

#pragma endregion KeyPressedEvent

#pragma region KeyReleasedEvent

    inline KeyReleasedEvent::KeyReleasedEvent(UInt16 keycode)
            : KeyEvent(keycode) {}

    inline EventType KeyReleasedEvent::Type() const
    {
        return EventType::KeyRelease;
    }

    inline const char* KeyReleasedEvent::Name() const
    {
        return "KeyReleasedEvent";
    }

    inline std::string KeyReleasedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "KeyReleasedEvent : " << KeyCode;
        return oss.str();
    }

#pragma endregion KeyReleasedEvent

}

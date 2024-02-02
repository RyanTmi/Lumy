#pragma once

#include "LumyEngine/Core/Input/KeyCode.hpp"
#include "LumyEngine/Core/Input/MouseButton.hpp"

#include "Event.hpp"

namespace Lumy
{
#pragma region KeyEvent

    struct KeyEvent : public Event
    {
        const KeyCode Code;

    protected:
        explicit KeyEvent(KeyCode code);
    };

#pragma endregion KeyEvent

#pragma region KeyPressedEvent

    struct KeyPressedEvent final : public KeyEvent
    {
        explicit KeyPressedEvent(KeyCode code);

        EventType Type() const override;
        const char* Name() const override;
        String ToString() const override;
    };

#pragma endregion KeyPressedEvent

#pragma region KeyReleasedEvent

    struct KeyReleasedEvent final : public KeyEvent
    {
        explicit KeyReleasedEvent(KeyCode code);

        EventType Type() const override;
        const char* Name() const override;
        String ToString() const override;
    };

#pragma endregion KeyReleasedEvent

#pragma region KeyEvent

    inline KeyEvent::KeyEvent(KeyCode code)
        : Code(code)
    {
    }

#pragma endregion KeyEvent

#pragma region KeyPressedEvent

    inline KeyPressedEvent::KeyPressedEvent(KeyCode code)
        : KeyEvent(code) {}

    inline EventType KeyPressedEvent::Type() const
    {
        return EventType::KeyPress;
    }

    inline const char* KeyPressedEvent::Name() const
    {
        return "KeyPressEvent";
    }

    inline String KeyPressedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "KeyPressEvent : " << static_cast<UInt16>(Code);
        return oss.str();
    }

#pragma endregion KeyPressedEvent

#pragma region KeyReleasedEvent

    inline KeyReleasedEvent::KeyReleasedEvent(KeyCode code)
            : KeyEvent(code) {}

    inline EventType KeyReleasedEvent::Type() const
    {
        return EventType::KeyRelease;
    }

    inline const char* KeyReleasedEvent::Name() const
    {
        return "KeyReleasedEvent";
    }

    inline String KeyReleasedEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "KeyReleasedEvent : " << static_cast<UInt16>(Code);
        return oss.str();
    }

#pragma endregion KeyReleasedEvent
}

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

#include "KeyEvent.inl"

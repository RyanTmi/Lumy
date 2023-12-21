#pragma once

#include "Event.hpp"

namespace Lumy
{
    struct KeyEvent : public Event
    {
        const UInt16 KeyCode;

    protected:
        explicit KeyEvent(UInt16 keycode);
    };

    struct KeyPressedEvent final : public KeyEvent
    {
        explicit KeyPressedEvent(UInt16 keycode);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;
    };

    struct KeyReleasedEvent final : public KeyEvent
    {
        explicit KeyReleasedEvent(UInt16 keycode);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;
    };
}

#include "KeyEvent.inl"

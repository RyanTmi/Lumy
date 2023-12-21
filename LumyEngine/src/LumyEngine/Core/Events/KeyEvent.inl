#pragma once

namespace Lumy
{
    inline KeyEvent::KeyEvent(UInt16 keycode)
        : KeyCode(keycode)
    {
    }


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
}
#pragma once

#include "Event.hpp"

namespace Lumy
{
    class KeyEvent : public Event
    {
    public:
        u16 GetKeyCode() const { return m_KeyCode; }
    protected:
        explicit KeyEvent(const u16 keycode)
            : m_KeyCode(keycode) {}

        const u16 m_KeyCode; // TODO : Change to KeyCode type
    };

    class KeyPressedEvent final : public KeyEvent
    {
    public:
        explicit KeyPressedEvent(const u16 keycode)
            : KeyEvent(keycode) {}

        EventType GetEventType() const override { return EventType::KeyPress; }
        const char* GetName() const override { return "KeyPressEvent"; }
        std::string ToString() const override
        {
            std::ostringstream oss;
            oss << "KeyPressEvent : " << m_KeyCode;
            return oss.str();
        }
    };

    class KeyReleasedEvent final : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(const u16 keycode)
            : KeyEvent(keycode) {}

        EventType GetEventType() const override { return EventType::KeyRelease; }
        const char* GetName() const override { return "KeyReleasedEvent"; }
        std::string ToString() const override
        {
            std::ostringstream oss;
            oss << "KeyReleasedEvent : " << m_KeyCode;
            return oss.str();
        }
    };
}

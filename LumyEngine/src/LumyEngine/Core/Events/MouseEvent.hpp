#pragma once

#include "Event.hpp"

namespace Lumy
{
    class MouseButtonEvent : public Event
    {
    public:
        u16 GetButton() const { return m_Button; }
    protected:
        explicit MouseButtonEvent(const u16 button)
            : m_Button(button) {}

        const u16 m_Button; // TODO : Change to MouseButton type
    };

    class MouseButtonPressedEvent final : public MouseButtonEvent
    {
    public:
        explicit MouseButtonPressedEvent(const u16 button)
            : MouseButtonEvent(button) {}

        EventType GetEventType() const override { return EventType::MouseButtonPress; }
        const char* GetName() const override { return "MouseButtonPressedEvent"; }
        std::string ToString() const override
        {
            std::ostringstream oss;
            oss << "MouseButtonPressedEvent : " << m_Button;
            return oss.str();
        }
    };

    class MousebuttonReleasedEvent final : public MouseButtonEvent
    {
    public:
        explicit MousebuttonReleasedEvent(const u16 button)
            : MouseButtonEvent(button) {}

        EventType GetEventType() const override { return EventType::MouseButtonRelease; }
        const char* GetName() const override { return "MousebuttonReleasedEvent"; }
        std::string ToString() const override
        {
            std::ostringstream oss;
            oss << "MousebuttonReleasedEvent : " << m_Button;
            return oss.str();
        }
    };

    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent(const f32 mouseX, const f32 mouseY)
            : m_MouseX(mouseX), m_MouseY(mouseY) {}

        f32 GetMouseX() const { return m_MouseX; }
        f32 GetMouseY() const { return m_MouseY; }

        EventType GetEventType() const override { return EventType::MouseMove; }
        const char* GetName() const override { return "MouseMoveEvent"; }
        std::string ToString() const override
        {
            std::ostringstream oss;
            oss << "MouseMoveEvent : " << m_MouseX << ", " << m_MouseY;
            return oss.str();
        }
    private:
        const f32 m_MouseX;
        const f32 m_MouseY;
    };

    class MouseScrolledEvent final : public Event
    {
    public:
        MouseScrolledEvent(const f32 xOffset, const f32 yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        f32 GetXOffset() const { return m_XOffset; }
        f32 GetYOffset() const { return m_YOffset; }

        EventType GetEventType() const override { return EventType::MouseScroll; }
        const char* GetName() const override { return "MouseScrolledEvent"; }
        std::string ToString() const override
        {
            std::ostringstream oss;
            oss << "MouseScrolledEvent : " << m_XOffset << ", " << m_YOffset;
            return oss.str();
        }
    private:
        const f32 m_XOffset;
        const f32 m_YOffset;
    };
}

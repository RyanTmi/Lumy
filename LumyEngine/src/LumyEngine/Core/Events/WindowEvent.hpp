#pragma once

#include "Event.hpp"

namespace Lumy
{
    class WindowResizeEvent final : public Event
    {
    public:
        WindowResizeEvent(const u16 width, const u16 height)
            : m_Width(width), m_Height(height) {}

        u16 GetWidth() const { return m_Width; }
        u16 GetHeight() const { return m_Height; }

        EventType GetEventType() const override { return EventType::WindowResize; }
        const char* GetName() const override { return "WindowResizeEvent"; }
        std::string ToString() const override
        {
            std::ostringstream oss;
            oss << "WindowResizeEvent : " << m_Width << ", " << m_Height;
            return oss.str();
        }
    private:
        const u16 m_Width;
        const u16 m_Height;
    };

    class WindowCloseEvent final : public Event
    {
    public:
        WindowCloseEvent() = default;

        EventType GetEventType() const override { return EventType::WindowClose; }
        const char* GetName() const override { return "WindowCloseEvent"; }
    };
}

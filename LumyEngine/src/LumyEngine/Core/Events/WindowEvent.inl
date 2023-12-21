#pragma once

namespace Lumy
{
    inline WindowResizeEvent::WindowResizeEvent(UInt16 width, UInt16 height)
        : Width(width), Height(height)
    {
    }

    inline EventType WindowResizeEvent::Type() const
    {
        return EventType::WindowResize;
    }

    inline const char* WindowResizeEvent::Name() const
    {
        return "WindowResizeEvent";
    }

    inline std::string WindowResizeEvent::ToString() const
    {
        std::ostringstream oss;
        oss << "WindowResizeEvent : " << Width << ", " << Height;
        return oss.str();
    }

    inline EventType WindowCloseEvent::Type() const
    {
        return EventType::WindowClose;
    }

    inline const char* WindowCloseEvent::Name() const
    {
        return "WindowCloseEvent";
    }

}
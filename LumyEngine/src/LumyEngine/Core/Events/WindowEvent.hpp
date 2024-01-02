#pragma once

#include "Event.hpp"

namespace Lumy
{

#pragma region WindowResizeEvent

    struct WindowResizeEvent final : public Event
    {
        WindowResizeEvent(UInt16 width, UInt16 height);

        EventType Type() const override;
        const char* Name() const override;
        std::string ToString() const override;

        const UInt16 Width;
        const UInt16 Height;
    };

#pragma endregion WindowResizeEvent

#pragma region WindowCloseEvent

    struct WindowCloseEvent final : public Event
    {
        WindowCloseEvent() = default;

        EventType Type() const override;
        const char* Name() const override;
    };
}

#pragma endregion WindowCloseEvent


namespace Lumy
{

#pragma region WindowResizeEvent

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

#pragma endregion WindowResizeEvent

#pragma region WindowCloseEvent

    inline EventType WindowCloseEvent::Type() const
    {
        return EventType::WindowClose;
    }

    inline const char* WindowCloseEvent::Name() const
    {
        return "WindowCloseEvent";
    }

#pragma endregion WindowCloseEvent

}

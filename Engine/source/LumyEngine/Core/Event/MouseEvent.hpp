#pragma once

#include "LumyEngine/Core/Event/Event.hpp"
#include "LumyEngine/Core/Input/MouseButton.hpp"

#include <ostream>

namespace Lumy
{
    //==============================================================================================
    // Struct : MouseButtonPressEvent
    //==============================================================================================

    struct MouseButtonPressEvent final
    {
        static constexpr EventType Type = EventType::MousePress;

        const MouseButton Button;

        explicit MouseButtonPressEvent(const MouseButton button)
            : Button(button)
        {}
    };

    inline std::ostream& operator<<(std::ostream& out, MouseButtonPressEvent e)
    {
        return out << "MouseButtonPressEvent: " << static_cast<int>(e.Button);
    }

    //==============================================================================================
    // Struct : MouseButtonReleaseEvent
    //==============================================================================================

    struct MouseButtonReleaseEvent final
    {
        static constexpr EventType Type = EventType::MouseRelease;

        const MouseButton Button;

        explicit MouseButtonReleaseEvent(const MouseButton button)
            : Button(button)
        {}
    };

    inline std::ostream& operator<<(std::ostream& out, MouseButtonReleaseEvent e)
    {
        return out << "MouseButtonReleaseEvent: " << static_cast<int>(e.Button);
    }

    //==============================================================================================
    // Struct : MouseMoveEvent
    //==============================================================================================

    struct MouseMoveEvent final
    {
        static constexpr EventType Type = EventType::MouseMove;

        const Float64 X = 0.0;
        const Float64 Y = 0.0;

        MouseMoveEvent(const Float64 x, const Float64 y)
            : X(x), Y(y)
        {}
    };

    inline std::ostream& operator<<(std::ostream& out, MouseMoveEvent e)
    {
        return out << "MouseMoveEvent: (" << e.X << ", " << e.Y << ")";
    }

    //==============================================================================================
    // Struct : MouseScrollEvent
    //==============================================================================================

    struct MouseScrollEvent final
    {
        static constexpr EventType Type = EventType::MouseScroll;

        const Float64 XOffset = 0.0;
        const Float64 YOffset = 0.0;

        MouseScrollEvent(const Float64 xOffset, const Float64 yOffset)
            : XOffset(xOffset), YOffset(yOffset)
        {}
    };

    inline std::ostream& operator<<(std::ostream& out, MouseScrollEvent e)
    {
        return out << "MouseScrollEvent: (" << e.XOffset << ", " << e.YOffset << ")";
    }
}

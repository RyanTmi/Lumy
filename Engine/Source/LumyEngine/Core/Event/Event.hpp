#pragma once

#include "LumyEngine/Core/Types.hpp"

#include <concepts>

namespace Lumy
{
    enum class EventType : UInt8
    {
        KeyPress,
        KeyRelease,

        MouseMove,
        MouseScroll,
        MousePress,
        MouseRelease,

        WindowClose,
        WindowResize
    };

    template <typename E>
    concept Event = requires() { std::same_as<decltype(E::Type), const EventType>; };
}

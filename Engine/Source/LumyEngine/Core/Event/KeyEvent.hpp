#pragma once

#include "LumyEngine/Core/Event/Event.hpp"
#include "LumyEngine/Core/Input/KeyCode.hpp"

#include <ostream>

namespace Lumy
{
    //==============================================================================================
    // Struct : KeyPressEvent
    //==============================================================================================

    struct KeyPressEvent final
    {
        static constexpr EventType Type = EventType::KeyPress;

        const KeyCode Key;

        explicit KeyPressEvent(const KeyCode key)
            : Key(key)
        {}
    };

    inline std::ostream& operator<<(std::ostream& out, KeyPressEvent e)
    {
        return out << "KeyPressEvent: " << static_cast<int>(e.Key);
    }

    //==============================================================================================
    // Struct : KeyReleaseEvent
    //==============================================================================================

    struct KeyReleaseEvent final
    {
        static constexpr EventType Type = EventType::KeyRelease;

        const KeyCode Key;

        explicit KeyReleaseEvent(const KeyCode key)
            : Key(key)
        {}
    };

    inline std::ostream& operator<<(std::ostream& out, KeyReleaseEvent e)
    {
        return out << "KeyPressEvent: " << static_cast<int>(e.Key);
    }
}

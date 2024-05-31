#pragma once

#include "LumyEngine/Core/Types.hpp"

#include <ostream>
#include <string_view>

namespace Lumy
{
    enum class KeyCode : UInt16
    {
        None,

        Alpha0,
        Alpha1,
        Alpha2,
        Alpha3,
        Alpha4,
        Alpha5,
        Alpha6,
        Alpha7,
        Alpha8,
        Alpha9,

        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Apostrophe,
        Backslash,
        Comma,
        Equal,
        GraveAccent,
        LeftBracket,
        Minus,
        Period,
        RightBracket,
        Semicolon,
        Slash,

        LeftAlt,
        LeftControl,
        LeftShift,
        LeftSuper,

        RightAlt,
        RightControl,
        RightShift,
        RightSuper,

        Keypad0,
        Keypad1,
        Keypad2,
        Keypad3,
        Keypad4,
        Keypad5,
        Keypad6,
        Keypad7,
        Keypad8,
        Keypad9,
        KeypadAdd,
        KeypadPeriod,
        KeypadDivide,
        KeypadEnter,
        KeypadEqual,
        KeypadMultiply,
        KeypadSubtract,

        Up,
        Down,
        Right,
        Left,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,

        Backspace,
        CapsLock,
        Delete,
        End,
        Enter,
        Escape,
    };

    // TODO: move to Inputs static function to handle modifiers
    inline std::string_view to_string(KeyCode key)
    {
        switch (key)
        {
            using enum KeyCode;

            default: return "";
        }
    }

    // std::ostream& operator<<(std::ostream& out, KeyCode key)
    // {
    //     return out << to_string(key);
    // }
}

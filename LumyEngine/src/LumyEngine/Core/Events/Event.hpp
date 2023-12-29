/**
 * @file Event.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#include "LumyEngine/Core/Foundation.hpp"

namespace Lumy
{
    enum class EventType
    {
        WindowResize, WindowClose,
        KeyPress, KeyRelease,
        MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
    };

    struct Event
    {
    public:
        virtual ~Event() = default;

        virtual EventType Type() const = 0;
        virtual const char* Name() const = 0;

        virtual String ToString() const
        {
            return Name();
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}

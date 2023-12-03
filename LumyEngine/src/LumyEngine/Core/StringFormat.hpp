/**
 * @file StringFormat.hpp
 * @author Ryan Timeus
 * @brief Static class for string formatting.
 *
 * @version 0.2
 * @date 2023-11-19
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */ 

#pragma once

#include <string>

namespace Lumy
{
    class StringFormat
    {
    public:
        template <typename... Args>
        static std::string Format(std::string_view format, Args... args);

        static std::string CurrentDate() { return CurrentDateTime("%Y-%m-%d"); }
        static std::string CurrentTime() { return CurrentDateTime("%H:%M:%S"); }
    private:
        static std::string CurrentDateTime(const char* format);
    };
}

#include "StringFormat.inl"

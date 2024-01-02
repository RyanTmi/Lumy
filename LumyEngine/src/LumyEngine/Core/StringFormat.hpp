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
#include <sstream>

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


namespace Lumy
{
    template <typename... Args>
    std::string StringFormat::Format(std::string_view format, Args... args)
    {
        static auto format_helper = [](std::ostringstream& oss, std::string_view& str, const auto& value)
        {
            const std::size_t openBracket = str.find('{');
            if (openBracket == std::string::npos)
            {
                return;
            }
            const std::size_t closeBracket = str.find('}', openBracket + 1);
            if (closeBracket == std::string::npos)
            {
                return;
            }
            oss << str.substr(0, openBracket) << value;
            str = str.substr(closeBracket + 1);
        };

        std::ostringstream oss;
        (format_helper(oss, format, args), ...);
        oss << format;
        return oss.str();
    }
}

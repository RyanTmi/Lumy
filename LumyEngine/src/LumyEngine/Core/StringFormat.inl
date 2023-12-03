#pragma once
#include <sstream>

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

#include "StringFormat.hpp"

#include <iomanip>
#include <sstream>

namespace Lumy
{
    /**
     * @brief Helper function for formatting a string with the current date and time.
     * @param format Format string.
     */
    std::string StringFormat::CurrentDateTime(const char* format)
    {
        const std::time_t now = std::time(nullptr);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now), format);
        return oss.str();
    }
}

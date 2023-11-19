#include "StringUtils.hpp"

#include <iomanip>

namespace Lumy::Utils
{
    /**
     * @brief Helper function for formatting a string with the current date and time.
     * @param outStream Output stream to write the formatted date and time.
     * @param format Format string.
     */
    static void GetCurrentDateTime(std::ostringstream& outStream, const char* format)
    {
        std::time_t now = std::time(nullptr);
        outStream << std::put_time(std::localtime(&now), format);
    }

    void GetCurrentDate(std::ostringstream& outStream)
    {
        GetCurrentDateTime(outStream, "%Y-%m-%d");
    }

    void GetCurrentTime(std::ostringstream& outStream)
    {
        GetCurrentDateTime(outStream, "%H:%M:%S");
    }
}
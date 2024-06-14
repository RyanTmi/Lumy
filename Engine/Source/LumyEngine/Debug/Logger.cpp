#include "LumyEngine/Debug/Log.hpp"
#include "Logger.hpp"

#include <iostream>

namespace Lumy
{
    Logger::Logger(const std::filesystem::path& logFilePath)
        : m_LogFileStream(logFilePath)
    {}

    auto Logger::LogConsole(std::string_view message, bool isError) const -> void
    {
        (isError ? std::cerr : std::cout) << message << '\n';
    }

    auto Logger::LogFile(std::string_view message) -> void
    {
        if (m_LogFileStream.is_open())
        {
            m_LogFileStream << message << '\n';
        }
    }
}

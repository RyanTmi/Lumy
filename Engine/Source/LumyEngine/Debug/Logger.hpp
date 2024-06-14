#pragma once

#include <format>
#include <fstream>

namespace Lumy
{
    //==================================================================================================================
    // Class : Logger
    //==================================================================================================================

    class Logger final
    {
    public:
        enum class Level
        {
            Trace,
            Debug,
            Info,
            Warn,
            Error,
            Fatal,
        };

    public:
        Logger() = default;
        Logger(const std::filesystem::path& logFilePath);

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

    public:
        template <typename... Args>
        auto Log(Level level, std::format_string<Args...> format, Args&&... args) -> void;

        auto IsLogFileOpen() const -> bool { return m_LogFileStream.is_open(); }

    private:
        auto LogConsole(std::string_view message, bool isError) const -> void;
        auto LogFile(std::string_view message) -> void;

    private:
        std::ofstream m_LogFileStream;
    };

    //==================================================================================================================
    // Class : Logger
    //==================================================================================================================

    template <typename... Args>
    auto Logger::Log(Logger::Level level, std::format_string<Args...> format, Args&&... args) -> void
    {
        std::string message = std::format(format, std::forward<Args>(args)...);
        bool isError = (level == Level::Error or level == Level::Fatal);
        LogConsole(message, isError);
        LogFile(message);
    }
}

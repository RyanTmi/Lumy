#pragma once

#include <format>
#include <iostream>
#include <string_view>

namespace Lumy
{
    class Logger
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

        template <typename... Args>
        auto Log(Level level, std::format_string<Args...> format, Args&&... args) -> void;
    };

    class Log
    {
    public:
        template <typename... Args>
        static auto Trace(std::format_string<Args...> format, Args&&... args) -> void;

        template <typename... Args>
        static auto Debug(std::format_string<Args...> format, Args&&... args) -> void;

        template <typename... Args>
        static auto Info(std::format_string<Args...> format, Args&&... args) -> void;

        template <typename... Args>
        static auto Warn(std::format_string<Args...> format, Args&&... args) -> void;

        template <typename... Args>
        static auto Error(std::format_string<Args...> format, Args&&... args) -> void;

        template <typename... Args>
        static auto Fatal(std::format_string<Args...> format, Args&&... args) -> void;

    private:
        static Logger s_Logger;
    };

    template <typename... Args>
    auto Logger::Log(Logger::Level level, std::format_string<Args...> format,
                     Args&&... args) -> void
    {
        std::string output = std::format(format, std::forward<Args>(args)...);
        bool isError = (level == Level::Error or level == Level::Fatal);
        (isError ? std::cerr : std::cout) << output << '\n';
    }

    template <typename... Args>
    auto Log::Trace(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_Logger.Log(Logger::Level::Trace, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Log::Debug(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_Logger.Log(Logger::Level::Debug, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Log::Info(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_Logger.Log(Logger::Level::Info, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Log::Warn(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_Logger.Log(Logger::Level::Warn, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Log::Error(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_Logger.Log(Logger::Level::Error, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Log::Fatal(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_Logger.Log(Logger::Level::Fatal, format, std::forward<Args>(args)...);
    }
}

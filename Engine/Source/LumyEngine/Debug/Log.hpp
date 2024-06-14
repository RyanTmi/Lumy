#pragma once

#include "LumyEngine/Debug/Logger.hpp"

namespace Lumy
{
    //==================================================================================================================
    // Class : Log
    //==================================================================================================================

    class Log final
    {
    public:
        static auto Initialize() -> bool;
        static auto Shutdown() -> void;

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
        static Logger s_CoreLogger;
    };

    //==================================================================================================================
    // Class : Log
    //==================================================================================================================

    template <typename... Args>
    inline auto Log::Trace(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_CoreLogger.Log(Logger::Level::Trace, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto Log::Debug(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_CoreLogger.Log(Logger::Level::Debug, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto Log::Info(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_CoreLogger.Log(Logger::Level::Info, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto Log::Warn(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_CoreLogger.Log(Logger::Level::Warn, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto Log::Error(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_CoreLogger.Log(Logger::Level::Error, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto Log::Fatal(std::format_string<Args...> format, Args&&... args) -> void
    {
        s_CoreLogger.Log(Logger::Level::Fatal, format, std::forward<Args>(args)...);
    }
}

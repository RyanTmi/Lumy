/**
 * @file Log.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Definition of the static Log class.
 * @version 0.2
 * @date 2023-11-20
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#include "Logger.hpp"

namespace Lumy
{
    /**
     * @brief Static Log class providing access to core and client loggers.
     */
    class Log
    {
    public:
        /**
         * @brief Initializes the Log class.
         */
        static void Initialize();

        /**
         * @brief Gets the core logger.
         * @return Shared pointer to the core logger.
         */
        static std::shared_ptr<Logger> GetEngineLogger() { return s_EngineLogger; }

        /**
         * @brief Gets the client logger.
         * @return Shared pointer to the client logger.
         */
        static std::shared_ptr<Logger> GetClientLogger() { return s_ClientLogger; }
    public:
        template <typename ...Args>
        static void Trace(Args&& ...args) { s_EngineLogger->Log(Logger::Level::Trace, args...); }

        template <typename ...Args>
        static void Debug(Args&& ...args) { s_EngineLogger->Log(Logger::Level::Debug, args...); }

        template <typename ...Args>
        static void Info(Args&& ...args) { s_EngineLogger->Log(Logger::Level::Info, args...); }

        template <typename ...Args>
        static void Warn(Args&& ...args) { s_EngineLogger->Log(Logger::Level::Warn, args...); }

        template <typename ...Args>
        static void Error(Args&& ...args) { s_EngineLogger->Log(Logger::Level::Error, args...); }

        template <typename ...Args>
        static void Fatal(Args&& ...args) { s_EngineLogger->Log(Logger::Level::Fatal, args...); }
    public:
        Log() = delete;
        ~Log() = delete;

        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;

    private:
        static std::shared_ptr<Logger> s_EngineLogger;
        static std::shared_ptr<Logger> s_ClientLogger;
    };

    template <typename ...Args>
    static void LogTrace(Args&& ...args) { Log::GetClientLogger()->Log(Logger::Level::Trace, args...); }

    template <typename ...Args>
    static void LogDebug(Args&& ...args) { Log::GetClientLogger()->Log(Logger::Level::Debug, args...); }

    template <typename ...Args>
    static void LogInfo(Args&& ...args) { Log::GetClientLogger()->Log(Logger::Level::Info, args...); }

    template <typename ...Args>
    static void LogWarn(Args&& ...args) { Log::GetClientLogger()->Log(Logger::Level::Warn, args...); }

    template <typename ...Args>
    static void LogError(Args&& ...args) { Log::GetClientLogger()->Log(Logger::Level::Error, args...); }

    template <typename ...Args>
    static void LogFatal(Args&& ...args) { Log::GetClientLogger()->Log(Logger::Level::Fatal, args...); }
}

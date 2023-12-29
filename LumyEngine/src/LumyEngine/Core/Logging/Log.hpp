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

#include "LumyEngine/Core/Module.hpp"

namespace Lumy
{
    class Log : public Module
    {
    public:
        static Log& Get();
    public:
        void Initialize() override;
        void Update() override;
        void Shutdown() override;

        SharedRef<Logger> EngineLogger() { return m_EngineLogger; }
        SharedRef<Logger> ClientLogger() { return m_ClientLogger; }
    public:
        template <typename ...Args>
        static void Trace(Args&& ...args) { Get().m_EngineLogger->Log(Logger::Level::Trace, args...); }

        template <typename ...Args>
        static void Debug(Args&& ...args) { Get().m_EngineLogger->Log(Logger::Level::Debug, args...); }

        template <typename ...Args>
        static void Info(Args&& ...args) { Get().m_EngineLogger->Log(Logger::Level::Info, args...); }

        template <typename ...Args>
        static void Warn(Args&& ...args) { Get().m_EngineLogger->Log(Logger::Level::Warn, args...); }

        template <typename ...Args>
        static void Error(Args&& ...args) { Get().m_EngineLogger->Log(Logger::Level::Error, args...); }

        template <typename ...Args>
        static void Fatal(Args&& ...args) { Get().m_EngineLogger->Log(Logger::Level::Fatal, args...); }
    private:
        SharedRef<Logger> m_EngineLogger;
        SharedRef<Logger> m_ClientLogger;
    };

    template <typename ...Args>
    static void LogTrace(Args&& ...args) { Log::Get().ClientLogger()->Log(Logger::Level::Trace, args...); }

    template <typename ...Args>
    static void LogDebug(Args&& ...args) { Log::Get().ClientLogger()->Log(Logger::Level::Debug, args...); }

    template <typename ...Args>
    static void LogInfo(Args&& ...args) { Log::Get().ClientLogger()->Log(Logger::Level::Info, args...); }

    template <typename ...Args>
    static void LogWarn(Args&& ...args) { Log::Get().ClientLogger()->Log(Logger::Level::Warn, args...); }

    template <typename ...Args>
    static void LogError(Args&& ...args) { Log::Get().ClientLogger()->Log(Logger::Level::Error, args...); }

    template <typename ...Args>
    static void LogFatal(Args&& ...args) { Log::Get().ClientLogger()->Log(Logger::Level::Fatal, args...); }
}

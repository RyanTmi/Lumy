// TODO - Documentation Needed

#pragma once

#include "Logger.h"

#include <memory>

namespace Lumy
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<Logger> GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<Logger> GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<Logger> s_CoreLogger;
        static std::shared_ptr<Logger> s_ClientLogger;
    };
}


#define LM_CORE_LOG_TRACE(...)   ::Lumy::Log::GetCoreLogger()->Log(Lumy::Logger::Level::Trace, ##__VA_ARGS__)
#define LM_CORE_LOG_DEBUG(...)   ::Lumy::Log::GetCoreLogger()->Log(Lumy::Logger::Level::Debug, ##__VA_ARGS__)
#define LM_CORE_LOG_INFO(...)    ::Lumy::Log::GetCoreLogger()->Log(Lumy::Logger::Level::Info, ##__VA_ARGS__)
#define LM_CORE_LOG_WARN(...)    ::Lumy::Log::GetCoreLogger()->Log(Lumy::Logger::Level::Warn, ##__VA_ARGS__)
#define LM_CORE_LOG_ERROR(...)   ::Lumy::Log::GetCoreLogger()->Log(Lumy::Logger::Level::Error, ##__VA_ARGS__)
#define LM_CORE_LOG_FATAL(...)   ::Lumy::Log::GetCoreLogger()->Log(Lumy::Logger::Level::Fatal, ##__VA_ARGS__)

#define LM_LOG_TRACE(...)        ::Lumy::Log::GetClientLogger()->Log(Lumy::Logger::Level::TRACE, ##__VA_ARGS__)
#define LM_LOG_DEBUG(...)        ::Lumy::Log::GetClientLogger()->Log(Lumy::Logger::Level::DEBUG, ##__VA_ARGS__)
#define LM_LOG_INFO(...)         ::Lumy::Log::GetClientLogger()->Log(Lumy::Logger::Level::INFO, ##__VA_ARGS__)
#define LM_LOG_WARN(...)         ::Lumy::Log::GetClientLogger()->Log(Lumy::Logger::Level::WARN, ##__VA_ARGS__)
#define LM_LOG_ERROR(...)        ::Lumy::Log::GetClientLogger()->Log(Lumy::Logger::Level::ERROR, ##__VA_ARGS__)
#define LM_LOG_FATAL(...)        ::Lumy::Log::GetClientLogger()->Log(Lumy::Logger::Level::FATAL, ##__VA_ARGS__)

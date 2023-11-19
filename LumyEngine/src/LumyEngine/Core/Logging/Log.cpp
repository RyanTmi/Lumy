#include "Log.hpp"

namespace Lumy
{
    std::shared_ptr<Logger> Log::s_CoreLogger;
    std::shared_ptr<Logger> Log::s_ClientLogger;

    void Log::Init()
    {
        auto configFlags = Logger::ConfigFlag_Time | Logger::ConfigFlag_Level | Logger::ConfigFlag_Name;

        Log::s_CoreLogger = std::make_shared<Logger>(static_cast<Logger::ConfigFlag>(configFlags), "Lumy");
        Log::s_ClientLogger = std::make_shared<Logger>(static_cast<Logger::ConfigFlag>(configFlags), "Client");

        LM_CORE_LOG_INFO("Log initialized !");
    }
}

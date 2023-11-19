#include "Log.hpp"

namespace Lumy
{
    std::shared_ptr<Logger> Log::s_EngineLogger;
    std::shared_ptr<Logger> Log::s_ClientLogger;

    void Log::Init()
    {
        Logger::Config consoleConfig
        {
            static_cast<Logger::FormatFlag>(Logger::FormatFlag_Level | Logger::FormatFlag_Name),
            true
        };
        Logger::Config logFileConfig
        {
            static_cast<Logger::FormatFlag>(Logger::FormatFlag_Time | Logger::FormatFlag_Level | Logger::FormatFlag_Name),
            true
        };

        Log::s_EngineLogger = std::make_shared<Logger>("Lumy", consoleConfig, logFileConfig);
        Log::s_ClientLogger = std::make_shared<Logger>("Client", consoleConfig);

        LM_CORE_LOG_INFO("Log initialized !");
    }
}

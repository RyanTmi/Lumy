#include "Log.hpp"

namespace Lumy
{
    std::shared_ptr<Logger> Log::s_EngineLogger;
    std::shared_ptr<Logger> Log::s_ClientLogger;

    void Log::Initialize()
    {
        Logger::Config consoleConfig
        {
            static_cast<Logger::FormatFlag>(Logger::FormatFlag_Level | Logger::FormatFlag_Name),
            true
        };
        Logger::Config logFileConfig
        {
            static_cast<Logger::FormatFlag>(Logger::FormatFlag_Time | Logger::FormatFlag_Level),
            true
        };

        s_EngineLogger = std::make_shared<Logger>("Lumy", consoleConfig, logFileConfig);
        s_ClientLogger = std::make_shared<Logger>("Client", consoleConfig);

        Info("Log initialized !");
    }
}

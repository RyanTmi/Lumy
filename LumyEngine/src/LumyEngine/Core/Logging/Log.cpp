#include "Log.hpp"

namespace Lumy
{
    Log& Log::Get()
    {
        static Log instance;
        return instance;
    }

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

        m_EngineLogger = std::make_shared<Logger>("Lumy", consoleConfig, logFileConfig);
        m_ClientLogger = std::make_shared<Logger>("Client", consoleConfig);
    }

    void Log::Update()
    {
    }

    void Log::Shutdown()
    {
    };
}

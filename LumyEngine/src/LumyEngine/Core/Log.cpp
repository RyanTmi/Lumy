#include "Log.h"

namespace Lumy
{
    std::shared_ptr<Logger> Log::s_CoreLogger;
    std::shared_ptr<Logger> Log::s_ClientLogger;

    void Log::Init()
    {
        Logger::FormatFlag formatFlags = Logger::FormatFlag::Time |
                                         Logger::FormatFlag::Level |
                                         Logger::FormatFlag::Name;

        Log::s_CoreLogger = std::make_shared<Logger>(formatFlags, "Lumy");
        Log::s_ClientLogger = std::make_shared<Logger>(formatFlags, "Client");
    }
}

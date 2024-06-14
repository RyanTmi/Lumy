#include "Log.hpp"

namespace Lumy
{
    Logger Log::s_CoreLogger;

    auto Log::Initialize() -> bool
    {
        // TODO: Init log file
        return true;
    }

    auto Log::Shutdown() -> void {}
}

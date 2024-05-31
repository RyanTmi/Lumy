#include "LumyEngine/Core/Event/CoreEvents.hpp"

#include "LumyEngine/Debug/Logger.hpp"

namespace Lumy
{
    CoreEvents::Listeners CoreEvents::s_Listeners;

    auto CoreEvents::Initialize() -> bool
    {
        return true;
    }

    auto CoreEvents::Shutdown() -> void
    {
        s_Listeners.clear();
    }
}

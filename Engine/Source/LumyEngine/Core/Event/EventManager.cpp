#include "LumyEngine/Core/Event/EventManager.hpp"

#include "LumyEngine/Debug/Log.hpp"

namespace Lumy
{
    EventManager::Listeners EventManager::s_Listeners;

    auto EventManager::Initialize() -> bool
    {
        return true;
    }

    auto EventManager::Shutdown() -> void
    {
        s_Listeners.clear();
    }
}

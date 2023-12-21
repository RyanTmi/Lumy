#include "EventManager.hpp"

#include "WindowEvent.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"

namespace Lumy
{
    EventManager& EventManager::Instance()
    {
        static EventManager instance;
        return instance;
    }

    void EventManager::PublishEvents()
    {
        while (const auto& event = Instance().m_EventQueue.DequeueEvent())
        {
            Instance().m_EventDispatcher.Dispatch(*event);
        }
    }

    void EventManager::SendEvent(const Event& event)
    {
        Instance().m_EventDispatcher.Dispatch(event);
    }
}

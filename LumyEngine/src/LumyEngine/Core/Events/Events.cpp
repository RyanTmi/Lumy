#include "Events.hpp"

#include "WindowEvent.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"

namespace Lumy
{
    Events& Events::Get()
    {
        static Events instance;
        return instance;
    }

    void Events::Initialize()
    {

    }

    void Events::Update()
    {

    }

    void Events::Shutdown()
    {

    }

    void Events::PublishEvents()
    {
        while (const auto& event = m_EventQueue.DequeueEvent())
        {
            m_EventDispatcher.Dispatch(*event);
        }
    }

    void Events::SendEvent(const Event& event)
    {
        m_EventDispatcher.Dispatch(event);
    }
}

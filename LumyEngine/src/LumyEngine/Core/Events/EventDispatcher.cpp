#include "EventDispatcher.hpp"

#include "WindowEvent.hpp"
#include "MouseEvent.hpp"
#include "KeyEvent.hpp"

namespace Lumy
{
    void EventDispatcher::Dispatch(const Event& event) const
    {
        EventType type = event.Type();

        if (m_Listeners.find(type) == m_Listeners.end())
        {
            return;
        }

        for (const auto& listener : m_Listeners.at(type))
        {
            listener->Invoke(event);
        }
    }

    std::unordered_map<std::type_index, EventType> const EventDispatcher::s_EventClassMap =
    {
        { typeid(WindowCloseEvent), EventType::WindowClose },
        { typeid(WindowResizeEvent), EventType::WindowResize },

        { typeid(KeyPressedEvent), EventType::KeyPress },
        { typeid(KeyReleasedEvent), EventType::KeyRelease },

        { typeid(MouseButtonPressedEvent),  EventType::MouseButtonPress },
        { typeid(MouseButtonReleasedEvent), EventType::MouseButtonRelease },
        { typeid(MouseScrolledEvent),  EventType::MouseScroll },
        { typeid(MouseMovedEvent),  EventType::MouseMove }
    };
}
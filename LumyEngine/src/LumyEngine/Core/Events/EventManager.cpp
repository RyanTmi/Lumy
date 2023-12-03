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

    void EventManager::InvokeEvent(const Event& event)
    {
        for (const auto& listener : m_Subscribers[event.GetEventType()])
        {
            listener->DispatchEvent(event);
        }
    }

    std::unordered_map<std::type_index, EventType> const EventManager::s_EventClassMap =
    {
        { typeid(WindowCloseEvent), EventType::WindowClose },
        { typeid(WindowResizeEvent), EventType::WindowResize },

        { typeid(KeyPressedEvent), EventType::KeyPress },
        { typeid(KeyReleasedEvent), EventType::KeyRelease },

        { typeid(MouseButtonPressedEvent),  EventType::MouseButtonPress },
        { typeid(MousebuttonReleasedEvent), EventType::MouseButtonRelease },
        { typeid(MouseScrolledEvent),  EventType::MouseScroll },
        { typeid(MouseMovedEvent),  EventType::MouseMove }
    };
}

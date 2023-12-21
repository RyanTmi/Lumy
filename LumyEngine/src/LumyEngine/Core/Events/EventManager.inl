#pragma once

namespace Lumy
{
    template <typename EventClass, typename>
    void EventManager::Subscribe(const typename EventClassListener<EventClass>::EventCallback& callback)
    {
        Instance().m_EventDispatcher.AddListener<EventClass>(callback);
    }

    template <typename EventClass, typename>
    void EventManager::Unsubscribe(const typename EventClassListener<EventClass>::EventCallback& callback)
    {
        Instance().m_EventDispatcher.RemoveListener<EventClass>(callback);
    }

    template <typename EventClass, typename... Args, typename>
    void EventManager::QueueEvent(Args&&... args)
    {
        Instance().m_EventQueue.QueueEvent(std::make_unique<EventClass>(std::forward<Args>(args)...));
    }
}

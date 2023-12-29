#pragma once

namespace Lumy
{
    template <typename EventClass, typename>
    inline void Events::Subscribe(const typename EventClassListener<EventClass>::EventCallback& callback)
    {
        m_EventDispatcher.AddListener<EventClass>(callback);
    }

    template <typename EventClass, typename>
    inline void Events::Unsubscribe(const typename EventClassListener<EventClass>::EventCallback& callback)
    {
        m_EventDispatcher.RemoveListener<EventClass>(callback);
    }

    template <typename EventClass, typename... Args, typename>
    inline void Events::QueueEvent(Args&&... args)
    {
        m_EventQueue.QueueEvent(std::make_unique<EventClass>(std::forward<Args>(args)...));
    }
}

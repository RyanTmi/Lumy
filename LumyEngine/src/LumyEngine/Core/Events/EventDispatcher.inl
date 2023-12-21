#pragma once

namespace Lumy
{
    template <typename EventClass>
    void EventDispatcher::AddListener(const typename EventClassListener<EventClass>::EventCallback& callback)
    {
        const EventType eventType = s_EventClassMap.at(typeid(EventClass));
        auto listener = std::make_unique<EventClassListener<EventClass>>(callback);

        auto[_, inserted] = m_Listeners[eventType].emplace(std::move(listener));
        if (!inserted)
        {
            Log::Error("Attempting to double-register callback !");
        }
    }

    template <typename EventClass>
    void EventDispatcher::RemoveListener(const typename EventClassListener<EventClass>::EventCallback& callback)
    {
        // TODO : Find a cleaner way to do this
        if (const EventType eventType = s_EventClassMap.at(typeid(EventClass)); m_Listeners.contains(eventType))
        {
            auto& listeners = m_Listeners[eventType];
            EventClassListener<EventClass> eventListener(callback);
            std::unique_ptr<EventListener> ptr(&eventListener);
            if (const auto& it = listeners.find(ptr); it != listeners.end())
            {
                listeners.erase(it);
                (void) ptr.release();
                return;
            }
            (void) ptr.release();
        }
        Log::Error("Attempting to erase non subscribed callback !");
    }

    // bool EventDispatcher::EventListenerEqual::operator()(const EventListenerPtr& lhs, const EventListenerPtr& rhs) const
    // {
    //     if (!lhs || !rhs)
    //     {
    //         return false;
    //     }
    //     return *lhs == *rhs;
    // }

    // std::size_t EventDispatcher::EventListenerHash::operator()(const EventListenerPtr& listener) const
    // {
    //     if (!listener)
    //     {
    //         return 0;
    //     }
    //     return listener->GetHashCode();
    // }
}

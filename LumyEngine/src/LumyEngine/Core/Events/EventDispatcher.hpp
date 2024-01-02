#pragma once

#include "EventListener.hpp"

#include <typeindex>

#include <unordered_map>
#include <unordered_set>

namespace Lumy
{
    class EventDispatcher
    {
    public:
        template <typename EventClass>
        void AddListener(const typename EventClassListener<EventClass>::EventCallback& callback);

        template <typename EventClass>
        void RemoveListener(const typename EventClassListener<EventClass>::EventCallback& callback);

        void Dispatch(const Event& event) const;
    private:
        static UnorderedMap<std::type_index, EventType> const s_EventClassMap;
    private:
        using EventListenerPtr = UniquePtr<EventListener>;
        struct EventListenerEqual
        {
            bool operator()(const EventListenerPtr& lhs, const EventListenerPtr& rhs) const
            {
                if (!lhs || !rhs)
                {
                    return false;
                }
                return *lhs == *rhs;
            }
        };

        struct EventListenerHash
        {
            std::size_t operator()(const EventListenerPtr& listener) const
            {
                if (!listener)
                {
                    return 0;
                }
                return listener->GetHashCode();
            }
        };

        using EventListenerSet = std::unordered_set<EventListenerPtr, EventListenerHash, EventListenerEqual>;
        UnorderedMap<EventType, EventListenerSet> m_Listeners;
    };
}

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
            UniquePtr<EventListener> ptr(&eventListener);
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
}

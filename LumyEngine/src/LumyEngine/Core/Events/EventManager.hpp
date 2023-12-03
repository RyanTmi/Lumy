#pragma once

#include "Event.hpp"
#include "EventListener.hpp"

#include <typeindex>

#include <unordered_map>
#include <unordered_set>
#include <queue>

namespace Lumy
{
    class EventManager
    {
    public:
        static EventManager& Instance();
    public:
        template <typename EventClass, typename = std::enable_if_t<std::derived_from<EventClass, Event>>>
        void Subscribe(const typename EventClassListener<EventClass>::EventCallback& callback);

        template <typename EventClass, typename = std::enable_if_t<std::derived_from<EventClass, Event>>>
        void Unsubscribe(const typename EventClassListener<EventClass>::EventCallback& callback);

        void InvokeEvent(const Event& event);

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;
    private:
        EventManager() = default;
        ~EventManager() = default;
    private:
        static const std::unordered_map<std::type_index, EventType> s_EventClassMap;
    private:
        struct EventListenerEqual
        {
            bool operator()(const std::unique_ptr<EventListener>& lhs, const std::unique_ptr<EventListener>& rhs) const
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
        public:
            std::size_t operator()(const std::unique_ptr<EventListener>& listener) const
            {
                if (!listener)
                {
                    return 0;
                }
                return listener->GetHashCode();
            }
        };

        using EventListenerSet = std::unordered_set<std::unique_ptr<EventListener>, EventListenerHash, EventListenerEqual>;
        std::unordered_map<EventType, EventListenerSet> m_Subscribers;
    };

    template <typename EventClass, typename>
    void EventManager::Subscribe(const typename EventClassListener<EventClass>::EventCallback& callback)
    {
        const EventType eventType = s_EventClassMap.at(typeid(EventClass));
        auto listener = std::make_unique<EventClassListener<EventClass>>(callback);

        auto[_, inserted] = m_Subscribers[eventType].emplace(std::move(listener));
        if (!inserted)
        {
            Log::Error("Attempting to double-register callback !");
        }
    }

    template <typename EventClass, typename>
    void EventManager::Unsubscribe(const typename EventClassListener<EventClass>::EventCallback& callback)
    {
        // TODO : Find a cleaner way to do this
        if (const EventType eventType = s_EventClassMap.at(typeid(EventClass)); m_Subscribers.contains(eventType))
        {
            auto& listeners = m_Subscribers[eventType];
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
}
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
        static std::unordered_map<std::type_index, EventType> const s_EventClassMap;
    private:
        using EventListenerPtr = std::unique_ptr<EventListener>;
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
        std::unordered_map<EventType, EventListenerSet> m_Listeners;
    };
}

#include "EventDispatcher.inl"

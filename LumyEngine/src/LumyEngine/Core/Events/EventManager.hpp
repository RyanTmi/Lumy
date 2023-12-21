#pragma once

#include "EventDispatcher.hpp"
#include "EventQueue.hpp"

namespace Lumy
{
    class EventManager
    {
    public:
        template <typename EventClass, typename = std::enable_if_t<std::derived_from<EventClass, Event>>>
        static void Subscribe(const typename EventClassListener<EventClass>::EventCallback& callback);

        template <typename EventClass, typename = std::enable_if_t<std::derived_from<EventClass, Event>>>
        static void Unsubscribe(const typename EventClassListener<EventClass>::EventCallback& callback);

        static void PublishEvents();

        template <typename EventClass, typename... Args, typename = std::enable_if_t<std::derived_from<EventClass, Event>>>
        static void QueueEvent(Args&&... args);

        static void SendEvent(const Event& event);

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;
    private:
        EventManager() = default;
        ~EventManager() = default;
    private:
        static EventManager& Instance();
        static const std::unordered_map<std::type_index, EventType> s_EventClassMap;
    private:
        EventDispatcher m_EventDispatcher;
        EventQueue m_EventQueue;
    };
}

#include "EventManager.inl"

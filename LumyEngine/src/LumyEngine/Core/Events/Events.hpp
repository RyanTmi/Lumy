#pragma once

#include "EventDispatcher.hpp"
#include "EventQueue.hpp"

#include "LumyEngine/Core/Module.hpp"

#include <type_traits>
#include <concepts>

namespace Lumy
{
    class Events : public Module
    {
    public:
        static Events& Get();
    public:
        void Initialize() override;
        void Update() override;
        void Shutdown() override;
    public:
        template <typename EventClass, typename = std::enable_if_t<std::is_base_of<Event, EventClass>::value>>
        void Subscribe(const typename EventClassListener<EventClass>::EventCallback& callback);

        template <typename EventClass, typename = std::enable_if_t<std::is_base_of<Event, EventClass>::value>>
        void Unsubscribe(const typename EventClassListener<EventClass>::EventCallback& callback);

        void PublishEvents();

        template <typename EventClass, typename... Args, typename = std::enable_if_t<std::is_base_of<Event, EventClass>::value>>
        void QueueEvent(Args&&... args);

        void SendEvent(const Event& event);
    public:
        Events(const Events&) = delete;
        Events& operator=(const Events&) = delete;
    private:
        Events() = default;
        ~Events() = default;
    private:
        EventDispatcher m_EventDispatcher;
        EventQueue m_EventQueue;
    };
}

#include "Events.inl"

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

        template <typename EventClass, typename... Args, typename = std::enable_if_t<std::is_base_of<Event, EventClass>::value>>
        void SendEvent(Args&&... args);
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

    template <typename EventClass, typename... Args, typename>
    void Events::SendEvent(Args&&... args)
    {
        EventClass event(args...);
        m_EventDispatcher.Dispatch(event);
    }
}

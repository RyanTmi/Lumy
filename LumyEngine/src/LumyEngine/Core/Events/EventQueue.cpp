#include "EventQueue.hpp"

namespace Lumy
{
    void EventQueue::QueueEvent(UniquePtr<Event> event)
    {
        m_EventQueue.push(std::move(event));
    }

    UniquePtr<Event> EventQueue::DequeueEvent()
    {
        if (m_EventQueue.empty())
        {
            return nullptr;
        }
        auto event = std::move(m_EventQueue.front());
        m_EventQueue.pop();
        return event;
    }

    bool EventQueue::HasEvent() const
    {
        return m_EventQueue.empty();
    }
}
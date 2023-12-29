#pragma once

#include "Event.hpp"

#include <queue>

namespace Lumy
{
    class EventQueue
    {
    public:
        void QueueEvent(UniquePtr<Event> event);

        UniquePtr<Event> DequeueEvent();

        bool HasEvent() const;
    private:
        std::queue<UniquePtr<Event>> m_EventQueue;
    };
}
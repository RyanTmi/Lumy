#pragma once

#include "Event.hpp"

#include <queue>

namespace Lumy
{
    class EventQueue
    {
    public:
        void QueueEvent(std::unique_ptr<Event> event);

        std::unique_ptr<Event> DequeueEvent();

        bool HasEvent() const;
    private:
        std::queue<std::unique_ptr<Event>> m_EventQueue;
    };
}
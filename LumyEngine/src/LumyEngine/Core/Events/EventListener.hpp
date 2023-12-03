#pragma once

#include "Event.hpp"

#include "LumyEngine/Core/Delegate.hpp"

namespace Lumy
{
    class EventListener
    {
    public:
        virtual ~EventListener() = default;
        virtual void DispatchEvent(const Event&) const = 0;
        virtual bool operator==(const EventListener &) const noexcept = 0;
        virtual std::size_t GetHashCode() const = 0;
    };

    template <typename EventClass>
    class EventClassListener final : public EventListener
    {
    public:
        using EventCallback = Delegate<void(const EventClass&)>;

        explicit EventClassListener(EventCallback callback)
            : m_Callback(callback) {}

        void DispatchEvent(const Event& event) const override
        {
            m_Callback(static_cast<const EventClass&>(event));
        }

        bool operator==(const EventListener &rhs) const noexcept override
        {
            if (auto* casted = dynamic_cast<const EventClassListener*>(&rhs))
            {
                return m_Callback == casted->m_Callback;
            }

            return false;
        }

        std::size_t GetHashCode() const override
        {
            return std::hash<EventCallback>{}(m_Callback);
        }

      private:
        friend struct std::hash<EventClassListener>;
        EventCallback m_Callback;
    };
}

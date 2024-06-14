#pragma once

#include "LumyEngine/Core/Delegate.hpp"
#include "LumyEngine/Core/Event/Event.hpp"
#include "LumyEngine/Core/Event/WindowEvent.hpp"
#include "LumyEngine/Core/Event/MouseEvent.hpp"
#include "LumyEngine/Core/Event/KeyEvent.hpp"
#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Debug/Log.hpp"

#include <unordered_map>
#include <unordered_set>
#include <variant>

namespace Lumy
{
    template <Event E>
    using EventDelegate = Delegate<bool(const E&)>;

    //==================================================================================================================
    // Class : EventManager
    //==================================================================================================================

    class EventManager final
    {
    public:
        static auto Initialize() -> bool;

        static auto Shutdown() -> void;

    public:
        template <Event E, typename... Args>
        static auto Fire(Args&&... args) -> void;

        template <Event E>
        static auto Add(EventDelegate<E> listener) -> void;

        template <Event E>
        static auto Remove(EventDelegate<E> listener) -> void;

    private:
        using EventListener = std::variant<
            EventDelegate<KeyPressEvent>,
            EventDelegate<KeyReleaseEvent>,
            EventDelegate<MouseMoveEvent>,
            EventDelegate<MouseScrollEvent>,
            EventDelegate<MouseButtonPressEvent>,
            EventDelegate<MouseButtonReleaseEvent>,
            EventDelegate<WindowCloseEvent>,
            EventDelegate<WindowResizeEvent>>;

        using Listeners = std::unordered_map<EventType, std::unordered_set<EventListener>>;

    private:
        static Listeners s_Listeners;
    };

    //==================================================================================================================
    // Class : EventManager
    //==================================================================================================================

    template <Event E>
    auto EventManager::Add(EventDelegate<E> listener) -> void
    {
        EventType type = E::Type;
        auto [_, inserted] = s_Listeners[type].insert(listener);
        if (!inserted)
        {
            Log::Warn("EventManager: Attempting to double-register callback !");
        }
    }

    template <Event E>
    auto EventManager::Remove(EventDelegate<E> listener) -> void
    {
        EventType type = E::Type;
        if (!s_Listeners.contains(type))
        {
            Log::Warn("EventManager: Attempting to erase non subscribed callback !");
            return;
        }

        auto& listeners = s_Listeners[type];
        if (auto it = listeners.find(listener); it != listeners.end())
        {
            listeners.erase(it);
        }
    }

    template <Event E, typename... Args>
    auto EventManager::Fire(Args&&... args) -> void
    {
        EventType type = E::Type;
        if (!s_Listeners.contains(type))
        {
            // No listeners for this event
            return;
        }

        E event(std::forward<Args>(args)...);
        for (auto listener : s_Listeners[type])
        {
            // NOTE: `std::get` should not throw `std::bad_variant_access`
            if (std::get<EventDelegate<E>>(listener)(event))
            {
                // Message has been handled, do not send to other listeners.
                return;
            }
        }
    }
}

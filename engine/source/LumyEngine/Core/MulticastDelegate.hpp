#pragma once

#include "Delegate.hpp"
#include "LumyEngine/debug/Logger.hpp"

#include <ranges>
#include <unordered_set>

namespace Lumy
{
    template <typename... Args>
    struct MulticastDelegate
    {
    public:
        constexpr MulticastDelegate() noexcept = default;
        constexpr MulticastDelegate(const MulticastDelegate& other) noexcept = default;

    public:
        constexpr auto
            operator=(const MulticastDelegate& other) noexcept -> MulticastDelegate& = default;

        template <typename... UArgs>
        constexpr auto operator()(UArgs&&... args) const -> void;

        auto operator+=(const Delegate<void(Args...)>& delegate) noexcept -> void;
        auto operator-=(const Delegate<void(Args...)>& delegate) noexcept -> void;

    private:
        std::unordered_set<Delegate<void(Args...)>> m_Delegates;
    };

    //==============================================================================================
    // class : MulticastDelegate
    //==============================================================================================

    template <typename... Args>
    template <typename... UArgs>
    inline constexpr auto MulticastDelegate<Args...>::operator()(UArgs&&... args) const -> void
    {
        std::ranges::for_each(m_Delegates,
                              [&](auto& delegate) { delegate(std::forward<UArgs>(args)...); });
    }

    template <typename... Args>
    inline auto MulticastDelegate<Args...>::operator+=(
        const Delegate<void(Args...)>& delegate) noexcept -> void
    {
        m_Delegates.insert(delegate);
    }

    template <typename... Args>
    inline auto MulticastDelegate<Args...>::operator-=(
        const Delegate<void(Args...)>& delegate) noexcept -> void
    {
        auto it = m_Delegates.find(delegate);
        if (it == m_Delegates.end())
        {
            Log::Warn("Can not remove Delegate");
            return;
        }
        m_Delegates.erase(it);
    }
}

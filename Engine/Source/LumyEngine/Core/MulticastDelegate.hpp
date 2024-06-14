#pragma once

#include "LumyEngine/Core/Delegate.hpp"
#include "LumyEngine/Debug/Log.hpp"

#include <ranges>
#include <unordered_set>

namespace Lumy
{
    //==================================================================================================================
    // Class : MulticastDelegate
    //==================================================================================================================

    template <typename... Args>
    struct MulticastDelegate
    {
    public:
        using DelegateType = Delegate<void(Args...)>;

    public:
        constexpr MulticastDelegate() noexcept = default;
        constexpr MulticastDelegate(const MulticastDelegate& other) noexcept = default;

    public:
        constexpr auto operator=(const MulticastDelegate& other) noexcept -> MulticastDelegate& = default;

        template <typename... UArgs>
        constexpr auto operator()(UArgs&&... args) const -> void;

        auto operator+=(const DelegateType& delegate) noexcept -> void;
        auto operator-=(const DelegateType& delegate) noexcept -> void;

    private:
        std::unordered_set<DelegateType> m_Delegates;
    };

    //==================================================================================================================
    // Class : MulticastDelegate
    //==================================================================================================================

    template <typename... Args>
    template <typename... UArgs>
    inline constexpr auto MulticastDelegate<Args...>::operator()(UArgs&&... args) const -> void
    {
        std::ranges::for_each(m_Delegates, [&](auto& delegate) { delegate(std::forward<UArgs>(args)...); });
    }

    template <typename... Args>
    inline auto MulticastDelegate<Args...>::operator+=(const DelegateType& delegate) noexcept -> void
    {
        m_Delegates.insert(delegate);
    }

    template <typename... Args>
    inline auto MulticastDelegate<Args...>::operator-=(const DelegateType& delegate) noexcept -> void
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

#pragma once

namespace Lumy
{
    template <auto Function>
    constexpr FunctionBindTarget<Function> MakeDelegate() noexcept
    {
        return {};
    }

    template <auto MemberFunction, typename C>
    constexpr MemberFunctionBindTarget<MemberFunction, C> MakeDelegate(C* p) noexcept
    {
        return { p };
    }

    template <typename ReturnType, typename... Args>
    template <auto Function, typename>
    constexpr Delegate<ReturnType(Args...)>::Delegate(FunctionBindTarget<Function>) noexcept
    {
        Bind<Function>();
    }

    template <typename ReturnType, typename... Args>
    template <auto MemberFunction, typename C, typename>
    constexpr Delegate<ReturnType(Args...)>::Delegate(MemberFunctionBindTarget<MemberFunction, C> target) noexcept
    {
        Bind<MemberFunction, C>(target.Instance);
    }

    template <typename ReturnType, typename... Args>
    template <auto MemberFunction, typename C, typename>
    constexpr Delegate<ReturnType(Args...)>::Delegate(MemberFunctionBindTarget<MemberFunction, const C> target) noexcept
    {
        Bind<MemberFunction, const C>(target.Instance);
    }

    template <typename ReturnType, typename... Args>
    template <typename... FArgs, typename>
    ReturnType Delegate<ReturnType(Args...)>::operator()(FArgs&&... args) const
    {
        LM_ENGINE_ASSERT(m_Function != nullptr);
        return std::invoke(m_Function, m_Instance, std::forward<FArgs>(args)...);
    }

    template <typename ReturnType, typename... Args>
    bool Delegate<ReturnType(Args...)>::operator==(const Delegate& rhs) const
    {
        return (m_Instance == rhs.m_Instance) && (m_Function == rhs.m_Function);
    }

    template <typename ReturnType, typename... Args>
    bool Delegate<ReturnType(Args...)>::operator!=(const Delegate& rhs) const
    {
        return !operator==(rhs);
    }

    template <typename ReturnType, typename... Args>
    template <auto Function, typename>
    void Delegate<ReturnType(Args...)>::Bind()
    {
        m_Instance = nullptr;
        m_Function = static_cast<InternalFunction>([](ClassInstance, Args... args) -> ReturnType
        {
            return std::invoke(Function, std::forward<Args>(args)...);
        });
    }

    template <typename ReturnType, typename... Args>
    template <auto Function, typename C, typename>
    void Delegate<ReturnType(Args...)>::Bind(const C* o)
    {
        m_Instance = o;
        m_Function = static_cast<InternalFunction>([](ClassInstance op, Args... args) -> ReturnType
        {
            const auto* ols = static_cast<const C*>(op);
            return std::invoke(Function, ols, std::forward<Args>(args)...);
        });
    }

    template <typename ReturnType, typename... Args>
    template <auto Function, typename C, typename>
    void Delegate<ReturnType(Args...)>::Bind(C* o)
    {
        m_Instance = o;
        m_Function = static_cast<InternalFunction>([](ClassInstance op, Args... args) -> ReturnType
        {
            auto* ols = const_cast<C*>(static_cast<const C*>(op));
            return std::invoke(Function, ols, std::forward<Args>(args)...);
        });
    }
}

namespace std
{
    template <typename ReturnType, typename ...Args>
    struct hash<Lumy::Delegate<ReturnType(Args...)>>
    {
        static size_t hash_combine(size_t seed, size_t v)
        {
            return seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        size_t operator()(const Lumy::Delegate<ReturnType(Args...)>& delegate) const noexcept
        {
            size_t a = std::hash<const void*>{}(delegate.m_Instance);
            size_t b = std::hash<typename Lumy::Delegate<ReturnType(Args...)>::InternalFunction>{}(delegate.m_Function);
            return hash_combine(a, b);
        }
    };
}

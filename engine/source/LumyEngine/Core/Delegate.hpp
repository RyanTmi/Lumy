#pragma once

#include <exception>
#include <functional>
#include <type_traits>
#include <utility>

namespace Lumy
{
    class BadDelegateCall : public std::runtime_error
    {
    public:
        BadDelegateCall();
    };

    template <auto Function>
    struct FunctionBindTarget
    {
    };

    template <auto MemberFunction, typename Class>
    struct MemberBindTarget
    {
        Class* Instance;
    };

    template <auto Function>
    constexpr auto MakeDelegate() -> FunctionBindTarget<Function>;

    template <auto MemberFunction, typename Class>
    constexpr auto
        MakeDelegate(Class* instance) -> MemberBindTarget<MemberFunction, Class>;

    //==============================================================================================
    // class : Delegate
    //==============================================================================================

    template <typename Signature>
    class Delegate;

    template <typename R, typename... Args>
    class Delegate<R(Args...)>
    {
    public:
        using ReturnType = R;

    public:
        constexpr Delegate() noexcept = default;
        constexpr Delegate(const Delegate& other) noexcept = default;

        template <auto Function>
        constexpr Delegate(FunctionBindTarget<Function> target) noexcept;

        template <auto MemberFunction, typename Class>
        constexpr Delegate(MemberBindTarget<MemberFunction, Class> target) noexcept;

        template <auto MemberFunction, typename Class>
        constexpr Delegate(
            MemberBindTarget<MemberFunction, const Class> target) noexcept;

    public:
        constexpr auto operator=(const Delegate& other) noexcept -> Delegate& = default;

        template <typename... UArgs,
                  typename = std::enable_if_t<std::is_invocable_v<ReturnType(Args...), UArgs...>>>
        constexpr auto operator()(UArgs&&... args) const -> ReturnType;

        constexpr auto operator==(const Delegate& rhs) const noexcept -> bool;
        constexpr auto operator!=(const Delegate& rhs) const noexcept -> bool;

    public:
        constexpr auto HasTarget() const noexcept -> bool { return m_Stub != &NullStub; }

        constexpr operator bool() const noexcept { return HasTarget(); }

        template <auto Function, typename = std::enable_if_t<std::is_invocable_r_v<
                                     ReturnType, decltype(Function), Args...>>>
        constexpr auto Bind() noexcept -> void;

        template <auto MemberFunction, typename Class,
                  typename = std::enable_if_t<
                      std::is_invocable_r_v<ReturnType, decltype(MemberFunction), Class*, Args...>>>
        constexpr auto Bind(Class* cls) noexcept -> void;

    private:
        using StubFunction = ReturnType (*)(const void*, Args...);

    private:
        [[noreturn]] constexpr static auto NullStub(const void*, Args...) -> ReturnType;

    private:
        friend struct std::hash<Delegate>;

    private:
        const void* m_Instance = nullptr;
        StubFunction m_Stub = &NullStub;
    };

    //==============================================================================================
    // class : BadDelegateCall
    //==============================================================================================

    inline BadDelegateCall::BadDelegateCall()
        : runtime_error("Delegate called without being bound")
    {}

    //==============================================================================================
    // functions : make Delegate
    //==============================================================================================

    template <auto Function>
    inline constexpr auto MakeDelegate() -> FunctionBindTarget<Function>
    {
        return {};
    }

    template <auto MemberFunction, typename Class>
    inline constexpr auto
        MakeDelegate(Class* instance) -> MemberBindTarget<MemberFunction, Class>
    {
        return {instance};
    }

    //==============================================================================================
    // class : Delegate
    //==============================================================================================

    template <typename R, typename... Args>
    template <auto Function>
    inline constexpr Delegate<R(Args...)>::Delegate(FunctionBindTarget<Function>) noexcept
    {
        Bind<Function>();
    }

    template <typename R, typename... Args>
    template <auto MemberFunction, typename Class>
    inline constexpr Delegate<R(Args...)>::Delegate(
        MemberBindTarget<MemberFunction, Class> target) noexcept
    {
        Bind<MemberFunction, Class>(target.Instance);
    }

    template <typename R, typename... Args>
    template <auto MemberFunction, typename Class>
    inline constexpr Delegate<R(Args...)>::Delegate(
        MemberBindTarget<MemberFunction, const Class> target) noexcept
    {
        Bind<MemberFunction, const Class>(target.Instance);
    }

    template <typename R, typename... Args>
    template <typename... UArgs, typename>
    inline constexpr auto Delegate<R(Args...)>::operator()(UArgs&&... args) const -> ReturnType
    {
        return std::invoke(m_Stub, m_Instance, std::forward<UArgs>(args)...);
    }

    template <typename R, typename... Args>
    inline constexpr auto
        Delegate<R(Args...)>::operator==(const Delegate& rhs) const noexcept -> bool
    {
        return m_Stub == rhs.m_Stub and m_Instance == rhs.m_Instance;
    }

    template <typename R, typename... Args>
    inline constexpr auto
        Delegate<R(Args...)>::operator!=(const Delegate& rhs) const noexcept -> bool
    {
        return !operator==(rhs);
    }

    template <typename R, typename... Args>
    template <auto Function, typename>
    inline constexpr auto Delegate<R(Args...)>::Bind() noexcept -> void
    {
        m_Instance = nullptr;
        m_Stub = static_cast<StubFunction>([](const void*, Args... args) -> ReturnType {
            return std::invoke(Function, std::forward<Args>(args)...);
        });
    }

    template <typename R, typename... Args>
    template <auto MemberFunction, typename Class, typename>
    inline constexpr auto Delegate<R(Args...)>::Bind(Class* cls) noexcept -> void
    {
        m_Instance = cls;
        m_Stub = static_cast<StubFunction>([](const void* p, Args... args) -> ReturnType {
            auto* c = const_cast<Class*>(static_cast<const Class*>(p));
            return std::invoke(MemberFunction, c, std::forward<Args>(args)...);
        });
    }

    template <typename R, typename... Args>
    inline constexpr auto Delegate<R(Args...)>::NullStub(const void*, Args...) -> ReturnType
    {
        throw BadDelegateCall {};
    }
}

namespace std
{
    template <typename R, typename... Args>
    struct hash<Lumy::Delegate<R(Args...)>>
    {
        static size_t hash_combine(size_t seed, size_t v)
        {
            return seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        size_t operator()(const Lumy::Delegate<R(Args...)>& Delegate) const noexcept
        {
            size_t a = std::hash<const void*> {}(Delegate.m_Instance);
            size_t b =
                std::hash<typename Lumy::Delegate<R(Args...)>::StubFunction> {}(Delegate.m_Stub);
            return hash_combine(a, b);
        }
    };
}

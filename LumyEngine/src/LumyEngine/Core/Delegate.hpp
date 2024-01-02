/**
 * @file Delegate.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Header file defining a generic delegate for binding functions and member functions.
 * @version 0.1
 * @date 2023-11-26
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#include "Foundation.hpp"

namespace Lumy
{
    /**
     * @brief Helper struct to represent the binding target of a non-member function.
     * @tparam Function The target non-member function.
     */
    template <auto Function>
    struct FunctionBindTarget {};

    /**
     * @brief Helper function to create a binding target for a non-member function.
     * @tparam Function The target non-member function.
     * @return A FunctionBindTarget representing the binding target.
     */
    template <auto Function>
    constexpr FunctionBindTarget<Function> MakeDelegate() noexcept;

    /**
     * @brief Helper struct to represent the binding target of a member function.
     * @tparam MemberFunction The target member function.
     * @tparam C The class type.
     */
    template <auto MemberFunction, typename C>
    struct MemberFunctionBindTarget { C* Instance; };

    /**
     * @brief Helper function to create a binding target for a member function.
     * @tparam MemberFunction The target member function.
     * @tparam C The class type.
     * @param p Pointer to an instance of the class.
     * @return A MemberFunctionBindTarget representing the binding target.
     */
    template <auto MemberFunction, typename C>
    constexpr MemberFunctionBindTarget<MemberFunction, C> MakeDelegate(C* p) noexcept;

    /**
     * @brief Generic delegate class template for binding functions and member functions.
     * @tparam Signature The signature of the function, including return type and argument types.
     */
    template <typename Signature>
    class Delegate;

    /**
     * @brief Generic delegate class for binding functions and member functions.
     * @tparam ReturnType The return type of the function.
     * @tparam Args The argument types of the function.
     */
    template <typename ReturnType, typename ...Args>
    class Delegate<ReturnType(Args...)>
    {
    private:
        using ClassInstance = const void*;
        using InternalFunction = ReturnType(*)(ClassInstance, Args...);
    public:
        /**
         * @brief Default constructor for an empty delegate.
         */
        constexpr Delegate() noexcept = default;

        /**
         * @brief Constructor to create a delegate from a non-member function.
         * @tparam Function The target non-member function.
         * @param target A FunctionBindTarget representing the binding target.
         */
        template <auto Function, typename = std::enable_if_t<std::is_invocable_r_v<ReturnType, decltype(Function), Args...>>>
        constexpr Delegate(FunctionBindTarget<Function> target) noexcept;

        /**
         * @brief Constructor to create a delegate from a const member function.
         * @tparam MemberFunction The target member function.
         * @tparam C The class type.
         * @param target A MemberFunctionBindTarget representing the binding target.
         */
        template <auto MemberFunction, typename C, typename = std::enable_if_t<std::is_invocable_r_v<ReturnType, decltype(MemberFunction), const C&, Args...>>>
        constexpr Delegate(MemberFunctionBindTarget<MemberFunction, const C> target) noexcept;

        /**
         * @brief Constructor to create a delegate from a non-const member function.
         * @tparam MemberFunction The target member function.
         * @tparam C The class type.
         * @param target A MemberFunctionBindTarget representing the binding target.
         */
        template <auto MemberFunction, typename C, typename = std::enable_if_t<std::is_invocable_r_v<ReturnType, decltype(MemberFunction), C&, Args...>>>
        constexpr Delegate(MemberFunctionBindTarget<MemberFunction, C> target) noexcept;

        /**
         * @brief Copy constructor.
         * @param rhs The delegate to copy.
         */
        constexpr Delegate(const Delegate& rhs) noexcept = default;

        /**
         * @brief Copy assignment operator.
         * @param rhs The delegate to copy.
         * @return A reference to the assigned delegate.
         */
        constexpr Delegate& operator=(const Delegate& rhs) = default;

        /**
         * @brief Operator to invoke the stored function.
         * @tparam FArgs The argument types for the function call.
         * @param args The arguments for the function call.
         * @return The result of the function call.
         */
        template <typename... FArgs, typename = std::enable_if_t<std::is_invocable_v<ReturnType(Args...), FArgs...>>>
        ReturnType operator()(FArgs&&... args) const;
    public:
        /**
         * @brief Equality comparison operator.
         * @param rhs The delegate to compare.
         * @return True if the delegates are equal, false otherwise.
         */
        bool operator==(const Delegate& rhs) const;

        /**
         * @brief Inequality comparison operator.
         * @param rhs The delegate to compare.
         * @return True if the delegates are not equal, false otherwise.
         */
        bool operator!=(const Delegate& rhs) const;

    public:
        /**
         * @brief Bind the delegate to a non-member function.
         * @tparam Function The target non-member function.
         * @param target A FunctionBindTarget representing the binding target.
         */
        template <auto Function, typename = std::enable_if_t<std::is_invocable_r_v<ReturnType, decltype(Function), Args...>>>
        void Bind();

        /**
         * @brief Bind the delegate to a const member function.
         * @tparam Function The target member function.
         * @tparam C The class type.
         * @param o Pointer to an instance of the class.
         */
        template <auto Function, typename C, typename = std::enable_if_t<std::is_invocable_r_v<ReturnType, decltype(Function), const C&, Args...>>>
        void Bind(const C* o);

        /**
         * @brief Bind the delegate to a non-const member function.
         * @tparam Function The target member function.
         * @tparam C The class type.
         * @param o Pointer to an instance of the class.
         */
        template <auto Function, typename C, typename = std::enable_if_t<std::is_invocable_r_v<ReturnType, decltype(Function), C&, Args...>>>
        void Bind(C* o);

    private:
        friend struct std::hash<Delegate>;

        /**
         * @brief Pointer to the class instance for member function binding.
         * If the function being bound is not a member function, this pointer remains nullptr.
         */
        ClassInstance m_Instance { nullptr };

        /**
         * @brief Internal function pointer for invoking the bound function.
         * If no function is bound, this pointer remains nullptr.
         */
        InternalFunction m_Function { nullptr };
    };
}


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

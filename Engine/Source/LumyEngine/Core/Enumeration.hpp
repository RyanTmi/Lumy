#pragma once

#include <type_traits>

namespace Lumy
{
    template <typename E>
    concept Enumeration = std::is_enum_v<E>;

    template <Enumeration E>
    constexpr auto operator|(E lhs, E rhs) -> E
    {
        return static_cast<E>(
            static_cast<std::underlying_type_t<E>>(lhs) | static_cast<std::underlying_type_t<E>>(rhs));
    }

    template <Enumeration E>
    constexpr auto operator|=(E& lhs, E rhs) -> E
    {
        lhs = static_cast<E>(static_cast<std::underlying_type_t<E>>(lhs) | static_cast<std::underlying_type_t<E>>(rhs));
        return lhs;
    }

    template <Enumeration E>
    constexpr auto operator&(E lhs, E rhs) -> E
    {
        return static_cast<E>(
            static_cast<std::underlying_type_t<E>>(lhs) & static_cast<std::underlying_type_t<E>>(rhs));
    }

    template <Enumeration E>
    constexpr auto operator&=(E& lhs, E rhs) -> E
    {
        lhs = static_cast<E>(static_cast<std::underlying_type_t<E>>(lhs) & static_cast<std::underlying_type_t<E>>(rhs));
        return lhs;
    }
}

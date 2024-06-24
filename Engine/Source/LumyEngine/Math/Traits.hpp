#pragma once

#include "LumyEngine/Core/Types.hpp"

#include <concepts>
#include <limits>

namespace Lumy
{
    template <typename T>
    concept Integral = std::integral<T>;

    template <typename T>
    concept Real = std::floating_point<T>;

    template <typename T>
    concept Numeric = Integral<T> or Real<T>;

    constexpr Size DynamicExtend = std::numeric_limits<Size>::max();
}

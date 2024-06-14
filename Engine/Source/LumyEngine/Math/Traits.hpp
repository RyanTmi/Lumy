#pragma once

#include <concepts>

namespace Lumy::Math
{
    template <typename T>
    concept Integral = std::integral<T>;

    template <typename T>
    concept FloatingPoint = std::floating_point<T>;

    template <typename T>
    concept Numeric = Integral<T> or FloatingPoint<T>;
}

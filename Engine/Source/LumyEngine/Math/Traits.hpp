#pragma once

#include <concepts>

namespace Lumy
{
    template <typename T>
    concept Numeric = std::integral<T> or std::floating_point<T>;
}

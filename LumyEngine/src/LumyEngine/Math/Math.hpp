#pragma once

#include "LumyEngine/Core/Types.hpp"

#include <concepts>
#include <cmath>

namespace Lumy::Math
{
    static constexpr Float64 Epsilon = 1.0e-6f;
    static constexpr Float64 Pi      = 3.14159265358979323846f;
    static constexpr Float64 E       = 2.71828182845904523536f;

    template <typename T>
    concept Integer = std::integral<T>;

    template <typename T>
    concept Float = std::floating_point<T>;

    template <typename T>
    concept Arithmetic = Integer<T> or Float<T>;

    template <typename T>
    concept Comparable = requires(const T& t1, const T& t2) {
        { t1.operator<(t2) } -> std::same_as<Bool8>;
    };

    template <Arithmetic T>
    inline T Sqrt(T x) noexcept
    {
        return std::sqrt(x);
    }

    template <Arithmetic T>
    inline T InverseSqrt(T x) noexcept
    {
        return 1 / Sqrt(x);
    }

    template <Arithmetic T>
    inline T Abs(T x) noexcept
    {
        return x < 0 ? -x : x;
    }

    template <Arithmetic T>
    inline Bool8 Equal(T x, T y) noexcept
    {
        return Abs(x - y) < Epsilon;
    }

    template <Arithmetic T>
    inline T Pow(T base, T exp) noexcept
    {
        return std::pow(base, exp);
    }

    template <Arithmetic T>
    inline T Sin(T x) noexcept
    {
        std::sin(x);
    }

    template <Arithmetic T>
    inline T ASin(T x) noexcept
    {
        return std::asin(x);
    }

    template <Arithmetic T>
    inline T Cos(T x) noexcept
    {
        return std::cos(x);
    }

    template <Arithmetic T>
    inline T ACos(T x) noexcept
    {
        return std::acos(x);
    }


    template <Arithmetic T>
    inline T Tan(T x) noexcept
    {
        return std::tan(x);
    }

    template <Arithmetic T>
    inline T ATan(T x) noexcept
    {
        return std::atan(x);
    }

    template <Arithmetic T>
    inline T ATan2(T x, T y) noexcept
    {
        return std::atan2(x, y);
    }

    template <Arithmetic T>
    inline T Floor(T x) noexcept
    {
        return std::floor(x);
    }

    template <Arithmetic T>
    inline T Ceil(T x) noexcept
    {
        return std::ceil(x);
    }

    template <Arithmetic T>
    inline T Round(T x) noexcept
    {
        return std::round(x);
    }

    template <Comparable T>
    inline T Min(T x, T y) noexcept
    {
        return x < y ? x : y;
    }

    template <Comparable T>
    inline T Max(T x, T y) noexcept
    {
        return x < y ? y : x;
    }

    template <Comparable T>
    inline T Clamp(T x, T min, T max) noexcept
    {
        return Max(min, Min(x, max));
    }
}

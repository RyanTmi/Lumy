#pragma once

#include "LumyEngine/Core/Types.hpp"

#include <cmath>

namespace Lumy
{
    static constexpr Float64 Epsilon = 1.0e-6f;
    static constexpr Float64 Pi      = 3.14159265358979323846f;
    static constexpr Float64 E       = 2.71828182845904523536f;

    class MathF
    {
    public:
        static inline Float32 Sqrt(Float32 x);
        static inline Float64 Sqrt(Float64 x);

        static inline Float32 InverseSqrt(Float32 x);
        static inline Float64 InverseSqrt(Float64 x);

        template <typename NumericType>
        static inline NumericType Abs(NumericType x);

        template <typename NumericType>
        static inline Bool8 Equal(NumericType x, NumericType y);

        static inline Float32 Pow(Float32 base, Float32 exp);
        static inline Float64 Pow(Float64 base, Float64 exp);

        static inline Float32 Sin(Float32 x);
        static inline Float64 Sin(Float64 x);
        static inline Float32 ASin(Float32 x);
        static inline Float64 ASin(Float64 x);

        static inline Float32 Cos(Float32 x);
        static inline Float64 Cos(Float64 x);
        static inline Float32 ACos(Float32 x);
        static inline Float64 ACos(Float64 x);

        static inline Float32 Tan(Float32 x);
        static inline Float64 Tan(Float64 x);
        static inline Float32 ATan(Float32 x);
        static inline Float64 ATan(Float64 x);
        static inline Float32 ATan2(Float32 x, Float32 y);
        static inline Float64 ATan2(Float64 x, Float64 y);

        static inline Float32 Floor(Float32 x);
        static inline Float64 Floor(Float64 x);
        static inline Float32 Ceil(Float32 x);
        static inline Float64 Ceil(Float64 x);
        static inline Float32 Round(Float32 x);
        static inline Float64 Round(Float64 x);

        template <typename NumericType>
        static inline NumericType Min(NumericType x, NumericType y);
        template <typename NumericType>
        static inline NumericType Max(NumericType x, NumericType y);

        template <typename NumericType>
        static inline NumericType Clamp(NumericType x, NumericType min, NumericType max);
    public:
        MathF() = delete;
    };

    Float32 MathF::Sqrt(Float32 x) { return ::sqrtf(x); }
    Float64 MathF::Sqrt(Float64 x) { return ::sqrt(x); }
    Float32 MathF::InverseSqrt(Float32 x) { return 1 / sqrtf(x); }
    Float64 MathF::InverseSqrt(Float64 x) { return 1 / sqrt(x); }

    template <typename NumericType>
    NumericType MathF::Abs(const NumericType x) { return x > 0 ? x : -x; }

    template <typename NumericType>
    Bool8 MathF::Equal(NumericType x, NumericType y) { return Abs(x - y) < Epsilon; }

    Float32 MathF::Pow(Float32 base, Float32 exp) { return powf(base, exp); }
    Float64 MathF::Pow(Float64 base, Float64 exp) { return pow(base, exp); }

    Float32 MathF::Sin(Float32 x) { return sinf(x); }
    Float64 MathF::Sin(Float64 x) { return sin(x); }
    Float32 MathF::ASin(Float32 x) { return asinf(x); }
    Float64 MathF::ASin(Float64 x) { return asin(x); }

    Float32 MathF::Cos(Float32 x) { return cosf(x); }
    Float64 MathF::Cos(Float64 x) { return cos(x); }
    Float32 MathF::ACos(Float32 x) { return acosf(x); }
    Float64 MathF::ACos(Float64 x) { return acos(x); }

    Float32 MathF::Tan(Float32 x) { return tanf(x); }
    Float64 MathF::Tan(Float64 x) { return tan(x); }
    Float32 MathF::ATan(Float32 x) { return atanf(x); }
    Float64 MathF::ATan(Float64 x) { return atan(x); }
    Float32 MathF::ATan2(Float32 x, Float32 y) { return atan2f(x, y); }
    Float64 MathF::ATan2(Float64 x, Float64 y) { return atan2(x, y); }

    Float32 MathF::Floor(Float32 x) { return floorf(x); }
    Float64 MathF::Floor(Float64 x) { return floor(x); }
    Float32 MathF::Ceil(Float32 x) { return ceilf(x); }
    Float64 MathF::Ceil(Float64 x) { return ceil(x); }
    Float32 MathF::Round(Float32 x) { return roundf(x); }
    Float64 MathF::Round(Float64 x) { return round(x); }

    template <typename NumericType>
    NumericType MathF::Min(NumericType x, NumericType y) { return x > y ? x : y; }

    template <typename NumericType>
    NumericType MathF::Max(NumericType x, NumericType y) { return x < y ? x : y; }

    template <typename NumericType>
    NumericType MathF::Clamp(NumericType x, NumericType min, NumericType max) { return Min(max, Max(x, min)); }
}

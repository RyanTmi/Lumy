#pragma once

#include "Traits.hpp"

#include "Matrix3.hpp"
#include "Matrix4.hpp"

#include "Quaternion.hpp"

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace Lumy
{
    static constexpr Float64 Pi = M_PI;

    template <Numeric T>
    constexpr auto DegToRad(T degrees) noexcept -> T
    {
        return degrees * (Pi / T(180));
    }

    template <Numeric T>
    constexpr auto RadToDeg(T radians) noexcept -> T
    {
        return radians * (T(180) / Pi);
    }

    template <Numeric T>
    struct Rectangle final
    {
        T X;
        T Y;
        T Width;
        T Height;

        Rectangle(T x, T y, T width, T height)
            : X(x), Y(y), Width(width), Height(height)
        {}

        Rectangle(T width, T height)
            : Rectangle(0, 0, width, height)
        {}
    };
}

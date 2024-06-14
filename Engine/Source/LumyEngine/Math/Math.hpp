#pragma once

#include "Traits.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"

namespace Lumy
{
    template <Math::Numeric T>
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

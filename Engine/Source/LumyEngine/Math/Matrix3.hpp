#pragma once

#include "LumyEngine/Math/Matrix.hpp"

namespace Lumy
{
    template <Numeric T>
    class Matrix<T, 3, 3>
    {
    public:
        constexpr Matrix() noexcept = default;

    private:
        T m_Data[9];
    };

    template <Numeric T>
    using Matrix3x3 = Matrix<T, 3, 3>;

    using Matrix3x3f = Matrix3x3<Float32>;
    using Matrix3x3d = Matrix3x3<Float64>;
}

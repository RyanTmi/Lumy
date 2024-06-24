#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Math/Traits.hpp"

namespace Lumy
{
    template <Numeric T, Size R, Size C>
    class Matrix;

    template <Numeric T, Size R, Size C>
    constexpr auto operator+(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) noexcept -> Matrix<T, R, C>;

    template <Numeric T, Size R, Size C>
    constexpr auto operator-(const Matrix<T, R, C>& m) noexcept -> Matrix<T, R, C>;

    template <Numeric T, Size R, Size C>
    constexpr auto operator-(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs) noexcept -> Matrix<T, R, C>;

    template <Size A, Size B, Size C, Numeric T>
    constexpr auto operator*(const Matrix<T, A, C>& lhs, const Matrix<T, C, B>& rhs) noexcept -> Matrix<T, A, B>;
}

#pragma once

#include "LumyEngine/Math/Matrix.hpp"
#include "LumyEngine/Math/Quaternion.hpp"
#include "LumyEngine/Math/Vector3.hpp"

#include <cmath>

namespace Lumy
{
    //==================================================================================================================
    // Class : Matrix
    //==================================================================================================================

    template <Numeric T>
    class Matrix<T, 4, 4>
    {
    public:
        // TODO: Maybe move theses functions to game engine specific file
        static auto OrthographicLH(T left, T right, T bottom, T top, T near, T far) -> Matrix;
        static auto OrthographicRH(T left, T right, T bottom, T top, T near, T far) -> Matrix;
        static auto Perspective(T fov, T aspect, T near, T far) -> Matrix;
        static auto Rotate(const Quaternion<T>& q) -> Matrix;
        static auto Translate(const Vector3<T>& position) -> Matrix;
        static auto Scale(const Vector3<T>& scale) -> Matrix;

        static auto LookAt(const Vector3<T>& position, const Vector3<T>& target, const Vector3<T>& up) -> Matrix;

    public:
        constexpr Matrix() noexcept = default;
        constexpr Matrix(T x) noexcept;

    public:
        constexpr auto operator[](Size i) noexcept -> T*;
        constexpr auto operator[](Size i) const noexcept -> const T*;

    public:
        auto Inverse() const -> Matrix;
        auto Transposed() const -> Matrix;

    private:
        T m_Data[4][4] = {};
    };

    //==================================================================================================================
    // Class : Matrix
    //==================================================================================================================

    template <Numeric T>
    inline auto Matrix<T, 4, 4>::OrthographicLH(T left, T right, T bottom, T top, T near, T far) -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> result;
        result[0][0] = T(2) / (right - left);
        result[0][3] = (left + right) / (left - right);
        result[1][1] = T(2) / (top - bottom);
        result[1][3] = (bottom + top) / (bottom - top);
        result[2][2] = T(1) / (far - near);
        result[2][3] = near / (near - far);
        result[3][3] = T(1);
        return result;
    }

    template <Numeric T>
    inline auto Matrix<T, 4, 4>::OrthographicRH(T left, T right, T bottom, T top, T near, T far) -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> result;
        result[0][0] = T(2) / (right - left);
        result[0][3] = (left + right) / (left - right);
        result[1][1] = T(2) / (top - bottom);
        result[1][3] = (bottom + top) / (bottom - top);
        result[2][2] = T(1) / (near - far);
        result[2][3] = near / (near - far);
        result[3][3] = T(1);
        return result;
    }

    template <Numeric T>
    inline auto Matrix<T, 4, 4>::Perspective(T fov, T aspect, T near, T far) -> Matrix<T, 4, 4>
    {
        // NOTE: Left handed
        T y = T(1) / std::tan(fov * 0.5);
        T x = y / aspect;
        T z = far / (far - near);

        Matrix<T, 4, 4> result;
        result[0][0] = x;
        result[1][1] = y;
        result[2][2] = z;
        result[2][3] = -near * z;
        result[3][2] = T(1);
        return result;

        // NOTE: Right handed
        // T y = 1 / std::tan(fov * 0.5);
        // T x = y / aspect;
        // T z = far / (near - far);

        // Matrix<T, 4, 4> result;
        // result[0][0] = x;
        // result[1][1] = y;
        // result[2][2] = z;
        // result[2][3] = near * z;
        // result[3][2] = T(-1);
        // return result;
    }

    template <Numeric T>
    inline auto Matrix<T, 4, 4>::Rotate(const Quaternion<T>& q) -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> result(T(1));
        result[0][0] = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);
        result[0][1] = 2 * (q[0] * q[1] - q[2] * q[3]);
        result[0][2] = 2 * (q[0] * q[2] + q[1] * q[3]);
        result[1][0] = 2 * (q[0] * q[1] + q[2] * q[3]);
        result[1][1] = 1 - 2 * (q[0] * q[0] + q[2] * q[2]);
        result[1][2] = 2 * (q[1] * q[2] - q[0] * q[3]);
        result[2][0] = 2 * (q[0] * q[2] - q[1] * q[3]);
        result[2][1] = 2 * (q[1] * q[2] + q[0] * q[3]);
        result[2][2] = 1 - 2 * (q[0] * q[0] + q[1] * q[1]);
        return result;
    }

    template <Numeric T>
    inline auto Matrix<T, 4, 4>::Translate(const Vector3<T>& position) -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> m(T(1));
        m[0][3] = position.X;
        m[1][3] = position.Y;
        m[2][3] = position.Z;
        return m;
    }

    template <Numeric T>
    inline auto Matrix<T, 4, 4>::Scale(const Vector3<T>& scale) -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> m(T(1));
        m[0][0] = scale.X;
        m[1][1] = scale.Y;
        m[2][2] = scale.Z;
        return m;
    }

    template <Numeric T>
    auto Matrix<T, 4, 4>::LookAt(const Vector3<T>& position, const Vector3<T>& target, const Vector3<T>& up)
        -> Matrix<T, 4, 4>
    {
        Vector3<T> forward = (position - target).Normalized();
        Vector3<T> right = Vector3<T>::Cross(up, forward).Normalized();
        Vector3<T> cameraUp = Vector3<T>::Cross(forward, right);

        Matrix<T, 4, 4> result;
        result[0][0] = right.X;
        result[0][1] = right.Y;
        result[0][2] = right.Z;
        result[1][0] = cameraUp.X;
        result[1][1] = cameraUp.Y;
        result[1][2] = cameraUp.Z;
        result[2][0] = forward.X;
        result[2][1] = forward.Y;
        result[2][2] = forward.Z;
        result[0][3] = -Vector3<T>::Dot(right, position);
        result[1][3] = -Vector3<T>::Dot(cameraUp, position);
        result[2][3] = -Vector3<T>::Dot(forward, position);
        result[3][3] = T(1);
        return result;
    }

    template <Numeric T>
    inline constexpr Matrix<T, 4, 4>::Matrix(T x) noexcept
    {
        m_Data[0][0] = x;
        m_Data[1][1] = x;
        m_Data[2][2] = x;
        m_Data[3][3] = x;
    }

    template <Numeric T>
    inline constexpr auto Matrix<T, 4, 4>::operator[](Size i) noexcept -> T*
    {
        return m_Data[i];
    }

    template <Numeric T>
    inline constexpr auto Matrix<T, 4, 4>::operator[](Size i) const noexcept -> const T*
    {
        return m_Data[i];
    }

    template <Numeric T>
    auto Matrix<T, 4, 4>::Inverse() const -> Matrix
    {
        T i0 = m_Data[1][1] * m_Data[3][3];
        T i1 = m_Data[3][2] * m_Data[2][3];
        T i2 = m_Data[1][2] * m_Data[3][3];
        T i3 = m_Data[3][2] * m_Data[1][3];
        T i4 = m_Data[1][2] * m_Data[2][3];
        T i5 = m_Data[1][1] * m_Data[1][3];
        T i6 = m_Data[0][2] * m_Data[3][3];
        T i7 = m_Data[3][2] * m_Data[0][3];
        T i8 = m_Data[0][2] * m_Data[2][3];
        T i9 = m_Data[1][1] * m_Data[0][3];
        T i10 = m_Data[0][2] * m_Data[1][3];
        T i11 = m_Data[1][2] * m_Data[0][3];
        T i12 = m_Data[2][0] * m_Data[3][1];
        T i13 = m_Data[3][0] * m_Data[2][1];
        T i14 = m_Data[1][0] * m_Data[3][1];
        T i15 = m_Data[3][0] * m_Data[1][1];
        T i16 = m_Data[1][0] * m_Data[2][1];
        T i17 = m_Data[2][0] * m_Data[1][1];
        T i18 = m_Data[0][0] * m_Data[3][1];
        T i19 = m_Data[3][0] * m_Data[0][1];
        T i20 = m_Data[0][0] * m_Data[2][1];
        T i21 = m_Data[2][0] * m_Data[0][1];
        T i22 = m_Data[0][0] * m_Data[1][1];
        T i23 = m_Data[1][0] * m_Data[0][1];

        Matrix<T, 4, 4> inverse;
        inverse[0][0] = (i0 * m_Data[1][1] + i3 * m_Data[2][1] + i4 * m_Data[3][1]) -
                        (i1 * m_Data[1][1] + i2 * m_Data[2][1] + i5 * m_Data[3][1]);
        inverse[0][1] = (i1 * m_Data[0][1] + i6 * m_Data[2][1] + i9 * m_Data[3][1]) -
                        (i0 * m_Data[0][1] + i7 * m_Data[2][1] + i8 * m_Data[3][1]);
        inverse[0][2] = (i2 * m_Data[0][1] + i7 * m_Data[1][1] + i10 * m_Data[3][1]) -
                        (i3 * m_Data[0][1] + i6 * m_Data[1][1] + i11 * m_Data[3][1]);
        inverse[0][3] = (i5 * m_Data[0][1] + i8 * m_Data[1][1] + i11 * m_Data[2][1]) -
                        (i4 * m_Data[0][1] + i9 * m_Data[1][1] + i10 * m_Data[2][1]);

        T d = T(1) / (m_Data[0][0] * inverse[0][0] + m_Data[1][0] * inverse[0][1] + m_Data[2][0] * inverse[0][2] +
                      m_Data[3][0] * inverse[3][0]);

        inverse[0][0] = d * inverse[0][0];
        inverse[0][1] = d * inverse[0][1];
        inverse[0][2] = d * inverse[0][2];
        inverse[0][3] = d * inverse[0][3];

        inverse[1][0] = d * ((i1 * m_Data[1][0] + i2 * m_Data[2][0] + i5 * m_Data[3][0]) -
                             (i0 * m_Data[1][0] + i3 * m_Data[2][0] + i4 * m_Data[3][0]));
        inverse[1][1] = d * ((i0 * m_Data[0][0] + i7 * m_Data[2][0] + i8 * m_Data[3][0]) -
                             (i1 * m_Data[0][0] + i6 * m_Data[2][0] + i9 * m_Data[3][0]));
        inverse[1][2] = d * ((i3 * m_Data[0][0] + i6 * m_Data[1][0] + i11 * m_Data[3][0]) -
                             (i2 * m_Data[0][0] + i7 * m_Data[1][0] + i10 * m_Data[3][0]));
        inverse[1][3] = d * ((i4 * m_Data[0][0] + i9 * m_Data[1][0] + i10 * m_Data[2][0]) -
                             (i5 * m_Data[0][0] + i8 * m_Data[1][0] + i11 * m_Data[2][0]));

        inverse[2][0] = d * ((i12 * m_Data[1][3] + i15 * m_Data[2][3] + i16 * m_Data[3][3]) -
                             (i13 * m_Data[1][3] + i14 * m_Data[2][3] + i17 * m_Data[3][3]));
        inverse[2][1] = d * ((i13 * m_Data[3][0] + i18 * m_Data[2][3] + i21 * m_Data[3][3]) -
                             (i12 * m_Data[3][0] + i19 * m_Data[2][3] + i20 * m_Data[3][3]));
        inverse[2][2] = d * ((i14 * m_Data[3][0] + i19 * m_Data[1][3] + i22 * m_Data[3][3]) -
                             (i15 * m_Data[3][0] + i18 * m_Data[1][3] + i23 * m_Data[3][3]));
        inverse[2][3] = d * ((i17 * m_Data[3][0] + i20 * m_Data[1][3] + i23 * m_Data[2][3]) -
                             (i16 * m_Data[3][0] + i21 * m_Data[1][3] + i22 * m_Data[2][3]));

        inverse[3][0] = d * ((i14 * m_Data[2][2] + i17 * m_Data[3][2] + i13 * m_Data[1][2]) -
                             (i16 * m_Data[3][2] + i12 * m_Data[1][2] + i15 * m_Data[2][2]));
        inverse[3][1] = d * ((i20 * m_Data[3][2] + i12 * m_Data[2][0] + i19 * m_Data[2][2]) -
                             (i18 * m_Data[2][2] + i21 * m_Data[3][2] + i13 * m_Data[2][0]));
        inverse[3][2] = d * ((i18 * m_Data[1][2] + i23 * m_Data[3][2] + i15 * m_Data[2][0]) -
                             (i22 * m_Data[3][2] + i14 * m_Data[2][0] + i19 * m_Data[1][2]));
        inverse[3][3] = d * ((i22 * m_Data[2][2] + i16 * m_Data[2][0] + i21 * m_Data[1][2]) -
                             (i20 * m_Data[1][2] + i23 * m_Data[2][2] + i17 * m_Data[2][0]));
        return inverse;
    }

    template <Numeric T>
    auto Matrix<T, 4, 4>::Transposed() const -> Matrix
    {
        Matrix<T, 4, 4> m;
        for (Size i = 0; i < 4; ++i)
        {
            for (Size j = 0; j < 4; ++j)
            {
                m[i][j] = m_Data[j][i];
            }
        }
        return m;
    }

    template <Numeric T>
    constexpr auto operator+(const Matrix<T, 4, 4>& lhs, const Matrix<T, 4, 4>& rhs) noexcept -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> r;
        for (Size i = 0; i < 4; ++i)
        {
            for (Size j = 0; j < 4; ++j)
            {
                r[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return r;
    }

    template <Numeric T>
    constexpr auto operator-(const Matrix<T, 4, 4>& m) noexcept -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> r;
        for (Size i = 0; i < 4; ++i)
        {
            for (Size j = 0; j < 4; ++j)
            {
                r[i][j] = -m[i][j];
            }
        }
        return r;
    }

    template <Numeric T>
    constexpr auto operator-(const Matrix<T, 4, 4>& lhs, const Matrix<T, 4, 4>& rhs) noexcept -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> r;
        for (Size i = 0; i < 4; ++i)
        {
            for (Size j = 0; j < 4; ++j)
            {
                r[i][j] = lhs[i][j] - rhs[i][j];
            }
        }
        return r;
    }

    template <Numeric T>
    constexpr auto operator*(const Matrix<T, 4, 4>& lhs, const Matrix<T, 4, 4>& rhs) noexcept -> Matrix<T, 4, 4>
    {
        Matrix<T, 4, 4> r;
        for (Size i = 0; i < 4; ++i)
        {
            for (Size j = 0; j < 4; ++j)
            {
                r[i][j] = T(0);
                for (Size k = 0; k < 4; ++k)
                {
                    r[i][j] += lhs[i][k] * rhs[k][j];
                }
            }
        }
        return r;
    }

    template <Numeric T>
    using Matrix4x4 = Matrix<T, 4, 4>;

    using Matrix4x4f = Matrix4x4<Float32>;
    using Matrix4x4d = Matrix4x4<Float64>;
}

namespace std
{
    template <Lumy::Numeric T>
    struct formatter<Lumy::Matrix4x4<T>>
    {
        constexpr auto parse(auto& context) { return context.begin(); }

        auto format(const Lumy::Matrix4x4<T>& e, auto& context) const
        {
            return std::format_to(
                context.out(),
                "{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n{} {} {} {}",
                e[0][0],
                e[0][1],
                e[0][2],
                e[0][3],
                e[1][0],
                e[1][1],
                e[1][2],
                e[1][3],
                e[2][0],
                e[2][1],
                e[2][2],
                e[2][3],
                e[3][0],
                e[3][1],
                e[3][2],
                e[3][3]);
        }
    };

}

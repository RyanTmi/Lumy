#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Debug/Assert.hpp"
#include "LumyEngine/Math/Traits.hpp"
#include "LumyEngine/Math/Vector3.hpp"

#include <cmath>

namespace Lumy
{
    //==================================================================================================================
    // Class : Quaternion
    //==================================================================================================================

    template <Real T>
    class Quaternion;

    template <Real T>
    constexpr auto operator*(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept -> Quaternion<T>;

    template <Real T>
    class Quaternion
    {
    public:
        static const Quaternion Identity;

    public:
        constexpr static auto AxisAngle(T angle, const Vector3<T>& axis) noexcept -> Quaternion;

    public:
        constexpr Quaternion() noexcept;
        constexpr Quaternion(T x, T y, T z, T w) noexcept;
        constexpr Quaternion(T x, T y, T z) noexcept;
        constexpr explicit Quaternion(const Vector3<T>& euler) noexcept;

    public:
        constexpr auto operator[](UInt8 i) const noexcept -> T;
        constexpr auto operator[](UInt8 i) noexcept -> T&;

    public:
        constexpr auto NormSqr() const noexcept -> T;
        constexpr auto Norm() const noexcept -> T;
        constexpr auto EulerAngles() const noexcept -> Vector3<T>;
        constexpr auto Normalized() const noexcept -> Quaternion;
        constexpr auto Normalize() noexcept -> void;
        constexpr auto Inverse() noexcept -> void;
        constexpr auto Conjugate() noexcept -> Quaternion;

    private:
        T m_X;
        T m_Y;
        T m_Z;
        T m_W;
    };

    using Quaternionf = Quaternion<Float32>;
    using Quaterniond = Quaternion<Float64>;

    //==================================================================================================================
    // Class : Quaternion
    //==================================================================================================================

    template <Real T>
    const Quaternion<T> Quaternion<T>::Identity = Quaternion<T>();

    template <Real T>
    inline constexpr Quaternion<T>::Quaternion() noexcept
        : m_X(0), m_Y(0), m_Z(0), m_W(1)
    {}

    template <Real T>
    inline constexpr Quaternion<T>::Quaternion(T x, T y, T z, T w) noexcept
        : m_X(x), m_Y(y), m_Z(z), m_W(w)
    {}

    template <Real T>
    constexpr Quaternion<T>::Quaternion(T x, T y, T z) noexcept
    {
        T cx = std::cos(x * 0.5);
        T sx = std::sin(x * 0.5);
        T cy = std::cos(y * 0.5);
        T sy = std::sin(y * 0.5);
        T cz = std::cos(z * 0.5);
        T sz = std::sin(z * 0.5);

        m_X = sx * cy * cz - cx * sy * sz;
        m_Y = cx * sy * cz + sx * cy * sz;
        m_Z = cx * cy * sz - sx * sy * cz;
        m_W = cx * cy * cz + sx * sy * sz;
    }

    template <Real T>
    inline constexpr Quaternion<T>::Quaternion(const Vector3<T>& euler) noexcept
        : Quaternion(euler.X, euler.Y, euler.Z)
    {}

    template <Real T>
    inline constexpr auto Quaternion<T>::AxisAngle(T angle, const Vector3<T>& axis) noexcept -> Quaternion<T>
    {
        T halfAngle = angle * (M_PI / T(180)) / T(2);
        T s = std::sin(halfAngle);
        return Quaternion<T> {axis.X * s, axis.Y * s, axis.Z * s, std::cos(halfAngle)};
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::operator[](UInt8 i) const noexcept -> T
    {
        Assert(0 <= i and i <= 3);
        return reinterpret_cast<const T*>(this)[i];
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::operator[](UInt8 i) noexcept -> T&
    {
        Assert(0 <= i and i <= 3);
        return reinterpret_cast<T*>(this)[i];
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::NormSqr() const noexcept -> T
    {
        return m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W;
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::Norm() const noexcept -> T
    {
        return std::sqrt(NormSqr());
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::EulerAngles() const noexcept -> Vector3<T>
    {
        Vector3<T> euler;

        // roll (x-axis rotation)
        T sinr_cosp = 2 * (m_W * m_X + m_Y * m_Z);
        T cosr_cosp = 1 - 2 * (m_X * m_X + m_Y * m_Y);
        euler.X = std::atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        T sinp = std::sqrt(1 + 2 * (m_W * m_Y - m_X * m_Z));
        T cosp = std::sqrt(1 - 2 * (m_W * m_Y - m_X * m_Z));
        euler.Y = 2 * std::atan2(sinp, cosp) - M_PI / 2;

        // yaw (z-axis rotation)
        T siny_cosp = 2 * (m_W * m_Z + m_X * m_Y);
        T cosy_cosp = 1 - 2 * (m_Y * m_Y + m_Z * m_Z);
        euler.Z = std::atan2(siny_cosp, cosy_cosp);

        return euler;
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::Normalized() const noexcept -> Quaternion<T>
    {
        Quaternion<T> result = *this;
        result.Normalize();
        return result;
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::Normalize() noexcept -> void
    {
        T norm = Norm();
        if (norm > T(0))
        {
            T invNorm = T(1) / norm;
            m_X *= invNorm;
            m_Y *= invNorm;
            m_Z *= invNorm;
            m_W *= invNorm;
        }
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::Inverse() noexcept -> void
    {
        T normSqr = NormSqr();
        if (normSqr > T(0))
        {
            float invNorm = T(1) / normSqr;
            return Quaternion<T>(-m_X * invNorm, -m_Y * invNorm, -m_Z * invNorm, m_W * invNorm);
        }
        return Quaternion<T>();
    }

    template <Real T>
    inline constexpr auto Quaternion<T>::Conjugate() noexcept -> Quaternion<T>
    {
        return {-m_X, -m_Y, -m_Z, m_W};
    }

    template <Real T>
    constexpr auto operator*(const Quaternion<T>& lhs, const Quaternion<T>& rhs) noexcept -> Quaternion<T>
    {
        return {
            lhs[3] * rhs[0] + lhs[0] * rhs[3] + lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[3] * rhs[1] - lhs[0] * rhs[2] + lhs[1] * rhs[3] + lhs[2] * rhs[0],
            lhs[3] * rhs[2] + lhs[0] * rhs[1] - lhs[1] * rhs[0] + lhs[2] * rhs[3],
            lhs[3] * rhs[3] - lhs[0] * rhs[0] - lhs[1] * rhs[1] - lhs[2] * rhs[2]};
    }
}

#pragma once

#include "Vector.hpp"

namespace Lumy::Math
{
    //==================================================================================================================
    // Struct : Vector
    //==================================================================================================================

    template <Numeric T>
    struct Vector<T, 3>
    {
    public:
        T X;
        T Y;
        T Z;

    public:
        static const Vector Zero;
        static const Vector One;
        static const Vector Up;
        static const Vector Down;
        static const Vector Left;
        static const Vector Right;
        static const Vector Forward;
        static const Vector Back;

    public:
        static constexpr auto Cross(const Vector& lhs, const Vector& rhs) noexcept -> Vector;
        static constexpr auto Distance(const Vector& lhs, const Vector& rhs) noexcept -> T;
        static constexpr auto Dot(const Vector& lhs, const Vector& rhs) noexcept -> T;
        static constexpr auto Lerp(const Vector& lhs, const Vector& rhs, Float32 t) noexcept -> Vector;

    public:
        constexpr Vector() noexcept = default;
        constexpr Vector(T x) noexcept;
        constexpr Vector(T x, T y, T z) noexcept;

    public:
        constexpr auto operator[](Size i) const noexcept -> T;
        constexpr auto operator[](Size i) noexcept -> T&;

    public:
        constexpr auto Norm() const -> T;
        constexpr auto NormSqr() const -> T;
        constexpr auto Normalized() const -> Vector;

        constexpr auto Normalize() -> Vector&;

    public:
        friend constexpr auto operator+ <>(const Vector& lhs, const Vector& rhs) noexcept -> Vector;
        friend constexpr auto operator+= <>(Vector& lhs, const Vector& rhs) noexcept -> Vector&;

        friend constexpr auto operator- <>(const Vector& lhs, const Vector& rhs) noexcept -> Vector;
        friend constexpr auto operator-= <>(Vector& lhs, const Vector& rhs) noexcept -> Vector&;

        friend constexpr auto operator* <>(T s, const Vector& v) noexcept -> Vector;
        friend constexpr auto operator* <>(const Vector& v, T s) noexcept -> Vector;
        friend constexpr auto operator*= <>(Vector& v, T s) noexcept -> Vector&;

        friend constexpr auto operator/ <>(T s, const Vector& v) noexcept -> Vector;
        friend constexpr auto operator/ <>(const Vector& v, T s) noexcept -> Vector;
        friend constexpr auto operator/= <>(Vector& v, T s) noexcept -> Vector&;
    };

    //==================================================================================================================
    // Struct : Vector
    //==================================================================================================================

    template <Numeric T>
    inline const Vector<T, 3> Vector<T, 3>::Zero = Vector<T, 3>(0);

    template <Numeric T>
    inline const Vector<T, 3> Vector<T, 3>::One = Vector<T, 3>(1);

    template <Numeric T>
    inline const Vector<T, 3> Vector<T, 3>::Up = Vector<T, 3>(0, 1, 0);

    template <Numeric T>
    inline const Vector<T, 3> Vector<T, 3>::Down = Vector<T, 3>(0, -1, 0);

    template <Numeric T>
    inline const Vector<T, 3> Vector<T, 3>::Left = Vector<T, 3>(-1, 0, 0);

    template <Numeric T>
    inline const Vector<T, 3> Vector<T, 3>::Right = Vector<T, 3>(1, 0, 0);

    template <Numeric T>
    inline const Vector<T, 3> Vector<T, 3>::Forward = Vector<T, 3>(0, 0, 1);

    template <Numeric T>
    inline const Vector<T, 3> Vector<T, 3>::Back = Vector<T, 3>(0, 0, -1);

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::Cross(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept -> Vector<T, 3>
    {
        return {lhs.Y * rhs.Z - lhs.Z * rhs.Y, lhs.Z * rhs.X - lhs.X * rhs.Z, lhs.X * rhs.Y - lhs.Y * rhs.X};
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::Distance(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept -> T
    {
        return (lhs - rhs).Norm();
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::Dot(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept -> T
    {
        return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
    }

    template <Numeric T>
    inline constexpr auto
        Vector<T, 3>::Lerp(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs, Float32 t) noexcept -> Vector<T, 3>
    {
        return t * lhs + (1 - t) * rhs;
    }

    template <Numeric T>
    inline constexpr Vector<T, 3>::Vector(T x) noexcept
        : Vector(x, x, x)
    {}

    template <Numeric T>
    inline constexpr Vector<T, 3>::Vector(T x, T y, T z) noexcept
        : X(x), Y(y), Z(z)
    {}

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::operator[](Size i) const noexcept -> T
    {
        return reinterpret_cast<T*>(this)[i];
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::operator[](Size i) noexcept -> T&
    {
        return reinterpret_cast<T*>(this)[i];
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::Norm() const -> T
    {
        return std::sqrt(NormSqr());
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::NormSqr() const -> T
    {
        return Dot(*this, *this);
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::Normalized() const -> Vector<T, 3>
    {
        return *this / Norm();
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 3>::Normalize() -> Vector<T, 3>&
    {
        return *this /= Norm();
    }

    template <Numeric T>
    inline constexpr auto operator+(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept -> Vector<T, 3>
    {
        return {lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z};
    }

    template <Numeric T>
    inline constexpr auto operator+=(Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept -> Vector<T, 3>&
    {
        lhs.X += rhs.X;
        lhs.Y += rhs.Y;
        lhs.Z += rhs.Z;
        return lhs;
    }

    template <Numeric T>
    inline constexpr auto operator-(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept -> Vector<T, 3>
    {
        return {lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z};
    }

    template <Numeric T>
    inline constexpr auto operator-=(Vector<T, 3>& lhs, const Vector<T, 3>& rhs) noexcept -> Vector<T, 3>&
    {
        lhs.X -= rhs.X;
        lhs.Y -= rhs.Y;
        lhs.Z -= rhs.Z;
        return lhs;
    }

    template <Numeric T>
    inline constexpr auto operator*(T s, const Vector<T, 3>& v) noexcept -> Vector<T, 3>
    {
        return {s * v.X, s * v.Y, s * v.Z};
    }

    template <Numeric T>
    inline constexpr auto operator*(const Vector<T, 3>& v, T s) noexcept -> Vector<T, 3>
    {
        return s * v;
    }

    template <Numeric T>
    inline constexpr auto operator*=(Vector<T, 3>& v, T s) -> Vector<T, 3>&
    {
        v.X *= s;
        v.Y *= s;
        v.Z *= s;
        return v;
    }

    template <Numeric T>
    inline constexpr auto operator/(T s, const Vector<T, 3>& v) noexcept -> Vector<T, 3>
    {
        return {s / v.X, s / v.Y, s / v.Z};
    }

    template <Numeric T>
    inline constexpr auto operator/(const Vector<T, 3>& v, T s) noexcept -> Vector<T, 3>
    {
        return {v.X / s, v.Y / s, v.Z / s};
    }

    template <Numeric T>
    inline constexpr auto operator/=(Vector<T, 3>& v, T s) noexcept -> Vector<T, 3>&
    {
        v.X /= s;
        v.Y /= s;
        v.Z /= s;
        return v;
    }
}

namespace Lumy
{
    using Vector3 = Math::Vector<Float32, 3>;
    using Vector3I = Math::Vector<Int32, 3>;
}

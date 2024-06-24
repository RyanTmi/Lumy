#pragma once

#include "Vector.hpp"

namespace Lumy
{
    //==================================================================================================================
    // Struct : Vector
    //==================================================================================================================

    template <Numeric T>
    struct Vector<T, 2>
    {
    public:
        T X;
        T Y;

    public:
        static const Vector Zero;
        static const Vector One;
        static const Vector Up;
        static const Vector Down;
        static const Vector Left;
        static const Vector Right;

    public:
        static constexpr auto Distance(const Vector& lhs, const Vector& rhs) noexcept -> T;
        static constexpr auto Dot(const Vector& lhs, const Vector& rhs) noexcept -> T;
        static constexpr auto Lerp(const Vector& lhs, const Vector& rhs, Float32 t) noexcept -> Vector;

    public:
        constexpr Vector() noexcept = default;
        constexpr Vector(T x) noexcept;
        constexpr Vector(T x, T y) noexcept;

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
    inline const Vector<T, 2> Vector<T, 2>::Zero = Vector<T, 2>(0);

    template <Numeric T>
    inline const Vector<T, 2> Vector<T, 2>::One = Vector<T, 2>(1);

    template <Numeric T>
    inline const Vector<T, 2> Vector<T, 2>::Up = Vector<T, 2>(0, 1);

    template <Numeric T>
    inline const Vector<T, 2> Vector<T, 2>::Down = Vector<T, 2>(0, -1);

    template <Numeric T>
    inline const Vector<T, 2> Vector<T, 2>::Left = Vector<T, 2>(-1, 0);

    template <Numeric T>
    inline const Vector<T, 2> Vector<T, 2>::Right = Vector<T, 2>(1, 0);

    template <Numeric T>
    inline constexpr auto Vector<T, 2>::Distance(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs) noexcept -> T
    {
        return (lhs - rhs).Norm();
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 2>::Dot(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs) noexcept -> T
    {
        return lhs.X * rhs.X + lhs.Y * rhs.Y;
    }

    template <Numeric T>
    inline constexpr auto
        Vector<T, 2>::Lerp(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs, Float32 t) noexcept -> Vector<T, 2>
    {
        return t * lhs + (1 - t) * rhs;
    }

    template <Numeric T>
    inline constexpr Vector<T, 2>::Vector(T x) noexcept
        : Vector(x, x)
    {}

    template <Numeric T>
    inline constexpr Vector<T, 2>::Vector(T x, T y) noexcept
        : X(x), Y(y)
    {}

    template <Numeric T>
    inline constexpr auto Vector<T, 2>::operator[](Size i) const noexcept -> T
    {
        return reinterpret_cast<T*>(this)[i];
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 2>::operator[](Size i) noexcept -> T&
    {
        return reinterpret_cast<T*>(this)[i];
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 2>::Norm() const -> T
    {
        return std::sqrt(NormSqr());
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 2>::NormSqr() const -> T
    {
        return Dot(*this, *this);
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 2>::Normalized() const -> Vector<T, 2>
    {
        return *this / Norm();
    }

    template <Numeric T>
    inline constexpr auto Vector<T, 2>::Normalize() -> Vector<T, 2>&
    {
        return *this /= Norm();
    }

    template <Numeric T>
    inline constexpr Vector<T, 2> operator+(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs) noexcept
    {
        return {lhs.X + rhs.X, lhs.Y + rhs.Y};
    }

    template <Numeric T>
    inline constexpr Vector<T, 2>& operator+=(Vector<T, 2>& lhs, const Vector<T, 2>& rhs) noexcept
    {
        lhs.X += rhs.X;
        lhs.Y += rhs.Y;
        return lhs;
    }

    template <Numeric T>
    inline constexpr Vector<T, 2> operator-(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs) noexcept
    {
        return {lhs.X - rhs.X, lhs.Y - rhs.Y};
    }

    template <Numeric T>
    inline constexpr Vector<T, 2>& operator-=(Vector<T, 2>& lhs, const Vector<T, 2>& rhs) noexcept
    {
        lhs.X -= rhs.X;
        lhs.Y -= rhs.Y;
        return lhs;
    }

    template <Numeric T>
    inline constexpr Vector<T, 2> operator*(T s, const Vector<T, 2>& v) noexcept
    {
        return {s * v.X, s * v.Y};
    }

    template <Numeric T>
    inline constexpr Vector<T, 2> operator*(const Vector<T, 2>& v, T s) noexcept
    {
        return s * v;
    }

    template <Numeric T>
    inline constexpr Vector<T, 2>& operator*=(Vector<T, 2>& v, T s)
    {
        v.X *= s;
        v.Y *= s;
        return v;
    }

    template <Numeric T>
    inline constexpr Vector<T, 2> operator/(T s, const Vector<T, 2>& v) noexcept
    {
        return {s / v.X, s / v.Y};
    }

    template <Numeric T>
    inline constexpr Vector<T, 2> operator/(const Vector<T, 2>& v, T s) noexcept
    {
        return {v.X / s, v.Y / s};
    }

    template <Numeric T>
    inline constexpr Vector<T, 2>& operator/=(Vector<T, 2>& v, T s)
    {
        v.X /= s;
        v.Y /= s;
        return v;
    }

    template <Numeric T>
    using Vector2 = Vector<T, 2>;

    using Vector2d = Vector2<Float64>;
    using Vector2f = Vector2<Float32>;
    using Vector2i = Vector2<Int32>;
    using Vector2b = Vector2<bool>;
}

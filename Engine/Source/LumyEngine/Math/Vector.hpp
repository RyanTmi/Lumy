#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Math/Traits.hpp"

#include <algorithm>
#include <array>
#include <initializer_list>
#include <numeric>
#include <type_traits>

namespace Lumy
{
    template <Numeric T, Size N>
    class Vector;

    template <Numeric T, Size N>
    constexpr auto operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> Vector<T, N>;

    template <Numeric T, Size N>
    constexpr auto operator+=(Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> Vector<T, N>&;

    template <Numeric T, Size N>
    constexpr auto operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> Vector<T, N>;

    template <Numeric T, Size N>
    constexpr auto operator-=(Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> Vector<T, N>&;

    template <Numeric T, Size N>
    constexpr auto operator*(T s, const Vector<T, N>& v) noexcept -> Vector<T, N>;

    template <Numeric T, Size N>
    constexpr auto operator*(const Vector<T, N>& v, T s) noexcept -> Vector<T, N>;

    template <Numeric T, Size N>
    constexpr auto operator*=(Vector<T, N>& v, T s) noexcept -> Vector<T, N>&;

    template <Numeric T, Size N>
    constexpr auto operator/(T s, const Vector<T, N>& v) noexcept -> Vector<T, N>;

    template <Numeric T, Size N>
    constexpr auto operator/(const Vector<T, N>& v, T s) noexcept -> Vector<T, N>;

    template <Numeric T, Size N>
    constexpr auto operator/=(Vector<T, N>& v, T s) noexcept -> Vector<T, N>&;

    template <Numeric T, Size N>
    struct Vector
    {
    public:
        static constinit Vector Zero;
        static constinit Vector One;

    public:
        static constexpr auto Distance(const Vector& lhs, const Vector& rhs) noexcept -> T;
        static constexpr auto Dot(const Vector& lhs, const Vector& rhs) noexcept -> T;
        static constexpr auto Lerp(const Vector& lhs, const Vector& rhs, Float32 t) noexcept -> Vector;

    public:
        constexpr Vector() noexcept = default;
        constexpr Vector(T x) noexcept;
        constexpr Vector(std::initializer_list<T> init) noexcept;

    public:
        constexpr auto operator[](Size i) const noexcept -> T;
        constexpr auto operator[](Size i) noexcept -> T&;

    public:
        // TODO: Change `Float64` to `Float32` according to the size of `T`.
        // TODO: Specify the norm used
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

    private:
        // TODO: Use C-array or own Array type
        std::array<T, N> m_Data;
    };

    template <Numeric T, Size N>
    inline constinit Vector<T, N> Vector<T, N>::Zero = Vector<T, N>(T(0));

    template <Numeric T, Size N>
    inline constinit Vector<T, N> Vector<T, N>::One = Vector<T, N>(T(1));

    template <Numeric T, Size N>
    inline constexpr auto Vector<T, N>::Distance(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> T
    {
        return (lhs - rhs).Norm();
    }

    template <Numeric T, Size N>
    inline constexpr auto
        Vector<T, N>::Lerp(const Vector<T, N>& lhs, const Vector<T, N>& rhs, Float32 t) noexcept -> Vector<T, N>
    {
        return t * lhs + (1 - t) * rhs;
    }

    template <Numeric T, Size N>
    inline constexpr auto Vector<T, N>::Dot(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> T
    {
        return std::inner_product(lhs.m_Data.begin(), lhs.m_Data.end(), rhs.m_Data.begin(), T(0));
    }

    template <Numeric T, Size N>
    constexpr Vector<T, N>::Vector(T x) noexcept
        : m_Data()
    {
        m_Data.fill(x);
    }

    template <Numeric T, Size N>
    inline constexpr Vector<T, N>::Vector(std::initializer_list<T> init) noexcept
        : m_Data()
    {
        std::copy(init.begin(), init.end(), m_Data.begin());
    }

    template <Numeric T, Size N>
    inline constexpr auto Vector<T, N>::operator[](Size i) const noexcept -> T
    {
        return m_Data[i];
    }

    template <Numeric T, Size N>
    inline constexpr auto Vector<T, N>::operator[](Size i) noexcept -> T&
    {
        return m_Data[i];
    }

    template <Numeric T, Size N>
    inline constexpr auto Vector<T, N>::Norm() const -> T
    {
        return std::sqrt(NormSqr());
    }

    template <Numeric T, Size N>
    inline constexpr auto Vector<T, N>::NormSqr() const -> T
    {
        return Dot(*this, *this);
    }

    template <Numeric T, Size N>
    inline constexpr auto Vector<T, N>::Normalized() const -> Vector<T, N>
    {
        return *this / Norm();
    }

    template <Numeric T, Size N>
    inline constexpr auto Vector<T, N>::Normalize() -> Vector<T, N>&
    {
        return *this /= Norm();
    }

    template <Numeric T, Size N>
    inline constexpr auto operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> Vector<T, N>
    {
        Vector<T, N> v;
        std::ranges::transform(lhs.m_Data, rhs.m_Data, v.m_Data.begin(), std::plus {});
        return v;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator+=(Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> Vector<T, N>&
    {
        std::ranges::transform(lhs.m_Data, rhs.m_Data, lhs.m_Data.begin(), std::plus {});
        return lhs;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> Vector<T, N>
    {
        Vector<T, N> v;
        std::ranges::transform(lhs.m_Data, rhs.m_Data, v.m_Data.begin(), std::minus {});
        return v;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator-=(Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept -> Vector<T, N>&
    {
        std::ranges::transform(lhs.m_Data, rhs.m_Data, lhs.m_Data.begin(), std::minus {});
        return lhs;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator*(T s, const Vector<T, N>& v) noexcept -> Vector<T, N>
    {
        Vector<T, N> r;
        std::ranges::transform(v.m_Data, r.m_Data.begin(), [s](T x) { return s * x; });
        return r;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator*(const Vector<T, N>& v, T s) noexcept -> Vector<T, N>
    {
        return s * v;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator*=(Vector<T, N>& v, T s) noexcept -> Vector<T, N>&
    {
        std::ranges::transform(v.m_Data, v.m_Data.begin(), [s](T x) { return x * s; });
        return v;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator/(T s, const Vector<T, N>& v) noexcept -> Vector<T, N>
    {
        Vector<T, N> r;
        std::ranges::transform(v.m_Data, r.m_Data.begin(), [s](T x) { return s / x; });
        return r;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator/(const Vector<T, N>& v, T s) noexcept -> Vector<T, N>
    {
        Vector<T, N> r;
        std::ranges::transform(v.m_Data, r.m_Data.begin(), [s](T x) { return x / s; });
        return r;
    }

    template <Numeric T, Size N>
    inline constexpr auto operator/=(Vector<T, N>& v, T s) noexcept -> Vector<T, N>&
    {
        std::ranges::transform(v.m_Data, v.m_Data.begin(), [s](T x) { return x / s; });
        return v;
    }
}

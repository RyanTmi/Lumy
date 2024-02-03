#pragma once

#include <iostream>

#include "LumyEngine/Core/Types.hpp"

namespace Lumy
{
    class Vector2
    {
    public:
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 Left;
        static const Vector2 Right;
        static const Vector2 Up;
        static const Vector2 Down;

        static Vector2 Normalize(Vector2 v);
        static Float32 Dot(Vector2 u, Vector2 v);
        static Vector2 Lerp(Vector2 from, Vector2 to, Float32 t);
        static Vector2 Project(Vector2 u, Vector2 v);
        static Vector2 Reject(Vector2 u, Vector2 v);

        Vector2() = default;
        inline Vector2(Float32 x, Float32 y)
            : X(x), Y(y)
        {
        }

        Float32 SqrMagnitude() const;
        Float32 Magnitude() const;
        Vector2& Normalize();

        Float32 operator[](UInt16 i) const;
        void Set(Float32 x, Float32 y);

        Vector2 operator+(Vector2 vector) const;
        Vector2& operator+=(Vector2 vector);

        Vector2 operator-(Vector2 vector) const;
        Vector2& operator-=(Vector2 vector);

        Vector2 operator*(Float32 scalar) const;
        friend Vector2 operator*(Float32 scalar, Vector2 vector);
        Vector2& operator*=(Float32 scalar);

        Vector2 operator/(Float32 scalar) const;
        Vector2& operator/=(Float32 scalar);

        Bool8 operator==(Vector2 vector) const;
        Bool8 operator!=(Vector2 vector) const;
    public:
        Float32 X;
        Float32 Y;
    };

    std::ostream& operator<<(std::ostream& os, const Vector2& v);
}

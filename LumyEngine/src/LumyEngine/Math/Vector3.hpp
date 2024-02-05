#pragma once

#include <iostream>

#include "LumyEngine/Core/Types.hpp"

namespace Lumy
{
    class Vector3
    {
    public:
        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 Left;
        static const Vector3 Right;
        static const Vector3 Up;
        static const Vector3 Down;
        static const Vector3 Forward;
        static const Vector3 Back;

        static Vector3 Normalize(Vector3 v);
        static Float32 Dot(Vector3 u, Vector3 v);
        static Vector3 Lerp(Vector3 from, Vector3 to, Float32 t);

        Vector3() = default;
        inline Vector3(Float32 x, Float32 y, Float32 z)
            : X(x), Y(y), Z(z)
        {
        }

        Float32 SqrMagnitude() const;
        Float32 Magnitude() const;
        Vector3& Normalize();

        Float32 operator[](UInt16 i) const;
        void Set(Float32 x, Float32 y, Float32 z);

        Vector3 operator+(Vector3 vector) const;
        Vector3& operator+=(Vector3 vector);

        Vector3 operator-(Vector3 vector) const;
        Vector3& operator-=(Vector3 vector);

        Vector3 operator*(Float32 scalar) const;
        friend Vector3 operator*(Float32 scalar, Vector3 vector);
        Vector3& operator*=(Float32 scalar);

        Vector3 operator/(Float32 scalar) const;
        Vector3& operator/=(Float32 scalar);

        Bool8 operator==(Vector3 vector) const;
        Bool8 operator!=(Vector3 vector) const;
    public:
        Float32 X;
        Float32 Y;
        Float32 Z;
    };

    std::ostream& operator<<(std::ostream& os, const Vector3& v);
}

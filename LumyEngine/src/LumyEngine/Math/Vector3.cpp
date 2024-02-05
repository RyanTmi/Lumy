#include "Vector3.hpp"

#include "LumyEngine/Core/Foundation.hpp"
#include "MathF.hpp"

namespace Lumy
{
    const Vector3 Vector3::Zero    = Vector3( 0.0f,  0.0f,  0.0f);
    const Vector3 Vector3::One     = Vector3( 1.0f,  1.0f,  1.0f);
    const Vector3 Vector3::Left    = Vector3(-1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::Right   = Vector3( 1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::Up      = Vector3( 0.0f,  1.0f,  0.0f);
    const Vector3 Vector3::Down    = Vector3( 0.0f, -1.0f,  0.0f);
    const Vector3 Vector3::Forward = Vector3( 0.0f,  0.0f,  1.0f);
    const Vector3 Vector3::Back    = Vector3( 0.0f,  0.0f, -1.0f);

    Vector3 Vector3::Normalize(Vector3 v)
    {
        return v / v.Magnitude();
    }

    Float32 Vector3::Dot(Vector3 u, Vector3 v)
    {
        return u.X * v.X + u.Y + v.Y + u.Z * v.Z;
    }

    Vector3 Vector3::Lerp(Vector3 from, Vector3 to, Float32 t)
    {
        return ((1.0f - t) * from) + (t * to);
    }

    Float32 Vector3::SqrMagnitude() const
    {
        return X * X + Y * Y + Z * Z;
    }

    Float32 Vector3::Magnitude() const
    {
        return MathF::Sqrt(SqrMagnitude());
    }

    Vector3& Vector3::Normalize()
    {
        *this /= Magnitude();
        return *this;
    }

    Float32 Vector3::operator[](UInt16 i) const
    {
        if (i > 2)
        {
            Log::Warn("Vector3: operator[]: Index {} out of bound. Returning 1.0f", i);
            return 1;
        }
        return reinterpret_cast<const Float32*>(this)[i];
    }

    void Vector3::Set(Float32 x, Float32 y, Float32 z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    Vector3 Vector3::operator+(Vector3 vector) const
    {
        return {X + vector.X, Y + vector.Y, Z + vector.Z};
    }

    Vector3& Vector3::operator+=(Vector3 vector)
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        return *this;
    }

    Vector3 Vector3::operator-(Vector3 vector) const
    {
        return {X - vector.X, Y - vector.Y, Z - vector.Z};
    }

    Vector3& Vector3::operator-=(Vector3 vector)
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
        return *this;
    }

    Vector3 Vector3::operator*(Float32 scalar) const
    {
        return {scalar * X, scalar * Y, scalar * Z};
    }

    Vector3 operator*(Float32 scalar, Vector3 vector)
    {
        return vector.operator*(scalar);
    }

    Vector3& Vector3::operator*=(Float32 scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    Vector3 Vector3::operator/(Float32 scalar) const
    {
        return {scalar / X, scalar / Y, scalar / Z};
    }

    Vector3& Vector3::operator/=(Float32 scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        return *this;
    }

    Bool8 Vector3::operator==(Vector3 vector) const
    {
        return X == vector.X && Y == vector.Y && Z == vector.Z;
    }

    Bool8 Vector3::operator!=(Vector3 vector) const
    {
        return X != vector.X || Y != vector.Y || Z != vector.Z;
    }

    std::ostream& operator<<(std::ostream& os, const Vector3& v)
    {
        os << "[" << v.X << ", " << v.Y << ", " << v.Z << "]";
        return os;
    }
}

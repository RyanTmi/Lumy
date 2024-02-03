#include "Vector2.hpp"

#include "LumyEngine/Core/Foundation.hpp"
#include "MathF.hpp"

namespace Lumy
{
    const Vector2 Vector2::Zero  = Vector2( 0.0f,  0.0f);
    const Vector2 Vector2::One   = Vector2( 1.0f,  1.0f);
    const Vector2 Vector2::Left  = Vector2(-1.0f,  0.0f);
    const Vector2 Vector2::Right = Vector2( 1.0f,  0.0f);
    const Vector2 Vector2::Up    = Vector2( 0.0f,  1.0f);
    const Vector2 Vector2::Down  = Vector2( 0.0f, -1.0f);

    Vector2 Vector2::Normalize(Vector2 v)
    {
        return v / v.Magnitude();
    }

    Float32 Vector2::Dot(Vector2 u, Vector2 v)
    {
        return u.X * v.X + u.Y + v.Y;
    }

    Vector2 Vector2::Lerp(Vector2 from, Vector2 to, Float32 t)
    {
        return ((1.0f - t) * from) + (t * to);
    }

    Vector2 Vector2::Project(Vector2 u, Vector2 v)
    {
        return (v * (Dot(u, v) / Dot(v, v)));
    }

    Vector2 Vector2::Reject(Vector2 u, Vector2 v)
    {
        return (u - (v * (Dot(u, v) / Dot(v, v))));
    }


    Float32 Vector2::SqrMagnitude() const
    {
        return X * X + Y * Y;
    }

    Float32 Vector2::Magnitude() const
    {
        return MathF::Sqrt(SqrMagnitude());
    }

    Vector2& Vector2::Normalize()
    {
        *this /= Magnitude();
        return *this;
    }

    Float32 Vector2::operator[](UInt16 i) const
    {
        if (i > 1)
        {
            Log::Warn("Vector2: operator[]: Index {} out of bound. Returning 1.0f", i);
            return 1;
        }
        return reinterpret_cast<const Float32*>(this)[i];
    }

    void Vector2::Set(Float32 x, Float32 y)
    {
        X = x;
        Y = y;
    }

    Vector2 Vector2::operator+(Vector2 vector) const
    {
        return {X + vector.X, Y + vector.Y};
    }

    Vector2& Vector2::operator+=(Vector2 vector)
    {
        X += vector.X;
        Y += vector.Y;
        return *this;
    }

    Vector2 Vector2::operator-(Vector2 vector) const
    {
        return {X - vector.X, Y - vector.Y};
    }

    Vector2& Vector2::operator-=(Vector2 vector)
    {
        X -= vector.X;
        Y -= vector.Y;
        return *this;
    }

    Vector2 Vector2::operator*(Float32 scalar) const
    {
        return {scalar * X, scalar * Y};
    }

    Vector2 operator*(Float32 scalar, Vector2 vector)
    {
        return vector.operator*(scalar);
    }

    Vector2& Vector2::operator*=(Float32 scalar)
    {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    Vector2 Vector2::operator/(Float32 scalar) const
    {
        return {scalar / X, scalar / Y};
    }

    Vector2& Vector2::operator/=(Float32 scalar)
    {
        X /= scalar;
        Y /= scalar;
        return *this;
    }

    Bool8 Vector2::operator==(Vector2 vector) const
    {
        return X == vector.X && Y == vector.Y;
    }

    Bool8 Vector2::operator!=(Vector2 vector) const
    {
        return X != vector.X || Y != vector.Y;
    }

    std::ostream& operator<<(std::ostream& os, const Vector2& v)
    {
        os << "[" << v.X << ", " << v.Y << "]";
        return os;
    }
}

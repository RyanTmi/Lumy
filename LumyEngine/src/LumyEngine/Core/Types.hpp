/**
 * @file Types.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Definition of fundamental types for the game engine.
 * @version 0.2
 * @date 2023-11-18
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

namespace Lumy
{
    /**
     * @brief Alias for unsigned integer types.
     */
    using UInt8  = unsigned char;
    using UInt16 = unsigned short;
    using UInt32 = unsigned int;
    using UInt64 = unsigned long;

    /**
     * @brief Alias for signed integer types.
     */
    using Int8  = char;
    using Int16 = short;
    using Int32 = int;
    using Int64 = long;

    /**
     * @brief Alias for floating-point types.
     */
    struct Float32
    {
    public:
        constexpr Float32(float x = 0.0f)
            : m_X(x)
        {}
        operator float() const { return m_X; }

        Float32 operator+(Float32 x) const { return m_X + x; }
        Float32& operator+=(Float32 x) { m_X += x; return *this; }

        Float32 operator-(Float32 x) const { return m_X - x; }
        Float32& operator-=(Float32 x) { m_X -= x; return *this; }

        Float32 operator*(Float32 x) const { return m_X * x; }
        Float32& operator*=(Float32 x) { m_X *= x; return *this; }

        Float32 operator/(Float32 x) const { return m_X / x; }
        Float32& operator/=(Float32 x) { m_X /= x; return *this; }

        bool operator==(float x) const { return m_X == x; }
        bool operator==(Float32 x) const { return m_X == x; }
        bool operator!=(float x) const { return m_X != x; }
        bool operator!=(Float32 x) const { return m_X != x; }
    private:
        float m_X;
    };

    using Float64 = double;

    /**
     * @brief Alias for boolean types.
     */
    using Bool8 = bool;

    /**
     * @brief Static assertions to check the size of types.
     */
    static_assert(sizeof(UInt8 ) == 1, "Expected UInt8 to be 1 byte.");
    static_assert(sizeof(UInt16) == 2, "Expected u16 to be 2 byte.");
    static_assert(sizeof(UInt32) == 4, "Expected UInt32 to be 4 byte.");
    static_assert(sizeof(UInt64) == 8, "Expected UInt64 to be 8 byte.");

    static_assert(sizeof(Int8 ) == 1, "Expected Int8 to be 1 byte.");
    static_assert(sizeof(Int16) == 2, "Expected Int16 to be 2 byte.");
    static_assert(sizeof(Int32) == 4, "Expected Int32 to be 4 byte.");
    static_assert(sizeof(Int64) == 8, "Expected Int64 to be 8 byte.");

    static_assert(sizeof(Float32) == 4, "Expected Float32 to be 4 byte.");
    static_assert(sizeof(Float64) == 8, "Expected Float64 to be 8 byte.");

    static_assert(sizeof(Bool8 ) == 1, "Expected Bool8 to be 1 byte.");

    /**
     * @brief Macro to define bits.
     */
    #define BIT(x) (1UL << (x))
}

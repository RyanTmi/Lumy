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
    using uint8_t  = unsigned char;
    using uint16_t = unsigned short;
    using uint32_t = unsigned int;
    using uint64_t = unsigned long;

    using int8_t   = signed char;
    using int16_t  = short;
    using int32_t  = int;
    using int64_t  = long;

    using float32_t = float;
    using float64_t = double;

    using bool8_t = bool;

    using UInt8  = unsigned char;
    using UInt16 = unsigned short;
    using UInt32 = unsigned int;
    using UInt64 = unsigned long;

    using Int8   = signed char;
    using Int16  = short;
    using Int32  = int;
    using Int64  = long;

    using Float32 = float;
    using Float64 = double;

    using Bool8 = bool;

    // struct UInt8
    // {
    // public:
    //     explicit constexpr UInt8(uint8_t x = 0)
    //          : m_X(x)
    //     {}
    //     explicit operator uint8_t() const { return m_X; }

    //     UInt8 operator+(UInt8 x) const { return UInt8(m_X + x.m_X); }
    //     UInt8& operator+=(UInt8 x) { m_X += x.m_X; return *this; }

    //     UInt8 operator-(UInt8 x) const { return UInt8(m_X - x.m_X); }
    //     UInt8& operator-=(UInt8 x) { m_X -= x.m_X; return *this; }

    //     UInt8 operator*(UInt8 x) const { return UInt8(m_X * x.m_X); }
    //     UInt8& operator*=(UInt8 x) { m_X *= x.m_X; return *this; }

    //     UInt8 operator/(UInt8 x) const { return UInt8(m_X / x.m_X); }
    //     UInt8& operator/=(UInt8 x) { m_X /= x.m_X; return *this; }

    //     bool8_t operator==(uint8_t x) const { return m_X == x; }
    //     bool8_t operator==(UInt8 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(uint8_t x) const { return m_X != x; }
    //     bool8_t operator!=(UInt8 x) const { return m_X != x.m_X; }
    // private:
    //     uint8_t m_X;
    // };

    // struct UInt16
    // {
    // public:
    //     constexpr UInt16(uint16_t x = 0)
    //          : m_X(x)
    //     {}
    //     operator uint16_t() const { return m_X; }

    //     UInt16 operator+(UInt16 x) const { return UInt16(m_X + x.m_X); }
    //     UInt16& operator+=(UInt16 x) { m_X += x.m_X; return *this; }

    //     UInt16 operator-(UInt16 x) const { return UInt16(m_X - x.m_X); }
    //     UInt16& operator-=(UInt16 x) { m_X -= x.m_X; return *this; }

    //     UInt16 operator*(UInt16 x) const { return UInt16(m_X * x.m_X); }
    //     UInt16& operator*=(UInt16 x) { m_X *= x.m_X; return *this; }

    //     UInt16 operator/(UInt16 x) const { return UInt16(m_X / x.m_X); }
    //     UInt16& operator/=(UInt16 x) { m_X /= x.m_X; return *this; }

    //     bool8_t operator==(uint16_t x) const { return m_X == x; }
    //     bool8_t operator==(UInt16 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(uint16_t x) const { return m_X != x; }
    //     bool8_t operator!=(UInt16 x) const { return m_X != x.m_X; }
    // private:
    //     uint16_t m_X;
    // };

    // struct UInt32
    // {
    // public:
    //     explicit constexpr UInt32(uint32_t x = 0)
    //             : m_X(x)
    //     {}
    //     explicit operator uint32_t() const { return m_X; }

    //     UInt32 operator+(UInt32 x) const { return UInt32(m_X + x.m_X); }
    //     UInt32& operator+=(UInt32 x) { m_X += x.m_X; return *this; }

    //     UInt32 operator-(UInt32 x) const { return UInt32(m_X - x.m_X); }
    //     UInt32& operator-=(UInt32 x) { m_X -= x.m_X; return *this; }

    //     UInt32 operator*(UInt32 x) const { return UInt32(m_X * x.m_X); }
    //     UInt32& operator*=(UInt32 x) { m_X *= x.m_X; return *this; }

    //     UInt32 operator/(UInt32 x) const { return UInt32(m_X / x.m_X); }
    //     UInt32& operator/=(UInt32 x) { m_X /= x.m_X; return *this; }

    //     bool8_t operator==(uint32_t x) const { return m_X == x; }
    //     bool8_t operator==(UInt32 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(uint32_t x) const { return m_X != x; }
    //     bool8_t operator!=(UInt32 x) const { return m_X != x.m_X; }
    // private:
    //     uint32_t m_X;
    // };

    // struct UInt64
    // {
    // public:
    //     explicit constexpr UInt64(uint64_t x = 0)
    //          : m_X(x)
    //     {}
    //     UInt64(const UInt64&) = default;
    //     UInt64(UInt64&&) = default;
    //     explicit operator uint64_t() const { return m_X; }

    //     UInt64 operator+(UInt64 x) const { return UInt64(m_X + x.m_X); }
    //     UInt64& operator+=(UInt64 x) { m_X += x.m_X; return *this; }

    //     UInt64 operator-(UInt64 x) const { return UInt64(m_X - x.m_X); }
    //     UInt64& operator-=(UInt64 x) { m_X -= x.m_X; return *this; }

    //     UInt64 operator*(UInt64 x) const { return UInt64(m_X * x.m_X); }
    //     UInt64& operator*=(UInt64 x) { m_X *= x.m_X; return *this; }

    //     UInt64 operator/(UInt64 x) const { return UInt64(m_X / x.m_X); }
    //     UInt64& operator/=(UInt64 x) { m_X /= x.m_X; return *this; }

    //     bool8_t operator==(uint64_t x) const { return m_X == x; }
    //     bool8_t operator==(UInt64 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(uint64_t x) const { return m_X != x; }
    //     bool8_t operator!=(UInt64 x) const { return m_X != x.m_X; }
    // private:
    //     uint64_t m_X;
    // };

    // struct Int8
    // {
    // public:
    //     explicit constexpr Int8(int8_t x = 0)
    //          : m_X(x)
    //     {}
    //     explicit operator int8_t() const { return m_X; }

    //     Int8 operator+(Int8 x) const { return Int8(static_cast<int8_t>(m_X + x.m_X)); }
    //     Int8& operator+=(Int8 x) { m_X = static_cast<int8_t>(m_X + x.m_X); return *this; }

    //     Int8 operator-(Int8 x) const { return Int8(static_cast<int8_t>(m_X - x.m_X)); }
    //     Int8& operator-=(Int8 x) { m_X = static_cast<int8_t>(m_X - x.m_X); return *this; }

    //     Int8 operator*(Int8 x) const { return Int8(static_cast<int8_t>(m_X * x.m_X)); }
    //     Int8& operator*=(Int8 x) { m_X = static_cast<int8_t>(m_X * x.m_X); return *this; }

    //     Int8 operator/(Int8 x) const { return Int8(static_cast<int8_t>(m_X / x.m_X)); }
    //     Int8& operator/=(Int8 x) { m_X = static_cast<int8_t>(m_X / x.m_X); return *this; }

    //     bool8_t operator==(int8_t x) const { return m_X == x; }
    //     bool8_t operator==(Int8 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(int8_t x) const { return m_X != x; }
    //     bool8_t operator!=(Int8 x) const { return m_X != x.m_X; }
    // private:
    //     int8_t m_X;
    // };

    // struct Int16
    // {
    // public:
    //     explicit constexpr Int16(int16_t x = 0)
    //          : m_X(x)
    //     {}
    //     explicit operator int16_t() const { return m_X; }

    //     Int16 operator+(Int16 x) const { return Int16(static_cast<int16_t>(m_X + x.m_X)); }
    //     Int16& operator+=(Int16 x) { m_X = static_cast<int16_t>(m_X + x.m_X); return *this; }

    //     Int16 operator-(Int16 x) const { return Int16(static_cast<int16_t>(m_X - x.m_X)); }
    //     Int16& operator-=(Int16 x) { m_X = static_cast<int16_t>(m_X - x.m_X); return *this; }

    //     Int16 operator*(Int16 x) const { return Int16(static_cast<int16_t>(m_X * x.m_X)); }
    //     Int16& operator*=(Int16 x) { m_X = static_cast<int16_t>(m_X * x.m_X); return *this; }

    //     Int16 operator/(Int16 x) const { return Int16(static_cast<int16_t>(m_X / x.m_X)); }
    //     Int16& operator/=(Int16 x) { m_X = static_cast<int16_t>(m_X / x.m_X); return *this; }

    //     bool8_t operator==(int16_t x) const { return m_X == x; }
    //     bool8_t operator==(Int16 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(int16_t x) const { return m_X != x; }
    //     bool8_t operator!=(Int16 x) const { return m_X != x.m_X; }
    // private:
    //     int16_t m_X;
    // };

    // struct Int32
    // {
    // public:
    //     explicit constexpr Int32(int32_t x = 0)
    //             : m_X(x)
    //     {}
    //     explicit operator int32_t() const { return m_X; }

    //     Int32 operator+(Int32 x) const { return Int32(m_X + x.m_X); }
    //     Int32& operator+=(Int32 x) { m_X += x.m_X; return *this; }

    //     Int32 operator-(Int32 x) const { return Int32(m_X - x.m_X); }
    //     Int32& operator-=(Int32 x) { m_X -= x.m_X; return *this; }

    //     Int32 operator*(Int32 x) const { return Int32(m_X * x.m_X); }
    //     Int32& operator*=(Int32 x) { m_X *= x.m_X; return *this; }

    //     Int32 operator/(Int32 x) const { return Int32(m_X / x.m_X); }
    //     Int32& operator/=(Int32 x) { m_X /= x.m_X; return *this; }

    //     bool8_t operator==(int32_t x) const { return m_X == x; }
    //     bool8_t operator==(Int32 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(int32_t x) const { return m_X != x; }
    //     bool8_t operator!=(Int32 x) const { return m_X != x.m_X; }
    // private:
    //     int32_t m_X;
    // };

    // struct Int64
    // {
    // public:
    //     explicit constexpr Int64(int64_t x = 0)
    //          : m_X(x)
    //     {}
    //     explicit operator int64_t() const { return m_X; }

    //     Int64 operator+(Int64 x) const { return Int64(m_X + x.m_X); }
    //     Int64& operator+=(Int64 x) { m_X += x.m_X; return *this; }

    //     Int64 operator-(Int64 x) const { return Int64(m_X - x.m_X); }
    //     Int64& operator-=(Int64 x) { m_X -= x.m_X; return *this; }

    //     Int64 operator*(Int64 x) const { return Int64(m_X * x.m_X); }
    //     Int64& operator*=(Int64 x) { m_X *= x.m_X; return *this; }

    //     Int64 operator/(Int64 x) const { return Int64(m_X / x.m_X); }
    //     Int64& operator/=(Int64 x) { m_X /= x.m_X; return *this; }

    //     bool8_t operator==(int64_t x) const { return m_X == x; }
    //     bool8_t operator==(Int64 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(int64_t x) const { return m_X != x; }
    //     bool8_t operator!=(Int64 x) const { return m_X != x.m_X; }
    // private:
    //     int64_t m_X;
    // };

    // struct Float32
    // {
    // public:
    //     explicit constexpr Float32(float32_t x = 0.0f)
    //         : m_X(x)
    //     {}
    //     explicit operator float32_t() const { return m_X; }

    //     Float32 operator+(Float32 x) const { return Float32(m_X + x.m_X); }
    //     Float32& operator+=(Float32 x) { m_X += x.m_X; return *this; }

    //     Float32 operator-(Float32 x) const { return Float32(m_X - x.m_X); }
    //     Float32& operator-=(Float32 x) { m_X -= x.m_X; return *this; }

    //     Float32 operator*(Float32 x) const { return Float32(m_X * x.m_X); }
    //     Float32& operator*=(Float32 x) { m_X *= x.m_X; return *this; }

    //     Float32 operator/(Float32 x) const { return Float32(m_X / x.m_X); }
    //     Float32& operator/=(Float32 x) { m_X /= x.m_X; return *this; }

    //     bool8_t operator==(float32_t x) const { return m_X == x; }
    //     bool8_t operator==(Float32 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(float32_t x) const { return m_X != x; }
    //     bool8_t operator!=(Float32 x) const { return m_X != x.m_X; }
    // private:
    //     float32_t m_X;
    // };

    // struct Float64
    // {
    // public:
    //     explicit constexpr Float64(float64_t x = 0.0)
    //          : m_X(x)
    //     {}
    //     explicit operator float64_t() const { return m_X; }

    //     Float64 operator+(Float64 x) const { return Float64(m_X + x.m_X); }
    //     Float64& operator+=(Float64 x) { m_X += x.m_X; return *this; }

    //     Float64 operator-(Float64 x) const { return Float64(m_X - x.m_X); }
    //     Float64& operator-=(Float64 x) { m_X -= x.m_X; return *this; }

    //     Float64 operator*(Float64 x) const { return Float64(m_X * x.m_X); }
    //     Float64& operator*=(Float64 x) { m_X *= x.m_X; return *this; }

    //     Float64 operator/(Float64 x) const { return Float64(m_X / x.m_X); }
    //     Float64& operator/=(Float64 x) { m_X /= x.m_X; return *this; }

    //     bool8_t operator==(float64_t x) const { return m_X == x; }
    //     bool8_t operator==(Float64 x) const { return m_X == x.m_X; }
    //     bool8_t operator!=(float64_t x) const { return m_X != x; }
    //     bool8_t operator!=(Float64 x) const { return m_X != x.m_X; }
    // private:
    //     float64_t m_X;
    // };

    // struct Bool8
    // {
    // public:
    //     explicit constexpr Bool8(bool8_t b = false)
    //         : m_B(b)
    //     {}
    //     explicit operator bool8_t () const { return m_B; }

    //     Bool8 operator=(bool8_t x) const { return Bool8(x); }
    //     bool8_t operator==(bool8_t x) const { return m_B == x; }
    //     bool8_t operator==(Bool8 x) const { return m_B == x.m_B; }
    //     bool8_t operator!=(bool8_t x) const { return m_B != x; }
    //     bool8_t operator!=(Bool8 x) const { return m_B != x.m_B; }
    // private:
    //     bool8_t m_B;
    // };

    /**
     * @brief Static assertions to check the size of types.
     */
    static_assert(sizeof(UInt8 ) == 1, "Expected UInt16 to be 1 byte.");
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

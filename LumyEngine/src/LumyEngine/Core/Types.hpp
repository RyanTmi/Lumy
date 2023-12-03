/**
 * @file Types.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Definition of fundamental types for the game engine.
 * @version 0.1
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
    using u8  = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using u64 = unsigned long;

    /**
     * @brief Alias for signed integer types.
     */
    using i8  = char;
    using i16 = short;
    using i32 = int;
    using i64 = long;

    /**
     * @brief Alias for floating-point types.
     */
    using f32 = float;
    using f64 = double;

    /**
     * @brief Alias for boolean types.
     */
    using b8 = bool;

    /**
     * @brief Static assertions to check the size of types.
     */
    static_assert(sizeof(u8 ) == 1, "Expected u8 to be 1 byte.");
    static_assert(sizeof(u16) == 2, "Expected u16 to be 2 byte.");
    static_assert(sizeof(u32) == 4, "Expected u32 to be 4 byte.");
    static_assert(sizeof(u64) == 8, "Expected u64 to be 8 byte.");

    static_assert(sizeof(i8 ) == 1, "Expected i8 to be 1 byte.");
    static_assert(sizeof(i16) == 2, "Expected i16 to be 2 byte.");
    static_assert(sizeof(i32) == 4, "Expected i32 to be 4 byte.");
    static_assert(sizeof(i64) == 8, "Expected i64 to be 8 byte.");

    static_assert(sizeof(f32) == 4, "Expected f32 to be 4 byte.");
    static_assert(sizeof(f64) == 8, "Expected f64 to be 8 byte.");

    static_assert(sizeof(b8 ) == 1, "Expected b8 to be 1 byte.");

    /**
     * @brief Macro to define bits.
     */
    #define BIT(x) (1UL << (x))
}

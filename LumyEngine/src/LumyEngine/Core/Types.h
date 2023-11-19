/**
 * @file Types.h
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief Definition of fundamental types for the game engine.
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

/**
 * @brief Alias for unsigned integer types.
 */
using lm_u8   = unsigned char;
using lm_u16  = unsigned short;
using lm_u32  = unsigned int;
using lm_u64  = unsigned long;

/**
 * @brief Alias for signed integer types.
 */
using lm_i8   = char;
using lm_i16  = short;
using lm_i32  = int;
using lm_i64  = long;


/**
 * @brief Alias for floating-point types.
 */
using lm_f32  = float;
using lm_f64  = double;

/**
 * @brief Alias for size types.
 */
using lm_size  = lm_u64;
using lm_ssize = lm_i64;

/**
 * @brief Macro for performing a static assertion.
 */
#define STATIC_ASSERT static_assert

/**
 * @brief Static assertions to check the size of types.
 */
STATIC_ASSERT(sizeof(lm_u8) == 1, "Expected lm_u8 to be 1 byte.");
STATIC_ASSERT(sizeof(lm_u16) == 2, "Expected lm_u16 to be 2 byte.");
STATIC_ASSERT(sizeof(lm_u32) == 4, "Expected lm_u32 to be 4 byte.");
STATIC_ASSERT(sizeof(lm_u64) == 8, "Expected lm_u64 to be 8 byte.");

STATIC_ASSERT(sizeof(lm_i8) == 1, "Expected lm_i8 to be 1 byte.");
STATIC_ASSERT(sizeof(lm_i16) == 2, "Expected lm_i16 to be 2 byte.");
STATIC_ASSERT(sizeof(lm_i32) == 4, "Expected lm_i32 to be 4 byte.");
STATIC_ASSERT(sizeof(lm_i64) == 8, "Expected lm_i64 to be 8 byte.");

STATIC_ASSERT(sizeof(lm_f32) == 4, "Expected lm_f32 to be 4 byte.");
STATIC_ASSERT(sizeof(lm_f64) == 8, "Expected lm_f64 to be 8 byte.");

/**
 * @brief Macro to define bits.
 */
#define BIT(x) (1ULL << x)

/**
 * @brief Constants for the maximum and minimum values of integer types.
 */
#define LM_U8_MAX    ((1U << (sizeof(lm_u8) * 8)) - 1)
#define LM_U16_MAX   ((1U << (sizeof(lm_u16) * 8)) - 1)
#define LM_U32_MAX   ((1U << (sizeof(lm_u32) * 8)) - 1)
#define LM_U64_MAX   ((1ULL << (sizeof(lm_u64) * 8)) - 1)

#define LM_I8_MIN    (-(1 << ((sizeof(lm_i8) * 8) - 1)))
#define LM_I16_MIN   (-(1 << ((sizeof(lm_i16) * 8) - 1)))
#define LM_I32_MIN   (-(1U << ((sizeof(lm_i32) * 8) - 1)))
#define LM_I64_MIN   (-(1ULL << ((sizeof(lm_i64) * 8) - 1)))

#define LM_I8_MAX    ((1 << ((sizeof(lm_i8) * 8) - 1)) - 1)
#define LM_I16_MAX   ((1 << ((sizeof(lm_i16) * 8) - 1)) - 1)
#define LM_I32_MAX   ((1U << ((sizeof(lm_i32) * 8) - 1)) - 1)
#define LM_I64_MAX   ((1ULL << ((sizeof(lm_i64) * 8) - 1)) - 1)

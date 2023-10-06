#pragma once

using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;

using int8   = char;
using int16  = short;
using int32  = int;
using int64  = long;

using float32 = float;
using float64 = double;

#if defined(__clang__) || defined(__GNUC__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

STATIC_ASSERT(sizeof(uint8) == 1, "Expected uint8 to be 1 byte.");
STATIC_ASSERT(sizeof(uint16) == 2, "Expected uint16 to be 2 byte.");
STATIC_ASSERT(sizeof(uint32) == 4, "Expected uint32 to be 4 byte.");
STATIC_ASSERT(sizeof(uint64) == 8, "Expected uint64 to be 8 byte.");


#define UINT8_MAX    255
#define UINT16_MAX   65535
#define UINT32_MAX   4294967295U
#define UINT64_MAX   18446744073709551615ULL


#define INT8_MIN     (-128)
#define INT16_MIN    (-32768)
#define INT32_MIN    (-2147483648)
#define INT64_MIN    (-9223372036854775808LL)

#define INT8_MAX     127
#define INT16_MAX    32767
#define INT32_MAX    2147483647
#define INT64_MAX    9223372036854775807LL

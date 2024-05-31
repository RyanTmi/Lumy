#pragma once

namespace Lumy
{
    using UInt8  = unsigned char;
    using UInt16 = unsigned short;
    using UInt32 = unsigned int;
    using UInt64 = unsigned long long;

    using Int8  = signed char;
    using Int16 = short;
    using Int32 = int;
    using Int64 = long long;

    using USize = unsigned long long;
    using Size  = long long;

    using Float32 = float;
    using Float64 = double;


    static_assert(sizeof(UInt8) == 1, "Size of UInt8 should be 1 byte");
    static_assert(sizeof(UInt16) == 2, "Size of UInt16 should be 2 bytes");
    static_assert(sizeof(UInt32) == 4, "Size of UInt32 should be 4 bytes");
    static_assert(sizeof(UInt64) == 8, "Size of UInt64 should be 8 bytes");

    static_assert(sizeof(Int8) == 1, "Size of Int8 should be 1 byte");
    static_assert(sizeof(Int16) == 2, "Size of Int16 should be 2 bytes");
    static_assert(sizeof(Int32) == 4, "Size of Int32 should be 4 bytes");
    static_assert(sizeof(Int64) == 8, "Size of Int64 should be 8 bytes");

    static_assert(sizeof(USize) == 8, "Size of USize should be 8 bytes");
    static_assert(sizeof(Size) == 8, "Size of Size should be 8 bytes");

    static_assert(sizeof(Float32) == 4, "Size of Float32 should be 4 bytes");
    static_assert(sizeof(Float64) == 8, "Size of Float64 should be 8 bytes");
}

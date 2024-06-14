#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Math/Vector4.hpp"

namespace Lumy
{
    //==================================================================================================================
    // Struct : Color
    //==================================================================================================================

    struct Color final
    {
    public:
        static const Color Black;
        static const Color Blue;
        static const Color Orange;
        static const Color Gray;
        static const Color Green;
        static const Color Purple;
        static const Color Red;
        static const Color Yellow;
        static const Color White;

    public:
        static constexpr auto Lerp(Color lhs, Color rhs, Float32 t) noexcept -> Color;

    public:
        Float32 R = 0.0f;
        Float32 G = 0.0f;
        Float32 B = 0.0f;
        Float32 A = 1.0f;

    public:
        constexpr Color() noexcept;

        constexpr Color(Float32 r, Float32 g, Float32 b, Float32 a) noexcept;

        constexpr Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a) noexcept;

        constexpr Color(const Vector4& color) noexcept;
    };
}

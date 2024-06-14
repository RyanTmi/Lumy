#include "Color.hpp"

namespace Lumy
{
    const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
    const Color Color::Orange = Color(1.0f, 0.5f, 0.0f, 1.0f);
    const Color Color::Gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
    const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
    const Color Color::Purple = Color(0.6f, 0.125f, 0.95f, 1.0f);
    const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
    const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);

    constexpr auto Color::Lerp(Color lhs, Color rhs, Float32 t) noexcept -> Color
    {
        Float32 r = t * lhs.R + (1 - t) * rhs.R;
        Float32 g = t * lhs.G + (1 - t) * rhs.G;
        Float32 b = t * lhs.B + (1 - t) * rhs.B;
        Float32 a = t * lhs.A + (1 - t) * rhs.A;
        return {r, g, b, a};
    }

    constexpr Color::Color() noexcept
        : R(0.0f), G(0.0f), B(0.0f), A(1.0f)
    {}

    constexpr Color::Color(Float32 r, Float32 g, Float32 b, Float32 a) noexcept
        : R(r), G(g), B(b), A(a)
    {}

    constexpr Color::Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a) noexcept
        : R(r / 255.0f), G(g / 255.0f), B(b / 255.0f), A(a / 255.0f)
    {}

    constexpr Color::Color(const Vector4& color) noexcept
        : R(color[0]), G(color[1]), B(color[2]), A(color[3])
    {}
}

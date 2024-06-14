#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Math/Traits.hpp"

namespace Lumy::Math
{
    template <FloatingPoint F>
    class Quaternion
    {
    public:
        using Float = F;

    public:
        constexpr Quaternion() noexcept;
        constexpr Quaternion(Float x, Float y, Float z, Float w) noexcept;

    private:
        Float m_X;
        Float m_Y;
        Float m_Z;
        Float m_W;
    };

    template <FloatingPoint F>
    inline constexpr Quaternion<F>::Quaternion() noexcept
        : m_X(0.0f), m_Y(0.0f), m_Z(0.0f), m_W(1.0f)
    {}

    template <FloatingPoint F>
    inline constexpr Quaternion<F>::Quaternion(Float x, Float y, Float z, Float w) noexcept
        : m_X(x), m_Y(y), m_Z(z), m_W(w)
    {}

}

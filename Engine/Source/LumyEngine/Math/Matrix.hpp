#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Math/Traits.hpp"

#include <mdspan>

namespace Lumy::Math
{
    template <Numeric T, Size R, Size C>
    class Matrix
    {
    public:
        Matrix()
            : m_Data()
        {
            m_Data.fill(T(0));
        }

    private:
        std::array<T, R * C> m_Data;
    };
}

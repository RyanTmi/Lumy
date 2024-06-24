#pragma once

#include "Vector.hpp"

namespace Lumy
{
    template <Numeric T>
    using Vector4 = Vector<T, 4>;

    using Vector4d = Vector4<Float64>;
    using Vector4f = Vector4<Float32>;
    using Vector4i = Vector4<Int32>;
    using Vector4b = Vector4<bool>;
}

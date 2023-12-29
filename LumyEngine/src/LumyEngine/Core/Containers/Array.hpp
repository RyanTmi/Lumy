#pragma once

#include "LumyEngine/Core/Types.hpp"

#include <array>

namespace Lumy
{
    template <typename T, UInt64 N>
    using Array = std::array<T, N>;
}

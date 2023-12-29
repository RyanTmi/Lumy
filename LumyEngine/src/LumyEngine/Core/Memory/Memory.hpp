#pragma once

#include <memory>

namespace Lumy
{
    template <typename T>
    using UniquePtr = std::unique_ptr<T>;

    template <typename T>
    using SharedRef = std::shared_ptr<T>;
}

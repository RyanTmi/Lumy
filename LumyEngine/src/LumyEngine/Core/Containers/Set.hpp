#pragma once

#include <set>
#include <unordered_set>

namespace Lumy
{
    template <typename T>
    using Set = std::set<T>;

    template <typename T>
    using UnorderedSet = std::unordered_set<T>;
}

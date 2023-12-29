#pragma once

#include <map>
#include <unordered_map>

namespace Lumy
{
    template <typename K, typename V>
    using Map = std::map<K, V>;

    template <typename K, typename V>
    using UnorderedMap = std::unordered_map<K, V>;
}

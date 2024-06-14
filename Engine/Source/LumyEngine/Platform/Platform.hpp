#pragma once

#include "LumyEngine/Core/Types.hpp"

// TODO: Do not expose all vector class
#include <vector>

namespace Lumy
{
    class Platform final
    {
    public:
        Platform() = delete;
        ~Platform() = delete;

    public:
        static auto Initialize() -> bool;
        static auto Shutdown() -> void;
        static auto PollEvents() -> bool;

        static auto ProcessorCount() -> UInt8;

        // NOTE: Used for Vulkan
        static auto GetRequiredExtensionNames(std::vector<const char*>& names) -> void;
    };
}

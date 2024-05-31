#pragma once

#include "LumyEngine/Core/Types.hpp"

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
    };
}

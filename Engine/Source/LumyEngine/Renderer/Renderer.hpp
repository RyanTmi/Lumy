#pragma once

#include "LumyEngine/Core/Types.hpp"

namespace Lumy
{
    class Renderer final
    {
    public:
        static auto Initialize() -> bool;

        static auto Shutdown() -> void;

        static auto DrawFrame() -> bool;

        static auto OnResize(UInt16 width, UInt16 height) -> void;

    private:
        static auto BeginFrame() -> bool;
        static auto EndFrame() -> bool;
    };
}

#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

namespace Lumy
{
    class MetalContext final
    {
    public:
        MetalContext() = default;

    private:
        MTL::Device* m_Device;
    };
}

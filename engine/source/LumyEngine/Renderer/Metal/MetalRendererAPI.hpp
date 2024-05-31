#pragma once

#include "LumyEngine/Renderer/RendererAPI.hpp"
#include "LumyEngine/Renderer/Metal/MetalContext.hpp"

namespace Lumy
{
    class MetalRendererAPI : public RendererAPI
    {
    public:
        MetalRendererAPI() = default;
        ~MetalRendererAPI() override = default;

    private:
        MetalContext m_Context;
    };
}

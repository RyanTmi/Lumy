#pragma once

#include "LumyEngine/Renderer/Metal/MetalDevice.hpp"
#include "LumyEngine/Renderer/Metal/MetalShader.hpp"

#include <Metal/Metal.hpp>

namespace Lumy
{
    class MetalGraphicsPipeline final
    {
    public:
        MetalGraphicsPipeline() = default;
        ~MetalGraphicsPipeline();

    public:
        auto Create(MetalDevice& device, MetalShader& shader, MTL::PixelFormat pixelFormat) -> bool;
        auto Destroy() -> void;

        auto Bind(MTL::RenderCommandEncoder* renderCommandEncoder) -> void;

    private:
        MTL::RenderPipelineDescriptor* m_RenderPipelineDescriptor;
        MTL::RenderPipelineState* m_RenderPipelineState;
    };
}

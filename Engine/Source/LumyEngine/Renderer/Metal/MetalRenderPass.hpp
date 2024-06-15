#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Renderer/Metal/MetalDevice.hpp"
#include "LumyEngine/Renderer/Color.hpp"

#include <Metal/MTLCommandBuffer.hpp>
#include <Metal/MTLRenderCommandEncoder.hpp>
#include <Metal/MTLRenderPass.hpp>

#include <QuartzCore/CAMetalDrawable.hpp>

namespace Lumy
{
    class MetalRenderPass final
    {
    public:
        MetalRenderPass() = default;

    public:
        auto Create(MetalDevice* device, Color clearColor) -> void;
        auto Destroy() -> void;

        auto Begin(CA::MetalDrawable* drawable) -> void;
        auto End() -> void;

        auto RenderCommandEncoder() -> MTL::RenderCommandEncoder* { return m_CommandEncoder; }

    private:
        MetalDevice* m_Device;
        MTL::CommandBuffer* m_CommandBuffer;

        CA::MetalDrawable* m_CurrentDrawable;
        MTL::RenderPassDescriptor* m_Descriptor;
        MTL::RenderCommandEncoder* m_CommandEncoder;
    };
}

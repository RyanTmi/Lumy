#pragma once

#include "LumyEngine/Renderer/Metal/MetalDevice.hpp"
#include "LumyEngine/Renderer/Metal/MetalRenderPass.hpp"

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalDrawable.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

namespace Lumy
{
    class MetalContext final
    {
    public:
        MetalContext() = default;

    public:
        auto Initialize() -> bool;
        auto Shutdown() -> void;

        auto Resize(UInt32 width, UInt32 height) -> void;

    public:
        auto NextDrawable() -> bool;

        auto CurrentDrawable() -> CA::MetalDrawable* { return m_Drawable; }

        auto RenderPass() -> MetalRenderPass& { return m_MainRenderPass; }

    private:
        MetalDevice m_Device;
        MetalRenderPass m_MainRenderPass;

        CA::MetalLayer* m_Layer;
        CA::MetalDrawable* m_Drawable;

        // MTL::Library* m_ShaderLibrary;
        // MTL::RenderPipelineState* m_RenderPipelineState;

        // MTL::Buffer* m_VertexBuffer;
        // MTL::Buffer* m_IndexBuffer;
    };
}

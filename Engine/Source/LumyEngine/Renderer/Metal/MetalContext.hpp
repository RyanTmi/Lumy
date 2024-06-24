#pragma once

#include "LumyEngine/Math/Math.hpp"
#include "LumyEngine/Renderer/Metal/MetalDevice.hpp"
#include "LumyEngine/Renderer/Metal/MetalRenderPass.hpp"
#include "LumyEngine/Renderer/Metal/MetalPipeline.hpp"
#include "LumyEngine/Renderer/Metal/MetalShader.hpp"

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

        auto FrameBufferSize() const -> Vector2f;

    public:
        auto NextDrawable() -> bool;

        auto CurrentDrawable() -> CA::MetalDrawable* { return m_Drawable; }

        auto RenderPass() -> MetalRenderPass& { return m_MainRenderPass; }

        auto GraphicsPipeline() -> MetalGraphicsPipeline& { return m_GraphicsPipeline; }

        auto VertexBuffer() -> MTL::Buffer* { return m_VertexBuffer; }

        auto ColorBuffer() -> MTL::Buffer* { return m_VertexColorBuffer; }

        auto IndexBuffer() -> MTL::Buffer* { return m_IndexBuffer; }

        auto UniformsBuffer() -> MTL::Buffer* { return m_UniformsBuffer; }

        auto UpdateUniforms(const Matrix4x4f& projection, const Matrix4x4f& view) -> void;

    private:
        MetalDevice m_Device {};
        MetalRenderPass m_MainRenderPass {};

        CA::MetalLayer* m_Layer {};
        CA::MetalDrawable* m_Drawable {};

        MTL::Library* m_Library {};
        MetalGraphicsPipeline m_GraphicsPipeline {};
        MetalShader m_Shader {};

        MTL::Buffer* m_VertexBuffer {};
        MTL::Buffer* m_VertexColorBuffer {};
        MTL::Buffer* m_IndexBuffer {};

        MTL::Buffer* m_UniformsBuffer {};
        Matrix4x4f m_ViewProjection;
    };
}

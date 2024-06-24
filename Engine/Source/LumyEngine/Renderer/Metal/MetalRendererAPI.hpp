#pragma once

#include "LumyEngine/Renderer/RendererAPI.hpp"
#include "LumyEngine/Renderer/Metal/MetalContext.hpp"

// #include "LumyEngine/Math/Math.hpp"

namespace Lumy
{
    class MetalRendererAPI final : public RendererAPI
    {
    public:
        MetalRendererAPI() = default;
        ~MetalRendererAPI() override = default;

    public:
        auto Initialize() -> bool override;

        auto Shutdown() -> void override;

        auto BeginFrame() -> bool override;
        auto EndFrame() -> bool override;

        auto UpdateUniforms(const Matrix4x4f& projection, const Matrix4x4f& view) -> void override;

        auto OnResize(UInt16 width, UInt16 height) -> void override;

    private:
        MetalContext m_Context;
    };
}

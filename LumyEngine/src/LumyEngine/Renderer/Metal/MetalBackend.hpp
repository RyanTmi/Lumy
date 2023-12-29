#pragma once

#include "LumyEngine/Renderer/RendererBackend.hpp"

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

namespace Lumy
{
    class MetalBackend : public RendererBackend
    {
    public:
        void Initialize() override;
        void Update() override;

        void Shutdown() override;
        void Render() override;

        void Draw(MTK::View* view);
    public:
        MTL::Device* GetDevice() const;
        MTL::CommandQueue* GetCommandQueue() const;
    private:
        void BuildShaders();
    private:
        MTL::Device* m_Device;
        MTL::CommandQueue* m_CommandQueue;
        MTL::RenderPipelineState* m_RenderPipelineState;
    };
}

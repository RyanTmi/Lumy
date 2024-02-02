#pragma once

#include "LumyEngine/Renderer/RendererBackend.hpp"

#include "MetalDevice.hpp"

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

namespace Lumy
{
    class MetalBackend : public RendererBackend
    {
    public:
        void Initialize() override;
        void Update() override;

        void Shutdown() override;
        void Render() override;
    public:
        MTL::Device* GetDevice() const;
        MTL::CommandQueue* GetCommandQueue() const;
        void SetLayer(CA::MetalLayer* layer);
    private:
        void Draw();
        void BuildShaders();
    private:
        MetalDevice m_MetalDevice;
        CA::MetalLayer* m_Layer;
        MTL::Device* m_Device;
        MTL::CommandQueue* m_CommandQueue;
        MTL::RenderPipelineState* m_RenderPipelineState;
    };
}

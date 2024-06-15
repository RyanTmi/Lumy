#include "MetalRenderPass.hpp"

namespace Lumy
{
    auto MetalRenderPass::Create(MetalDevice* device, Color clearColor) -> void
    {
        m_Device = device;
        m_Descriptor = MTL::RenderPassDescriptor::renderPassDescriptor();
        auto colorAttachment = m_Descriptor->colorAttachments()->object(0);
        colorAttachment->setLoadAction(MTL::LoadActionClear);
        colorAttachment->setClearColor(MTL::ClearColor(clearColor.R, clearColor.G, clearColor.B, clearColor.A));
        colorAttachment->setStoreAction(MTL::StoreActionStore);
    }

    auto MetalRenderPass::Destroy() -> void
    {
        m_Descriptor->release();
        m_CommandEncoder->release();
    }

    auto MetalRenderPass::Begin(CA::MetalDrawable* drawable) -> void
    {
        m_CurrentDrawable = drawable;
        m_CommandBuffer = m_Device->CommandQueue()->commandBuffer();
        m_CommandEncoder = m_CommandBuffer->renderCommandEncoder(m_Descriptor);
        m_Descriptor->colorAttachments()->object(0)->setTexture(drawable->texture());
    }

    auto MetalRenderPass::End() -> void
    {
        m_CommandEncoder->endEncoding();

        m_CommandBuffer->presentDrawable(m_CurrentDrawable);
        m_CommandBuffer->commit();
        m_CommandBuffer->waitUntilCompleted();
        m_CommandBuffer->release();
    }

}

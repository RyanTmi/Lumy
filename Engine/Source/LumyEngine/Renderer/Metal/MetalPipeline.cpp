#include "MetalPipeline.hpp"

#include "LumyEngine/Math/Vector3.hpp"
#include "LumyEngine/Renderer/Color.hpp"

namespace Lumy
{
    MetalGraphicsPipeline::~MetalGraphicsPipeline()
    {
        Destroy();
    }

    auto MetalGraphicsPipeline::Create(MetalDevice& device, MetalShader& shader, MTL::PixelFormat pixelFormat) -> bool
    {
        auto vertexDescriptor = MTL::VertexDescriptor::vertexDescriptor();
        if (!vertexDescriptor)
        {
            return false;
        }
        vertexDescriptor->attributes()->object(0)->setBufferIndex(0);
        vertexDescriptor->attributes()->object(0)->setFormat(MTL::VertexFormatFloat3);
        vertexDescriptor->attributes()->object(0)->setOffset(0);
        vertexDescriptor->attributes()->object(1)->setBufferIndex(1);
        vertexDescriptor->attributes()->object(1)->setFormat(MTL::VertexFormatFloat4);
        vertexDescriptor->attributes()->object(1)->setOffset(0);

        vertexDescriptor->layouts()->object(0)->setStepFunction(MTL::VertexStepFunctionPerVertex);
        vertexDescriptor->layouts()->object(0)->setStride(sizeof(Vector3f));
        vertexDescriptor->layouts()->object(1)->setStepFunction(MTL::VertexStepFunctionPerVertex);
        vertexDescriptor->layouts()->object(1)->setStride(sizeof(Color));

        m_RenderPipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
        if (!m_RenderPipelineDescriptor)
        {
            return false;
        }
        m_RenderPipelineDescriptor->setVertexDescriptor(vertexDescriptor);
        m_RenderPipelineDescriptor->setInputPrimitiveTopology(MTL::PrimitiveTopologyClassTriangle);

        m_RenderPipelineDescriptor->setVertexFunction(shader.VertexFunction());
        m_RenderPipelineDescriptor->setFragmentFunction(shader.FragmentFunction());

        m_RenderPipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(pixelFormat);
        vertexDescriptor->release();

        NS::Error* error;
        m_RenderPipelineState = device.Handle()->newRenderPipelineState(m_RenderPipelineDescriptor, &error);

        return true;
    }

    auto MetalGraphicsPipeline::Destroy() -> void
    {
        if (m_RenderPipelineState)
        {
            m_RenderPipelineState->release();
            m_RenderPipelineState = nullptr;
        }

        if (m_RenderPipelineDescriptor)
        {
            m_RenderPipelineDescriptor->release();
            m_RenderPipelineDescriptor = nullptr;
        }
    }

    auto MetalGraphicsPipeline::Bind(MTL::RenderCommandEncoder* renderCommandEncoder) -> void
    {
        renderCommandEncoder->setRenderPipelineState(m_RenderPipelineState);
    }
}

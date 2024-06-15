#include "LumyEngine/Renderer/Metal/MetalRendererAPI.hpp"

#include "LumyEngine/Debug/Log.hpp"

namespace Lumy
{
    auto MetalRendererAPI::Initialize() -> bool
    {
        if (!m_Context.Initialize())
        {
            return false;
        }

        return true;
    }

    auto MetalRendererAPI::Shutdown() -> void
    {
        m_Context.Shutdown();
    }

    auto MetalRendererAPI::BeginFrame() -> bool
    {
        m_Context.NextDrawable();

        m_Context.RenderPass().Begin(m_Context.CurrentDrawable());

        auto renderCommandEncoder = m_Context.RenderPass().RenderCommandEncoder();
        m_Context.GraphicsPipeline().Bind(renderCommandEncoder);

        renderCommandEncoder->setVertexBuffer(m_Context.VertexBuffer(), 0, 0);
        renderCommandEncoder->setVertexBuffer(m_Context.ColorBuffer(), 0, 1);
        renderCommandEncoder
            ->drawIndexedPrimitives(MTL::PrimitiveTypeTriangle, 6, MTL::IndexTypeUInt16, m_Context.IndexBuffer(), 0);

        return true;
    }

    auto MetalRendererAPI::EndFrame() -> bool
    {
        m_Context.RenderPass().End();

        return true;
    }

    auto MetalRendererAPI::OnResize(UInt16 width, UInt16 height) -> void
    {
        m_Context.Resize(width, height);
    }
}
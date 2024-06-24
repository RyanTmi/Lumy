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
        renderCommandEncoder->setVertexBuffer(m_Context.UniformsBuffer(), 0, 10);
        renderCommandEncoder
            ->drawIndexedPrimitives(MTL::PrimitiveTypeTriangle, 6, MTL::IndexTypeUInt16, m_Context.IndexBuffer(), 0);

        return true;
    }

    auto MetalRendererAPI::EndFrame() -> bool
    {
        m_Context.RenderPass().End();

        return true;
    }

    auto MetalRendererAPI::UpdateUniforms(const Matrix4x4f& projection, const Matrix4x4f& view) -> void
    {
        m_Context.UpdateUniforms(projection, view);
    }

    auto MetalRendererAPI::OnResize(UInt16 width, UInt16 height) -> void
    {
        m_Context.Resize(width, height);

        // TODO: Temporary
        auto frameBufferSize = m_Context.FrameBufferSize();

        Matrix4x4f projection =
            Matrix4x4f::Perspective(DegToRad(90.0f), frameBufferSize.X / frameBufferSize.Y, 0.1, 100.0f);

        Matrix4x4f rotation = Matrix4x4f::Rotate(Quaternionf::AxisAngle(-30.0f, Vector3f::Up));
        Matrix4x4f transform = Matrix4x4f::Translate(Vector3f(0, 0, -1.0f)) * rotation;
        Matrix4x4f view = transform.Inverse();

        // Row Major -> Column Major for Metal API
        projection = projection.Transposed();
        view = view.Transposed();

        UpdateUniforms(projection, view);
        // TODO: End temporary
    }
}

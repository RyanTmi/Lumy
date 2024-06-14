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

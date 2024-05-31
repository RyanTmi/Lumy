#include "Renderer.hpp"

#include "RendererAPI.hpp"

namespace Lumy
{
    static RendererAPI* s_RendererAPI = nullptr;

    auto Renderer::Initialize() -> bool
    {
        // TODO: Make this configurable
        s_RendererAPI = RendererAPI::Create(RendererAPIType::Metal);
        return true;
    }

    auto Renderer::Shutdown() -> void
    {
        delete s_RendererAPI;
    }

    auto Renderer::DrawFrame() -> bool
    {

        return true;
    }

    auto Renderer::BeginFrame() -> bool
    {
        return true;
    }

    auto Renderer::EndFrame() -> bool
    {
        return true;
    }

    auto Renderer::OnResize(UInt16 width, UInt16 height) -> void {}
}

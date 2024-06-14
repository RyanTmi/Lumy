#include "LumyEngine/Renderer/Renderer.hpp"

#include "LumyEngine/Debug/Log.hpp"
#include "LumyEngine/Renderer/RendererAPI.hpp"

namespace Lumy
{
    static std::unique_ptr<RendererAPI> s_RendererAPI = nullptr;

    auto Renderer::Initialize() -> bool
    {
        if (s_RendererAPI)
        {
            s_RendererAPI->Shutdown();
            s_RendererAPI.reset();
        }

        // TODO: Make this configurable
        s_RendererAPI = RendererAPI::Create(RendererAPIType::Metal);
        if (!s_RendererAPI)
        {
            Log::Error("Renderer: Failed to create RendererAPI");
            return false;
        }

        if (!s_RendererAPI->Initialize())
        {
            Log::Error("Renderer: Failed to initialize RendererAPI");
            s_RendererAPI.reset();
            return false;
        }

        return true;
    }

    auto Renderer::Shutdown() -> void
    {
        if (s_RendererAPI)
        {
            s_RendererAPI->Shutdown();
            s_RendererAPI.reset();
        }
    }

    auto Renderer::DrawFrame() -> bool
    {
        if (BeginFrame())
        {
            // TODO: Render Scene

            if (!EndFrame())
            {
                Log::Error("Renderer: EndFrame failed");
                return false;
            }
        }

        return true;
    }

    auto Renderer::BeginFrame() -> bool
    {
        return s_RendererAPI->BeginFrame();
    }

    auto Renderer::EndFrame() -> bool
    {
        return s_RendererAPI->EndFrame();
    }

    auto Renderer::OnResize(UInt16 width, UInt16 height) -> void
    {
        s_RendererAPI->OnResize(width, height);
    }
}

#include "Renderer.hpp"

#include "RendererBackend.hpp"
#include "LumyEngine/Renderer/Metal/MetalBackend.hpp"

namespace Lumy
{
    Renderer& Renderer::Get()
    {
        static Renderer instance;
        return instance;
    }

    void Renderer::Initialize()
    {
        m_Backend = UniquePtr<RendererBackend>(RendererBackend::Create());
        m_Backend->Initialize();
    }

    void Renderer::Update()
    {

    }

    void Renderer::Shutdown()
    {
        m_Backend->Shutdown();
    }

    RendererBackend* Renderer::GetBackend() const
    {
        return m_Backend.get();
    }
}

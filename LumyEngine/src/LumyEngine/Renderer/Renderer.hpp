#pragma once

#include "LumyEngine/Core/Memory/Memory.hpp"

#include "LumyEngine/Core/Module.hpp"
#include "LumyEngine/Renderer/RendererBackend.hpp"

namespace Lumy
{
    class Renderer : public Module
    {
    public:
        static Renderer& Get();
    public:
        void Initialize() override;
        void Update() override;
        void Shutdown() override;
    public:
        RendererBackend* GetBackend() const;
    private:
        UniquePtr<RendererBackend> m_Backend;
    };
}

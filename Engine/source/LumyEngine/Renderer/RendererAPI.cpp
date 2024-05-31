#include "LumyEngine/Renderer/RendererAPI.hpp"

#include "LumyEngine/Debug/Logger.hpp"
#include "LumyEngine/Renderer/Metal/MetalRendererAPI.hpp"

namespace Lumy
{
    auto RendererAPI::Create(RendererAPIType type) -> RendererAPI*
    {
        switch (type)
        {
            case RendererAPIType::DirectX: Log::Error("Renderer: DirectX is not supported"); break;
            case RendererAPIType::Metal:   return new MetalRendererAPI();
            case RendererAPIType::Vulkan:  Log::Error("Renderer: Vulkan is not supported"); break;
        }

        return nullptr;
    }
}

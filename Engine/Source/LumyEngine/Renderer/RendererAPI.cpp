#include "LumyEngine/Renderer/RendererAPI.hpp"

#include "LumyEngine/Debug/Log.hpp"
#include "LumyEngine/Renderer/Metal/MetalRendererAPI.hpp"
#include "LumyEngine/Renderer/Vulkan/VulkanRendererAPI.hpp"

namespace Lumy
{
    auto RendererAPI::Create(RendererAPIType type) -> std::unique_ptr<RendererAPI>
    {
        switch (type)
        {
            using enum RendererAPIType;

            case None:    Log::Error("Renderer: Headless is not supported"); return nullptr;
            case DirectX: Log::Error("Renderer: DirectX is not supported"); return nullptr;
            case Metal:   return std::make_unique<MetalRendererAPI>();
            case Vulkan:  return std::make_unique<VulkanRendererAPI>();
        }

        Log::Error("Renderer: Unknown renderer API");
        return nullptr;
    }
}

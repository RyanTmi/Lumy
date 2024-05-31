#pragma once

namespace Lumy
{
    enum class RendererAPIType
    {
        DirectX,
        Metal,
        Vulkan,
    };

    class RendererAPI
    {
    public:
        static auto Create(RendererAPIType type) -> RendererAPI*;

    public:
        RendererAPI() = default;
        virtual ~RendererAPI() = default;
    };
}

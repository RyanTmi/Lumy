#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "LumyEngine/Math/Math.hpp"

#include <memory>

namespace Lumy
{
    enum class RendererAPIType
    {
        None = 0,  // TODO: Headless
        DirectX,
        Metal,
        Vulkan,
    };

    class RendererAPI
    {
    public:
        static auto Create(RendererAPIType type) -> std::unique_ptr<RendererAPI>;

    public:
        virtual ~RendererAPI() = default;

    public:
        virtual auto Initialize() -> bool = 0;
        virtual auto Shutdown() -> void = 0;

        virtual auto BeginFrame() -> bool = 0;
        virtual auto EndFrame() -> bool = 0;

        virtual auto UpdateUniforms(const Matrix4x4f& projection, const Matrix4x4f& view) -> void = 0;

        virtual auto OnResize(UInt16 width, UInt16 height) -> void = 0;
    };
}

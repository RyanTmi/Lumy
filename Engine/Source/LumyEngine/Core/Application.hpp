#pragma once

#include "LumyEngine/Platform/Platform.hpp"
#include "LumyEngine/Platform/Window.hpp"

#include <string_view>

namespace Lumy
{
    struct ApplicationSpecification final
    {
        std::string_view Name;
        WindowSpecification WindowSpec;

        ApplicationSpecification(std::string_view name, const WindowSpecification& windowSpec)
            : Name(name), WindowSpec(windowSpec)
        {}
    };

    class Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;

        virtual auto Initialize() -> bool = 0;
        virtual auto Shutdown() -> void = 0;
        virtual auto Update(Float64 deltaTime) -> bool = 0;
        virtual auto Render(Float64 deltaTime) -> bool = 0;

        virtual auto Specification() const -> const ApplicationSpecification& = 0;
    };

    extern Application* MakeApplication();
}

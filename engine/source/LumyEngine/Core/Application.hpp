#pragma once

#include "LumyEngine/Platform/Platform.hpp"
#include "LumyEngine/Platform/Window.hpp"

namespace Lumy
{
    struct ApplicationSpecification final
    {
        WindowSpecification WindowSpec;

        explicit ApplicationSpecification(const WindowSpecification& WindowSpec)
            : WindowSpec(WindowSpec)
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

#pragma once

#include "LumyEngine/Core/Application.hpp"
#include "LumyEngine/Core/Event/WindowEvent.hpp"
#include "LumyEngine/Platform/Platform.hpp"

int main(int argc, char** argv);

namespace Lumy
{
    class Window;
    
    class Engine final
    {
    public:
        static auto GetWindow() -> Window&;

    private:
        static auto Initialize(Application& application) -> bool;
        static auto Shutdown() -> void;
        static auto Run() -> void;

        static auto OnWindowClose(const WindowCloseEvent& e) -> bool;
        static auto OnWindowResize(const WindowResizeEvent& e) -> bool;

        friend int ::main(int argc, char** argv);
    };
}

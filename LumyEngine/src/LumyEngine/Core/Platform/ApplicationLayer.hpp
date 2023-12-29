#pragma once

#include "LumyEngine/Core/Module.hpp"
#include "LumyEngine/Core/Window.hpp"

namespace Lumy
{
    class ApplicationLayer : public Module
    {
    public:
        static ApplicationLayer& Get();
    public:
        virtual void CreateWindow(const WindowProperties& windowProperties) = 0;

        inline Window* GetWindow() { return m_Window.get(); }
    protected:
        UniquePtr<Window> m_Window;
    };
}

#pragma once

#include "Foundation.hpp"

#include "Events/EventManager.hpp"
#include "Events/WindowEvent.hpp"

#include "Window.hpp"

namespace Lumy
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        
    public:
        void Run();
    private:
        void OnWindowResize(const WindowResizeEvent& e);
        void OnWindowClose(const WindowCloseEvent& e);
    private:
        Bool8 m_Running;
        std::unique_ptr<Window> m_Window;
    };

    Application* CreateApplication();
}

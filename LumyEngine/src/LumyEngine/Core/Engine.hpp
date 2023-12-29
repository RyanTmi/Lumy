#pragma once

#include "Foundation.hpp"

namespace Lumy
{
    class LUMY_API Engine
    {
    public:
        static Engine& Create();
    public:
        void Initialize(class Application* application);
        void Run();
        void Shutdown();
    private:
        Engine() = default;
        ~Engine() = default;
    private:
        void OnWindowResize(const struct WindowResizeEvent& e);
        void OnWindowClose(const struct WindowCloseEvent& e);
    private:
        Bool8 m_Running;
        Bool8 m_Suspended;

        UniquePtr<class Application> m_Application;
    };
}

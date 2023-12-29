#include "Engine.hpp"

#include "LumyEngine/Core/Application.hpp"
#include "LumyEngine/Core/Platform/ApplicationLayer.hpp"

#include "LumyEngine/Core/Events/Events.hpp"
#include "LumyEngine/Core/Events/WindowEvent.hpp"

#include "LumyEngine/Renderer/Renderer.hpp"

#include "LumyEngine/Debug/Profiler.hpp"

namespace Lumy
{
    Engine& Engine::Create()
    {
        static Engine instance;
        return instance;
    }

    void Engine::Initialize(Application* application)
    {
        LM_PROFILE_FUNCTION();

        Log::Get().Initialize();

        // Platform layer
        ApplicationLayer::Get().Initialize();
        WindowProperties windowProperties;
        windowProperties.Title = application->GetConfiguration().ApplicationName;
        windowProperties.X = application->GetConfiguration().WindowX;
        windowProperties.Y = application->GetConfiguration().WindowY;
        windowProperties.Width = application->GetConfiguration().WindowWidth;
        windowProperties.Height = application->GetConfiguration().WindowHeight;

        // Renderer
        Renderer::Get().Initialize();

        ApplicationLayer::Get().CreateWindow(windowProperties);

        Events::Get().Initialize();
        Events::Get().Subscribe<WindowResizeEvent>(MakeDelegate<&Engine::OnWindowResize>(this));
        Events::Get().Subscribe<WindowCloseEvent>(MakeDelegate<&Engine::OnWindowClose>(this));

        // Application
        m_Application = UniquePtr<Application>(application);
        m_Application->SetEngine(this);
        m_Application->Initialize();

        m_Running = true;
        m_Suspended = false;

        Log::Info("Engine Initialized");
    }

    void Engine::Shutdown()
    {
        LM_PROFILE_FUNCTION();

        Log::Info("Engine Shutdown");
        // Application
        m_Application->Shutdown();

        Events::Get().Unsubscribe<WindowResizeEvent>(MakeDelegate<&Engine::OnWindowResize>(this));
        Events::Get().Unsubscribe<WindowCloseEvent>(MakeDelegate<&Engine::OnWindowClose>(this));
        Events::Get().Shutdown();

        ApplicationLayer::Get().Shutdown();

        // Renderer
        Renderer::Get().Shutdown();

        Log::Get().Shutdown();
    }

    void Engine::Run()
    {
        LM_PROFILE_FUNCTION();

        while (m_Running)
        {
            LM_PROFILE_SCOPE("Run Loop");

            ApplicationLayer::Get().Update();
            if (!m_Suspended)
            {
                m_Application->Update();
            }

            Events::Get().PublishEvents();
        }

        m_Running = false;
    }

    void Engine::OnWindowClose(const WindowCloseEvent& e)
    {
        m_Running = false;
    }

    void Engine::OnWindowResize(const WindowResizeEvent& e)
    {
        m_Suspended = (e.Width == 0 || e.Height == 0);
    }
}

#include "LumyEngine/Core/Engine.hpp"

#include "LumyEngine/Core/Event/EventManager.hpp"
#include "LumyEngine/Core/Input/Inputs.hpp"
#include "LumyEngine/Debug/Log.hpp"
#include "LumyEngine/Platform/Window.hpp"
#include "LumyEngine/Renderer/Renderer.hpp"
#include "Engine.hpp"

namespace Lumy
{
    struct EngineContext
    {
        bool IsRunning = false;
        bool IsSuspended = true;
        Window MainWindow;  // NOTE: Move window management to Platform ?
        std::unique_ptr<Application> ClientApplication;
    };

    static EngineContext* s_Context = nullptr;

    auto Engine::GetWindow() -> Window&
    {
        return s_Context->MainWindow;
    }

    auto Engine::ApplicationName() -> std::string_view
    {
        return s_Context->ClientApplication->Specification().Name;
    }

    auto Engine::Initialize(Application& application) -> bool
    {
        if (!Platform::Initialize())
        {
            Log::Fatal("Failed to initialize Platform");
            return false;
        }

        if (!EventManager::Initialize())
        {
            Log::Fatal("Failed to initialize Application Event");
            return false;
        }
        EventManager::Add<WindowCloseEvent>(MakeDelegate<&Engine::OnWindowClose>());
        EventManager::Add<WindowResizeEvent>(MakeDelegate<&Engine::OnWindowResize>());

        if (!Inputs::Initialize())
        {
            Log::Fatal("Failed to initialize Input");
            return false;
        }

        s_Context = new EngineContext();
        s_Context->ClientApplication.reset(&application);
        s_Context->MainWindow.Create(application.Specification().WindowSpec);
        if (!s_Context->ClientApplication->Initialize())
        {
            Log::Fatal("Failed to initialize Application");
            return false;
        }
        s_Context->IsSuspended = false;

        if (!Renderer::Initialize())
        {
            Log::Fatal("Failed to initialize Renderer");
            return false;
        }

        return true;
    }

    auto Engine::Shutdown() -> void
    {
        Renderer::Shutdown();

        s_Context->ClientApplication->Shutdown();
        s_Context->MainWindow.Destroy();
        delete s_Context;

        Inputs::Shutdown();

        EventManager::Remove<WindowCloseEvent>(MakeDelegate<&Engine::OnWindowClose>());
        EventManager::Remove<WindowResizeEvent>(MakeDelegate<&Engine::OnWindowResize>());
        EventManager::Shutdown();

        Platform::Shutdown();
    }

    auto Engine::Run() -> void
    {
        s_Context->IsRunning = true;
        // TODO: Add delta time
        Float64 deltaTime = 0.0;

        while (s_Context->IsRunning)
        {
            if (!Platform::PollEvents())
            {
                s_Context->IsRunning = false;
                break;
            }

            if (!s_Context->IsSuspended)
            {
                if (!s_Context->ClientApplication->Update(deltaTime))
                {
                    s_Context->IsRunning = false;
                    break;
                }

                if (!s_Context->ClientApplication->Render(deltaTime))
                {
                    s_Context->IsRunning = false;
                    break;
                }

                Renderer::DrawFrame();
            }
        }
    }

    auto Engine::OnWindowClose(const WindowCloseEvent& e) -> bool
    {
        s_Context->IsRunning = false;
        Log::Debug("{}", e);
        return false;
    }

    auto Engine::OnWindowResize(const WindowResizeEvent& e) -> bool
    {
        s_Context->IsSuspended = (e.Width == 0 or e.Height == 0);
        Renderer::OnResize(e.Width, e.Height);
        return false;
    }
}

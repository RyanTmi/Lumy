#include "LumyEngine/Core/Engine.hpp"

#include "LumyEngine/Core/Event/CoreEvents.hpp"
#include "LumyEngine/Core/Input/Inputs.hpp"
#include "LumyEngine/Debug/Logger.hpp"
#include "LumyEngine/Platform/Window.hpp"
#include "LumyEngine/Renderer/Renderer.hpp"

namespace Lumy
{
    struct EngineContext
    {
        bool IsRunning = false;
        bool IsSuspended = true;
        Window MainWindow;
        std::unique_ptr<Application> ClientApplication;
    };

    static EngineContext* s_Context = nullptr;

    auto Engine::GetWindow() -> Window&
    {
        return s_Context->MainWindow;
    }

    auto Engine::Initialize(Application& application) -> bool
    {
        if (!Platform::Initialize())
        {
            Log::Fatal("Failed to Initialize Platform");
            return false;
        }

        if (!CoreEvents::Initialize())
        {
            Log::Fatal("Failed to Initialize Application Event");
            return false;
        }
        CoreEvents::Add<WindowCloseEvent>(MakeDelegate<&Engine::OnWindowClose>());
        CoreEvents::Add<WindowResizeEvent>(MakeDelegate<&Engine::OnWindowResize>());

        if (!Inputs::Initialize())
        {
            Log::Fatal("Failed to Initialize Input");
            return false;
        }

        if (!Renderer::Initialize())
        {
            Log::Fatal("Failed to initialize Renderer");
            return false;
        }

        s_Context = new EngineContext();
        s_Context->ClientApplication.reset(&application);
        s_Context->MainWindow.Create(application.Specification().WindowSpec);
        if (!s_Context->ClientApplication->Initialize())
        {
            Log::Fatal("Failed to Initialize Application");
            return false;
        }
        s_Context->IsRunning = true;
        s_Context->IsSuspended = false;

        return true;
    }

    auto Engine::Shutdown() -> void
    {
        s_Context->ClientApplication->Shutdown();
        s_Context->MainWindow.Destroy();
        delete s_Context;

        Renderer::Shutdown();

        Inputs::Shutdown();

        CoreEvents::Remove<WindowCloseEvent>(MakeDelegate<&Engine::OnWindowClose>());
        CoreEvents::Remove<WindowResizeEvent>(MakeDelegate<&Engine::OnWindowResize>());
        CoreEvents::Shutdown();

        Platform::Shutdown();
    }

    auto Engine::Run() -> void
    {
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
        Log::Debug("{}", e);
        return false;
    }
}

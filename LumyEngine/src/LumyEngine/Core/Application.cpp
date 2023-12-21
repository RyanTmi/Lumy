#include "Application.hpp"

#include "Foundation.hpp"

namespace Lumy
{
    Application::Application()
        : m_Running(true), m_Window(std::unique_ptr<Window>(Window::Create(WindowProperties())))
    {
        LM_PROFILE_FUNCTION();

        EventManager::Subscribe<WindowResizeEvent>(MakeDelegate<&Application::OnWindowResize>(this));
        EventManager::Subscribe<WindowCloseEvent>(MakeDelegate<&Application::OnWindowClose>(this));
    }

    Application::~Application()
    {
        LM_PROFILE_FUNCTION();

        EventManager::Unsubscribe<WindowResizeEvent>(MakeDelegate<&Application::OnWindowResize>(this));
        EventManager::Unsubscribe<WindowCloseEvent>(MakeDelegate<&Application::OnWindowClose>(this));
    }

    void Application::Run()
    {
        LM_PROFILE_FUNCTION();

        while (m_Running)
        {
            LM_PROFILE_SCOPE("Run Loop");

            m_Window->Update();

            EventManager::PublishEvents();
        }
    }

    void Application::OnWindowClose(const WindowCloseEvent& e)
    {
        Log::Debug("{}", e);
        m_Running = false;
    }

    void Application::OnWindowResize(const WindowResizeEvent& e)
    {
        Log::Debug("{}", e);
    }
}

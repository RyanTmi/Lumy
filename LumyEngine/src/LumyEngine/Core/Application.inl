#pragma once

namespace Lumy
{
    inline ApplicationConfiguration::ApplicationConfiguration()
         : ApplicationName("ApplicationName"), WindowX(0), WindowY(0), WindowWidth(1280), WindowHeight(720), CenterWindow(true)
    {
    }

    inline ApplicationConfiguration::ApplicationConfiguration(const char* applicationName, UInt16 width, UInt16 height)
         : ApplicationName(applicationName), WindowX(0), WindowY(0), WindowWidth(width), WindowHeight(height), CenterWindow(true)
    {
    }

    inline Application::Application()
        : m_ApplicationConfiguration(), m_Engine(nullptr)
    {
    }

    inline ApplicationConfiguration& Application::GetConfiguration()
    {
        return m_ApplicationConfiguration;
    }

    inline void Application::SetEngine(Engine* engine)
    {
        m_Engine = engine;
    }
}

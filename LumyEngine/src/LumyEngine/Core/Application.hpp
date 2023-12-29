#pragma once

#include "Foundation.hpp"
#include "Engine.hpp"

namespace Lumy
{
    struct LUMY_API ApplicationConfiguration
    {
        ApplicationConfiguration();
        ApplicationConfiguration(const char* applicationName, UInt16 width, UInt16 height);

        const char* ApplicationName;

        // TODO: Change to a Rectangle struct
        UInt16 WindowX;
        UInt16 WindowY;
        UInt16 WindowWidth;
        UInt16 WindowHeight;
        
        Bool8 CenterWindow;
    };

    class LUMY_API Application
    {
    public:
        Application();
        virtual ~Application() = default;
    public:
        virtual void Initialize() = 0;
        virtual void Update() = 0;
        virtual void Shutdown() = 0;
    public:
        ApplicationConfiguration& GetConfiguration();
        void SetEngine(Engine* engine);
    protected:
        ApplicationConfiguration m_ApplicationConfiguration;
        Engine* m_Engine;
    };

    extern Application* ApplicationCreate();
}

#include "Application.inl"

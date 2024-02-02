#include "MacOSApplicationLayer.hpp"

#include "LumyEngine/Core/Foundation.hpp"

#include "LumyEngine/Platform/MacOS/MacOSScopeAutoReleasePool.hpp"
#include "LumyEngine/Platform/MacOS/MacOSWindow.hpp"

#import <AppKit/AppKit.h>

namespace Lumy
{
    ApplicationLayer& ApplicationLayer::Get()
    {
        static MacOSApplicationLayer instance;
        return instance;
    }

    void MacOSApplicationLayer::Initialize()
    {
        const MacOSScopeAutoReleasePool pool;

        m_ApplicationDelegate = ApplicationDelegate();

        m_Application = NS::Application::sharedApplication();
        m_Application->setDelegate(&m_ApplicationDelegate);
        m_Application->setActivationPolicy(NS::ActivationPolicyRegular);

        if (![[NSRunningApplication currentApplication] isFinishedLaunching])
        {
            [NSApp run];
        }

        m_Application->activateIgnoringOtherApps(true);

        Log::Info("MacOS platform application created");
    }

    void MacOSApplicationLayer::Update()
    {
        m_Window->Update();
    }

    void MacOSApplicationLayer::Shutdown()
    {
    }

    void MacOSApplicationLayer::CreateWindow(const WindowProperties& windowProperties)
    {
        m_Window = UniquePtr<Window>(new MacOSWindow(windowProperties));
    }
}

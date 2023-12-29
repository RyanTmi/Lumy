#pragma once

#include "LumyEngine/Core/Platform/ApplicationLayer.hpp"
#include "LumyEngine/Platform/MacOS/MacOSApplicationDelegate.hpp"

#include <AppKit/AppKit.hpp>

namespace Lumy
{
    class MacOSApplicationLayer : public ApplicationLayer
    {
    public:
        void Initialize() override;
        void Update() override;
        void Shutdown() override;

        void CreateWindow(const WindowProperties& windowProperties) override;
    private:
        NS::Application* m_Application;
        ApplicationDelegate m_ApplicationDelegate;
    };
}

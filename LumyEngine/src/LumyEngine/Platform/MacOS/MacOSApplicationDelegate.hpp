#pragma once

#include <AppKit/AppKit.hpp>

namespace Lumy
{
    class ApplicationDelegate : public NS::ApplicationDelegate
    {
    public:
        void applicationWillFinishLaunching(NS::Notification* notification) override;
        void applicationDidFinishLaunching(NS::Notification* notification) override;
        bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* sender) override;
    };
}

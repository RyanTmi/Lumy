#include "MacOSApplicationDelegate.hpp"

#include "LumyEngine/Core/Foundation.hpp"

namespace Lumy
{
    void ApplicationDelegate::applicationWillFinishLaunching(NS::Notification *notification)
    {
    }

    void ApplicationDelegate::applicationDidFinishLaunching(NS::Notification *notification)
    {
    }

    bool ApplicationDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application *sender)
    {
        return true;
    }
}

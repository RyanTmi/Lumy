#include "MacOSApplicationDelegate.hpp"

#include "LumyEngine/Core/Foundation.hpp"

#include "MacOSScopeAutoReleasePool.hpp"

#import <AppKit/AppKit.h>

namespace Lumy
{
    void ApplicationDelegate::applicationWillFinishLaunching(NS::Notification *notification)
    {
    }

    void ApplicationDelegate::applicationDidFinishLaunching(NS::Notification *notification)
    {
        const MacOSScopeAutoReleasePool pool;

        NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                            location:NSMakePoint(0, 0)
                                       modifierFlags:0
                                           timestamp:0
                                        windowNumber:0
                                             context:nil
                                             subtype:0
                                               data1:0
                                               data2:0];
        [NSApp postEvent:event atStart:YES];
        [NSApp stop:nil];
    }

    bool ApplicationDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application *sender)
    {
        return true;
    }
}

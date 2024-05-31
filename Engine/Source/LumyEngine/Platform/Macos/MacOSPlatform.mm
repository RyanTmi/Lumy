#include "LumyEngine/Platform/Platform.hpp"

#include "LumyEngine/Debug/Logger.hpp"
#include "LumyEngine/Platform/MacOS/MacOSApplicationDelegate.hpp"
#include "LumyEngine/Platform/MacOS/MacOSAutoreleasePool.hpp"

namespace Lumy
{
    struct PlatformContext
    {
        MacOSApplicationDelegate* Delegate = nullptr;
    };

    static PlatformContext* s_Context = nullptr;

    auto Platform::Initialize() -> bool
    {
        if (s_Context != nullptr)
        {
            Log::Error("Cocoa: Failed to Initialize Platform");
            return false;
        }
        s_Context = new PlatformContext();

        @autoreleasepool
        {
            [NSApplication sharedApplication];
            s_Context->Delegate = [[MacOSApplicationDelegate alloc] init];
            if (s_Context->Delegate == nil)
            {
                Log::Error("Cocoa: Failed to Create Application Delegate");
                return false;
            }

            [NSApp setDelegate:s_Context->Delegate];

            if (![[NSRunningApplication currentApplication] isFinishedLaunching])
            {
                [NSApp run];
            }

            [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        }

        return true;
    }

    auto Platform::Shutdown() -> void
    {
        @autoreleasepool
        {
            if (s_Context->Delegate)
            {
                [NSApp setDelegate:nil];
                [s_Context->Delegate release];
                s_Context->Delegate = nil;
            }
        }

        delete s_Context;
        s_Context = nullptr;
    }

    auto Platform::PollEvents() -> bool
    {
        @autoreleasepool
        {
            while (true)
            {
                NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                                    untilDate:[NSDate distantPast]
                                                       inMode:NSDefaultRunLoopMode
                                                      dequeue:YES];
                if (event == nil)
                {
                    break;
                }

                [NSApp sendEvent:event];
            }
        }

        return true;
    }

    auto Platform::ProcessorCount() -> UInt8
    {
        return static_cast<UInt8>([[NSProcessInfo processInfo] processorCount]);
    }
}

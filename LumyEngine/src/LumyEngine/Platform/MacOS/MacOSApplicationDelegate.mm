#include "MacOSApplicationDelegate.hpp"

#include "LumyEngine/Core/Foundation.hpp"

@implementation MacOSApplicationDelegate

// Launching Applications

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    Lumy::Log::Info("applicationWillFinishLaunching");
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    Lumy::Log::Info("applicationDidFinishLaunching");
}

// Terminating Applications

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

@end

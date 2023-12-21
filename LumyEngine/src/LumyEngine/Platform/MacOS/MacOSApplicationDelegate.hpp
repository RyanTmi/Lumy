#pragma once

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

struct WindowHandle;

@interface MacOSApplicationDelegate : NSObject<NSApplicationDelegate>

- (void)applicationWillFinishLaunching:(NSNotification *)notification;

- (void)applicationDidFinishLaunching:(NSNotification *)notification;


// Terminating Applications

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;

@end

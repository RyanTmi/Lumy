#include "MacOSWindow.hpp"

#include "LumyEngine/Core/Foundation.hpp"

#include "MacOSScopeAutoReleasePool.hpp"
#include "MacOSApplicationDelegate.hpp"
#include "MacOSWindowController.hpp"

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

#include <MetalKit/MetalKit.hpp>

namespace Lumy
{
    static bool s_NSApplicationInitialized = false;

    struct WindowHandle
    {
        MacOSWindowController* WindowController;
        NSView* View;
    };

    static void InitializeNSApplication()
    {
        const MacOSScopeAutoReleasePool pool;

        [NSApplication sharedApplication];

        // Setup Application Delegate
        MacOSApplicationDelegate* applicationDelegate = [[MacOSApplicationDelegate alloc] init];
        [NSApp setDelegate:applicationDelegate];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        [NSApp activateIgnoringOtherApps:YES];

        s_NSApplicationInitialized = true;
    }
    
    MacOSWindow::MacOSWindow(const WindowProperties& properties)
    {
        const MacOSScopeAutoReleasePool pool;

        if (!s_NSApplicationInitialized)
        {
            InitializeNSApplication();
        }

        m_WindowHandle = std::make_unique<WindowHandle>();

        // Setup Window
        NSRect rect = NSMakeRect(properties.X, properties.Y,
                                 static_cast<CGFloat>(properties.Width) / 2.0f,
                                 static_cast<CGFloat>(properties.Height) / 2.0f);

        NSWindowStyleMask styleMask = 0;
        styleMask |= NSWindowStyleMaskMiniaturizable;
        styleMask |= NSWindowStyleMaskTitled;
        styleMask |= NSWindowStyleMaskClosable;
        styleMask |= NSWindowStyleMaskResizable;

        NSWindow* window = [[NSWindow alloc] initWithContentRect:rect
                                                       styleMask:styleMask
                                                         backing:NSBackingStoreBuffered
                                                           defer:NO];

        NSString* windowTitle = [NSString stringWithCString:properties.Title encoding:[NSString defaultCStringEncoding]];
        [window setTitle:windowTitle];
        [window center];

        // Setup Window Controller and Window Delegate
        m_WindowHandle->WindowController = [[MacOSWindowController alloc] initWithWindow:window];
        [window setDelegate:m_WindowHandle->WindowController];
        
        // Setup View
//        m_WindowHandle->View = [[NSView alloc] init];
//        [m_WindowHandle->View setHidden:NO];
//        [m_WindowHandle->View setNeedsDisplay:YES];
//        [m_WindowHandle->Window setContentView:m_WindowHandle->View];


        // Show the window
        [window makeKeyAndOrderFront:nil];
    }

    MacOSWindow::~MacOSWindow()
    {
        const MacOSScopeAutoReleasePool pool;

        [m_WindowHandle->WindowController release];
        [m_WindowHandle->View release];
    }

    UInt16 MacOSWindow::GetWidth() const
    {
        CGFloat width = [m_WindowHandle->WindowController window].frame.size.height;
        return static_cast<UInt16>(width);
    }

    UInt16 MacOSWindow::GetHeight() const
    {
        CGFloat height = [m_WindowHandle->WindowController window].frame.size.height;
        return static_cast<UInt16>(height);
    }
    
    void MacOSWindow::Update()
    {
        const MacOSScopeAutoReleasePool pool;

        NSEvent* event;
        while (true)
        {
            event = [NSApp nextEventMatchingMask:NSEventMaskAny
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
}

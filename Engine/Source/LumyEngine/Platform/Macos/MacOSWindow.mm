#include "LumyEngine/Platform/Window.hpp"

#include "LumyEngine/Debug/Log.hpp"
#include "LumyEngine/Platform/MacOS/MacOSAutoreleasePool.hpp"
#include "LumyEngine/Platform/MacOS/MacOSContentView.hpp"
#include "LumyEngine/Platform/MacOS/MacOSWindow.hpp"
#include "LumyEngine/Platform/MacOS/MacOSWindowDelegate.hpp"

#include "QuartzCore/CAMetalLayer.hpp"

#import <QuartzCore/CAMetalLayer.h>

//======================================================================================================================
// Class : MacOSWindow
//======================================================================================================================

@implementation MacOSWindow

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}

@end

namespace Lumy
{
    //==================================================================================================================
    // Class : MacOSNativeWindow
    //==================================================================================================================

    MacOSNativeWindow::~MacOSNativeWindow()
    {
        @autoreleasepool
        {
            if (m_Window)
            {
                [m_Window orderOut:nil];
                [m_Window setDelegate:nil];
                [m_Window close];
                m_Window = nil;
            }

            if (m_View)
            {
                [m_View release];
                m_View = nil;
            }

            if (m_Delegate)
            {
                [m_Delegate release];
                m_Delegate = nil;
            }

            if (m_Layer)
            {
                [m_Layer release];
                m_Layer = nil;
            }
        }
    }

    auto MacOSNativeWindow::Create(const WindowSpecification& spec) -> bool
    {
        @autoreleasepool
        {
            m_Delegate = [[MacOSWindowDelegate alloc] init];
            if (!m_Delegate)
            {
                Log::Error("Cocoa: Failed to create window delegate");
                return false;
            }

            NSRect contentRect =
                NSMakeRect(spec.Frame.X, spec.Frame.Y, spec.Frame.Width, spec.Frame.Height);

            NSUInteger styleMask = 0;
            styleMask |= NSWindowStyleMaskMiniaturizable;
            styleMask |= NSWindowStyleMaskTitled;
            styleMask |= NSWindowStyleMaskClosable;
            styleMask |= NSWindowStyleMaskResizable;

            m_Window = [[MacOSWindow alloc] initWithContentRect:contentRect
                                                      styleMask:styleMask
                                                        backing:NSBackingStoreBuffered
                                                          defer:NO];
            if (!m_Window)
            {
                Log::Error("Cocoa: Failed to create window");
                return false;
            }
            // NOTE: Needed for manually release MacOSWindow in ~MacOSNativeWindow()
            m_Window.releasedWhenClosed = NO;

            m_Layer = [CAMetalLayer layer];
            if (!m_Layer)
            {
                Log::Error("Cocoa: Failed to create metal layer");
                return false;
            }

            m_View = [[MacOSContentView alloc] initWithWindow:m_Window frame:contentRect];
            if (!m_View)
            {
                Log::Error("Cocoa: Failed to create content view");
                return false;
            }
            [m_View setLayer:m_Layer];

            [m_Window center];
            [m_Window setLevel:NSNormalWindowLevel];
            [m_Window setContentView:m_View];
            [m_Window makeFirstResponder:m_View];
            [m_Window setTitle:@(spec.Title.data())];
            [m_Window setDelegate:m_Delegate];
            [m_Window setAcceptsMouseMovedEvents:YES];

            [NSApp activateIgnoringOtherApps:YES];
            [m_Window makeKeyAndOrderFront:nil];
        }
        return true;
    }

    auto MacOSNativeWindow::GetLayer() -> CA::MetalLayer*
    {
        return (__bridge CA::MetalLayer*) m_Layer;
    }

    auto MacOSNativeWindow::Size() const -> std::pair<UInt32, UInt32>
    {
        @autoreleasepool
        {
            if (!m_Window)
            {
                return {0, 0};
            }

            const NSRect frame = [m_Window frame];
            const auto width = static_cast<UInt32>(frame.size.width);
            const auto height = static_cast<UInt32>(frame.size.height);
            return {width, height};
        }
    }

    auto MacOSNativeWindow::FramebufferSize() const -> std::pair<UInt32, UInt32>
    {
        @autoreleasepool
        {
            if (!m_Window)
            {
                return {0, 0};
            }

            const NSRect contentRect = [m_View frame];
            const NSRect framebufferRect = [m_View convertRectToBacking:contentRect];
            return {framebufferRect.size.width, framebufferRect.size.height};
        }
    }

    auto MacOSNativeWindow::SetTitle(std::string_view title) -> void
    {
        @autoreleasepool
        {
            if (m_Window)
            {
                NSString* nsTitle = @(title.data());
                [m_Window setTitle:nsTitle];
                [m_Window setMiniwindowTitle:nsTitle];
            }
        }
    }

    auto MacOSNativeWindow::Show() -> void
    {
        @autoreleasepool
        {
            if (m_Window)
            {
                [m_Window orderFront:nil];
            }
        }
    }

    auto MacOSNativeWindow::Hide() -> void
    {
        @autoreleasepool
        {
            if (m_Window)
            {
                [m_Window orderOut:nil];
            }
        }
    }

    auto MacOSNativeWindow::Focus() -> void
    {
        @autoreleasepool
        {
            if (m_Window)
            {
                [NSApp activateIgnoringOtherApps:YES];
                [m_Window makeKeyAndOrderFront:nil];
            }
        }
    }

    auto MacOSNativeWindow::Maximize() -> void
    {
        @autoreleasepool
        {
            if (m_Window)
            {
                if (![m_Window isZoomed])
                {
                    [m_Window zoom:nil];
                }
            }
        }
    }

    //==================================================================================================================
    // Class : Window
    //==================================================================================================================

    Window::~Window()
    {
        Destroy();
    }

    auto Window::Create(const WindowSpecification& specification) -> bool
    {
        if (m_NativeWindow)
        {
            Destroy();
        }

        auto nativeWindow = new MacOSNativeWindow();
        m_NativeWindow = nativeWindow;
        return nativeWindow->Create(specification);
    }

    auto Window::Destroy() -> void
    {
        if (m_NativeWindow)
        {
            auto nativeWindow = reinterpret_cast<MacOSNativeWindow*>(m_NativeWindow);
            delete nativeWindow;
            m_NativeWindow = nullptr;
        }
    }

    auto Window::Size() const -> std::pair<UInt32, UInt32>
    {
        if (!m_NativeWindow)
        {
            return {0, 0};
        }
        auto nativeWindow = reinterpret_cast<MacOSNativeWindow*>(m_NativeWindow);
        return nativeWindow->Size();
    }

    auto Window::SetTitle(std::string_view title) -> void
    {
        if (!m_NativeWindow)
        {
            return;
        }
        auto nativeWindow = reinterpret_cast<MacOSNativeWindow*>(m_NativeWindow);
        return nativeWindow->SetTitle(title);
    }

    auto Window::Show() -> void
    {
        if (!m_NativeWindow)
        {
            return;
        }
        auto nativeWindow = reinterpret_cast<MacOSNativeWindow*>(m_NativeWindow);
        return nativeWindow->Show();
    }

    auto Window::Hide() -> void
    {
        if (!m_NativeWindow)
        {
            return;
        }
        auto nativeWindow = reinterpret_cast<MacOSNativeWindow*>(m_NativeWindow);
        return nativeWindow->Hide();
    }

    auto Window::Maximize() -> void
    {
        if (!m_NativeWindow)
        {
            return;
        }
        auto nativeWindow = reinterpret_cast<MacOSNativeWindow*>(m_NativeWindow);
        return nativeWindow->Maximize();
    }

    auto Window::GetSurface() -> void*
    {
        if (!m_NativeWindow)
        {
            return nullptr;
        }
        auto nativeWindow = reinterpret_cast<MacOSNativeWindow*>(m_NativeWindow);
        return nativeWindow->GetLayer();
    }
    
    auto Window::GetFramebufferSize() -> std::pair<UInt32, UInt32>
    {
        if (!m_NativeWindow)
        {
            return {0, 0};
        }
        auto nativeWindow = reinterpret_cast<MacOSNativeWindow*>(m_NativeWindow);
        return nativeWindow->FramebufferSize();
    }
}

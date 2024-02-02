#include "MacOSWindow.hpp"

#include "LumyEngine/Core/Foundation.hpp"
#include "LumyEngine/Renderer/Renderer.hpp"
#include "LumyEngine/Renderer/Metal/MetalBackend.hpp"

#include "MacOSScopeAutoReleasePool.hpp"
#include "MacOSApplicationDelegate.hpp"
#include "MacOSWindowController.hpp"
#include "MacOSViewDelegate.hpp"

#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <QuartzCore/CAMetalLayer.h>

namespace Lumy
{
    struct MacOSWindow::WindowHandle
    {
        NS::Window* GetWindow() const
        {
            return (__bridge NS::Window*)[WindowController window];
        }

        MacOSWindowController* WindowController;
    };
    
    MacOSWindow::MacOSWindow(const WindowProperties& properties)
    {
        const MacOSScopeAutoReleasePool pool;
        
        m_WindowHandle = std::make_unique<WindowHandle>();

        NSRect rect = NSMakeRect(properties.X, properties.Y,
                                 static_cast<CGFloat>(properties.Width) / 2.0f,
                                 static_cast<CGFloat>(properties.Height) / 2.0f);

        NS::WindowStyleMask styleMask = 0;
        styleMask |= NS::WindowStyleMaskMiniaturizable;
        styleMask |= NS::WindowStyleMaskTitled;
        styleMask |= NS::WindowStyleMaskClosable;
        styleMask |= NS::WindowStyleMaskResizable;

        NS::String* windowTitle = NS::String::string(properties.Title, NS::UTF8StringEncoding);
        NS::Window* window = NS::Window::alloc()->init(rect, styleMask, NS::BackingStoreBuffered, false);

        // TODO: Test
        MetalBackend* backend = dynamic_cast<MetalBackend*>(Renderer::Get().GetBackend());
        MTL::Device* device = backend->GetDevice();
        CA::MetalLayer* layer = CA::MetalLayer::layer();
        layer->setDevice(device);
        layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
        backend->SetLayer(layer);
        // TODO: Test
        
        window->setTitle(windowTitle);
        
        NSWindow* objc_window = (__bridge NSWindow*) window;
        [objc_window center];

        // TODO: Test
        objc_window.contentView.layer = (__bridge CAMetalLayer*) layer;
        objc_window.contentView.wantsLayer = YES;
        // TODO: Test

        // Setup Window Controller and Window Delegate
        m_WindowHandle->WindowController = [[MacOSWindowController alloc] initWithWindow:objc_window];
        [objc_window setDelegate:m_WindowHandle->WindowController];
        [objc_window setAcceptsMouseMovedEvents:YES];

        // Show the window
        [m_WindowHandle->WindowController showWindow:objc_window];
        [objc_window makeKeyAndOrderFront:nil];
    }

    MacOSWindow::~MacOSWindow()
    {
        const MacOSScopeAutoReleasePool pool;

        [m_WindowHandle->WindowController release];
    }

    UInt16 MacOSWindow::GetWidth() const
    {
        NSWindow* window = reinterpret_cast<NSWindow*>(m_WindowHandle->GetWindow());
        return static_cast<UInt16>(window.frame.size.width);
    }

    UInt16 MacOSWindow::GetHeight() const
    {
        NSWindow* window = reinterpret_cast<NSWindow*>(m_WindowHandle->GetWindow());
        return static_cast<UInt16>(window.frame.size.height);
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
    
    void* MacOSWindow::GetNativeWindow() const
    {
        return m_WindowHandle->GetWindow();
    }
}

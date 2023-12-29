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

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

namespace Lumy
{
    struct MacOSWindow::WindowHandle
    {
        NS::Window* GetWindow() const
        {
            return reinterpret_cast<NS::Window*>([WindowController window]);
        }

        MacOSWindowController* WindowController;
        MTK::View* View;
        MacOSViewDelegate* ViewDelegate;
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

        MetalBackend* backend = dynamic_cast<MetalBackend*>(Renderer::Get().GetBackend());
        MTL::Device* device = backend->GetDevice();

        m_WindowHandle->View = MTK::View::alloc()->init(rect, device);
        m_WindowHandle->View->setColorPixelFormat(MTL::PixelFormatBGRA8Unorm);
        
        m_WindowHandle->ViewDelegate = new MacOSViewDelegate(backend);
        m_WindowHandle->View->setDelegate(m_WindowHandle->ViewDelegate);

        window->setContentView(m_WindowHandle->View);
        window->setTitle(windowTitle);

        [(__bridge NSWindow*)window center];

        // Setup Window Controller and Window Delegate
        m_WindowHandle->WindowController = [[MacOSWindowController alloc] initWithWindow:(__bridge NSWindow*)window];
        [(__bridge NSWindow*)window setDelegate:m_WindowHandle->WindowController];

        // Show the window
        window->makeKeyAndOrderFront(nullptr);
    }

    MacOSWindow::~MacOSWindow()
    {
        const MacOSScopeAutoReleasePool pool;

        [m_WindowHandle->WindowController release];
        m_WindowHandle->View->release();
        delete m_WindowHandle->ViewDelegate;
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

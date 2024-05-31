#include "LumyEngine/Platform/MacOS/MacOSWindowDelegate.hpp"

#include "LumyEngine/Core/Event/CoreEvents.hpp"
#include "LumyEngine/Core/Event/WindowEvent.hpp"

using namespace Lumy;

@implementation MacOSWindowDelegate

- (BOOL)windowShouldClose:(id)sender
{
    CoreEvents::Fire<WindowCloseEvent>();
    return YES;
}

- (void)windowDidResize:(NSNotification*)notification
{
    NSWindow* Window = [notification object];

    NSView* view = Window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    CoreEvents::Fire<WindowResizeEvent>(width, height);
}

- (void)windowDidMove:(NSNotification*)notification
{}

- (void)windowDidMiniaturize:(NSNotification*)notification
{
    CoreEvents::Fire<WindowResizeEvent>(0, 0);
}

- (void)windowDidDeminiaturize:(NSNotification*)notification
{
    NSWindow* Window = [notification object];

    NSView* view = Window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    CoreEvents::Fire<WindowResizeEvent>(width, height);
}

- (void)windowDidChangeScreen:(NSNotification*)notification
{
    NSWindow* Window = [notification object];

    NSView* view = Window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    CoreEvents::Fire<WindowResizeEvent>(width, height);
}

- (void)windowDidBecomeKey:(NSNotification*)notification
{}

- (void)windowDidResignKey:(NSNotification*)notification
{}

- (void)windowDidChangeOcclusionState:(NSNotification*)notification
{}

@end

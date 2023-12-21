#include "MacOSWindowController.hpp"

#include "LumyEngine/Core/Events/EventManager.hpp"
#include "LumyEngine/Core/Events/WindowEvent.hpp"

using namespace Lumy;

@implementation MacOSWindowController

- (void)windowDidResize:(NSNotification *)notification
{
    NSWindow* window = [notification object];

    NSView* view = window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    EventManager::SendEvent(WindowResizeEvent(width, height));
}

- (void)windowDidMiniaturize:(NSNotification *)notification
{
    EventManager::SendEvent(WindowResizeEvent(0, 0));
}

- (void)windowDidDeminiaturize:(NSNotification *)notification
{
    NSWindow* window = [notification object];

    NSView* view = window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    EventManager::SendEvent(WindowResizeEvent(width, height));
}

- (void)windowDidChangeScreen:(NSNotification *)notification
{
    NSWindow* window = [notification object];

    NSView* view = window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    EventManager::SendEvent(WindowResizeEvent(width, height));
}

- (BOOL)windowShouldClose:(NSWindow *)sender
{
    Lumy::EventManager::QueueEvent<WindowCloseEvent>();
    return YES;
}

@end

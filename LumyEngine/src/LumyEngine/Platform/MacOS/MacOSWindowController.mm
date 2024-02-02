#include "MacOSWindowController.hpp"

#include "LumyEngine/Core/Events/Events.hpp"

#include "LumyEngine/Core/Events/WindowEvent.hpp"
#include "LumyEngine/Core/Events/KeyEvent.hpp"
#include "LumyEngine/Core/Events/MouseEvent.hpp"

static Lumy::KeyCode TranslateKey(Lumy::UInt16 keyCode);

@implementation MacOSWindowController

- (void)windowDidResize:(NSNotification *)notification
{
    NSWindow* window = [notification object];

    NSView* view = window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    Lumy::Events::Get().SendEvent<Lumy::WindowResizeEvent>(width, height);
}

- (void)windowDidMiniaturize:(NSNotification *)notification
{
    Lumy::Events::Get().SendEvent<Lumy::WindowResizeEvent>(0, 0);
}

- (void)windowDidDeminiaturize:(NSNotification *)notification
{
    NSWindow* window = [notification object];

    NSView* view = window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    Lumy::Events::Get().SendEvent<Lumy::WindowResizeEvent>(width, height);
}

- (void)windowDidChangeScreen:(NSNotification *)notification
{
    NSWindow* window = [notification object];

    NSView* view = window.contentView;
    CGSize viewSize = view.bounds.size;
    NSSize size = [view convertSizeToBacking:viewSize];

    auto width = static_cast<UInt16>(size.width);
    auto height = static_cast<UInt16>(size.height);
    Lumy::Events::Get().SendEvent<Lumy::WindowResizeEvent>(width, height);
}

- (BOOL)windowShouldClose:(NSWindow *)sender
{
    Lumy::Events::Get().QueueEvent<Lumy::WindowCloseEvent>();
    return YES;
}

- (void)keyDown:(NSEvent *)event
{
    Lumy::KeyCode keyCode = TranslateKey([event keyCode]);
    Lumy::Events::Get().QueueEvent<Lumy::KeyPressedEvent>(keyCode);
}

- (void)keyUp:(NSEvent *)event
{
    Lumy::KeyCode keyCode = TranslateKey([event keyCode]);
    Lumy::Events::Get().QueueEvent<Lumy::KeyReleasedEvent>(keyCode);
}

- (void)mouseMoved:(NSEvent *)event
{
    NSPoint mousePosition = [event locationInWindow];
    Lumy::Events::Get().QueueEvent<Lumy::MouseMovedEvent>(mousePosition.x, mousePosition.y);
}

- (void)mouseDragged:(NSEvent *)event
{
    [self mouseMoved:event];
}

- (void)mouseDown:(NSEvent *)event
{
    Lumy::MouseButton button = static_cast<Lumy::MouseButton>([event buttonNumber]);
    Lumy::Events::Get().QueueEvent<Lumy::MouseButtonPressedEvent>(button);
}

- (void)mouseUp:(NSEvent *)event
{
    Lumy::MouseButton button = static_cast<Lumy::MouseButton>([event buttonNumber]);
    Lumy::Events::Get().QueueEvent<Lumy::MouseButtonReleasedEvent>(button);
}

- (void)rightMouseDown:(NSEvent *)event
{
    Lumy::MouseButton button = static_cast<Lumy::MouseButton>([event buttonNumber]);
    Lumy::Events::Get().QueueEvent<Lumy::MouseButtonPressedEvent>(button);
}

- (void)rightMouseUp:(NSEvent *)event
{
    Lumy::MouseButton button = static_cast<Lumy::MouseButton>([event buttonNumber]);
    Lumy::Events::Get().QueueEvent<Lumy::MouseButtonReleasedEvent>(button);
}

- (void)scrollWheel:(NSEvent *)event
{
    Lumy::Events::Get().QueueEvent<Lumy::MouseScrolledEvent>([event scrollingDeltaX], [event scrollingDeltaY]);
}

@end

Lumy::KeyCode TranslateKey(Lumy::UInt16 keyCode)
{
    using namespace Lumy;
    switch (keyCode) {
        case 0x00: return KeyCode::A;
        case 0x0B: return KeyCode::B;
        case 0x08: return KeyCode::C;
        case 0x02: return KeyCode::D;
        case 0x0E: return KeyCode::E;
        case 0x03: return KeyCode::F;
        case 0x05: return KeyCode::G;
        case 0x04: return KeyCode::H;
        case 0x22: return KeyCode::I;
        case 0x26: return KeyCode::J;
        case 0x28: return KeyCode::K;
        case 0x25: return KeyCode::L;
        case 0x2E: return KeyCode::M;
        case 0x2D: return KeyCode::N;
        case 0x1F: return KeyCode::O;
        case 0x23: return KeyCode::P;
        case 0x0C: return KeyCode::Q;
        case 0x0F: return KeyCode::R;
        case 0x01: return KeyCode::S;
        case 0x11: return KeyCode::T;
        case 0x20: return KeyCode::U;
        case 0x09: return KeyCode::V;
        case 0x0D: return KeyCode::W;
        case 0x07: return KeyCode::X;
        case 0x10: return KeyCode::Y;
        case 0x06: return KeyCode::Z;
            
        case 0x1D: return KeyCode::Zero;
        case 0x12: return KeyCode::One;
        case 0x13: return KeyCode::Two;
        case 0x14: return KeyCode::Three;
        case 0x15: return KeyCode::Four;
        case 0x17: return KeyCode::Five;
        case 0x16: return KeyCode::Six;
        case 0x1A: return KeyCode::Seven;
        case 0x1C: return KeyCode::Eight;
        case 0x19: return KeyCode::Nine;
            
        case 0x52: return KeyCode::Keypad0;
        case 0x53: return KeyCode::Keypad1;
        case 0x54: return KeyCode::Keypad2;
        case 0x55: return KeyCode::Keypad3;
        case 0x56: return KeyCode::Keypad4;
        case 0x57: return KeyCode::Keypad5;
        case 0x58: return KeyCode::Keypad6;
        case 0x59: return KeyCode::Keypad7;
        case 0x5B: return KeyCode::Keypad8;
        case 0x5C: return KeyCode::Keypad9;
            
        case 0x45: return KeyCode::Add;
        case 0x41: return KeyCode::Decimal;
        case 0x4B: return KeyCode::Divide;
        case 0x4C: return KeyCode::Enter;
        case 0x51: return KeyCode::NumpadEqual;
        case 0x43: return KeyCode::Multiply;
        case 0x4E: return KeyCode::Substract;
            
        case 0x7A: return KeyCode::F1;
        case 0x78: return KeyCode::F2;
        case 0x63: return KeyCode::F3;
        case 0x76: return KeyCode::F4;
        case 0x60: return KeyCode::F5;
        case 0x61: return KeyCode::F6;
        case 0x62: return KeyCode::F7;
        case 0x64: return KeyCode::F8;
        case 0x65: return KeyCode::F9;
        case 0x6D: return KeyCode::F10;
        case 0x67: return KeyCode::F11;
        case 0x6F: return KeyCode::F12;
        case 0x69: return KeyCode::F13;
        case 0x6B: return KeyCode::F14;
        case 0x71: return KeyCode::F15;
        case 0x6A: return KeyCode::F16;
        case 0x40: return KeyCode::F17;
        case 0x4F: return KeyCode::F18;
        case 0x50: return KeyCode::F19;
        case 0x5A: return KeyCode::F20;

        case 0x33: return KeyCode::BackSpace;
        case 0x39: return KeyCode::Capital;
        case 0x75: return KeyCode::Delete;
        case 0x7D: return KeyCode::Down;
        case 0x77: return KeyCode::End;
        case 0x24: return KeyCode::Enter;
        case 0x35: return KeyCode::Escape;
        
        default: return KeyCode::A;
    }
}

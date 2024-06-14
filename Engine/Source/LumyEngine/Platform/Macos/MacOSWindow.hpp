#pragma once

#include "LumyEngine/Platform/Window.hpp"

#import <AppKit/NSWindow.h>

@class MacOSWindowDelegate;
@class MacOSContentView;
@class CAMetalLayer;

@interface MacOSWindow : NSWindow
{}
@end

namespace CA
{
    class MetalLayer;
}

namespace Lumy
{
    class MacOSNativeWindow
    {
    public:
        MacOSNativeWindow() = default;
        ~MacOSNativeWindow();

    public:
        auto Create(const WindowSpecification& spec) -> bool;

        // TODO: Change to Vector2 struct
        auto Size() const -> std::pair<UInt32, UInt32>;

        auto SetTitle(std::string_view title) -> void;
        auto Show() -> void;
        auto Hide() -> void;
        auto Focus() -> void;
        auto Maximize() -> void;

        auto FramebufferSize() const -> std::pair<UInt32, UInt32>;
        auto GetLayer() -> CA::MetalLayer*;

    private:
        MacOSWindow* m_Window;
        MacOSWindowDelegate* m_Delegate;
        MacOSContentView* m_View;
        CAMetalLayer* m_Layer;
    };
}

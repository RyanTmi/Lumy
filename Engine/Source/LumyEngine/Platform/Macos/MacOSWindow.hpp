#pragma once

#include "LumyEngine/Platform/MacOS/MacOSContentView.hpp"
#include "LumyEngine/Platform/MacOS/MacOSWindowDelegate.hpp"
#include "LumyEngine/Platform/Window.hpp"

#import <QuartzCore/CAMetalLayer.h>

@interface MacOSWindow : NSWindow
{}
@end

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

    public:
        auto FramebufferSize() const -> std::pair<UInt32, UInt32>;
        auto SetLayer(CAMetalLayer* layer) -> void;

    private:
        MacOSWindow* m_Window;
        MacOSWindowDelegate* m_Delegate;
        MacOSContentView* m_View;
        CAMetalLayer* m_Layer;
    };
}

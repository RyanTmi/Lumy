#pragma once

#include "LumyEngine/Core/Window.hpp"

// Cocoa window resize events
//
// Lumy window resize events are not added to the event queue because, for these events,
// the [NSApp sendEvent] function call initiates an internal loop that only concludes when
// the window resizing is completed, i.e., when the mouse button is released.
//
// As a result, window resize events accumulate in the queue and are dispatched all at once when the loop completes.
//
// Instead, these resize events are sent directly, causing all associated event listeners to be executed in sequence,
// during the Update function, potentially resulting in a temporary blockage of the application run loop.


namespace Lumy
{
    class MacOSWindow : public Window
    {
    public:
        MacOSWindow(const WindowProperties& properties);
        ~MacOSWindow() override;

        UInt16 GetWidth() const override;
        UInt16 GetHeight() const override;

        void Update() override;
        void* GetNativeWindow() const override;
    private:
        struct WindowHandle;
        UniquePtr<WindowHandle> m_WindowHandle;
    };
}

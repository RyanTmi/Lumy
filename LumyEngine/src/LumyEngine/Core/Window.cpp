#include "Window.hpp"

#if defined(LM_PLATFORM_MACOS)
    #include "LumyEngine/Platform/MacOS/MacOSWindow.hpp"
#endif

namespace Lumy
{
    Window* Window::Create(const WindowProperties& properties)
    {
    #if defined(LM_PLATFORM_MACOS)
        return new MacOSWindow(properties);
    #else
        LogError("Plateform not supported !");
        return nullptr;
    #endif
    }
}

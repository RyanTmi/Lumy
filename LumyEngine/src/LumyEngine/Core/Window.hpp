#pragma once

#include "Foundation.hpp"

namespace Lumy
{
    struct WindowProperties
    {
        const char* Title;

        UInt16 X = 0;
        UInt16 Y = 0;

        UInt16 Width = 1920;
        UInt16 Height = 1080;
        
        WindowProperties(const char* title = "Window Title")
            : Title(title)
        {
        }
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void Update() = 0;

        virtual UInt16 GetWidth() const = 0;
        virtual UInt16 GetHeight() const = 0;

        virtual void* GetNativeWindow() const = 0;
    protected:
        Window() = default;
    };
}

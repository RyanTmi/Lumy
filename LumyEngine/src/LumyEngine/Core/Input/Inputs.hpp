#pragma once

#include "LumyEngine/Core/Foundation.hpp"
#include "LumyEngine/Core/Module.hpp"
#include "LumyEngine/Core/Containers/Map.hpp"

#include "KeyCode.hpp"
#include "MouseButton.hpp"

namespace Lumy
{
    class Input : public Module
    {
    public:
        static Input& Get();
    public:
        void Initialize() override;
        void Update() override;
        void Shutdown() override;
    public:
        LUMY_API Bool8 IsKeyDown(KeyCode keyCode);
        LUMY_API Bool8 IsKeyUp(KeyCode keyCode);
        LUMY_API Bool8 WasKeyDown(KeyCode keyCode);
        LUMY_API Bool8 WasKeyUp(KeyCode keyCode);

        LUMY_API Bool8 IsButtonDown(MouseButton mouseButton);
        LUMY_API Bool8 IsButtonUp(MouseButton mouseButton);
        LUMY_API Bool8 WasButtonDown(MouseButton mouseButton);
        LUMY_API Bool8 WasButtonUp(MouseButton mouseButton);

        LUMY_API Float32 MouseX();
        LUMY_API Float32 MouseY();
        LUMY_API Float32 PreviousMouseX();
        LUMY_API Float32 PreviousMouseY();
    private:
        struct KeyboardState
        {
            UnorderedMap<KeyCode, Bool8> Keys;
        };

        struct MouseState
        {
            UnorderedMap<MouseButton, Bool8> Buttons;
            Float32 X;
            Float32 Y;
        };
    private:
        void OnKeyPressed(const struct KeyPressedEvent& event);
        void OnKeyReleased(const struct KeyReleasedEvent& event);

        void OnMousePressed(const struct MouseButtonPressedEvent& event);
        void OnMouseReleased(const struct MouseButtonReleasedEvent& event);
        void OnMouseMoved(const struct MouseMovedEvent& event);
        void OnMouseScrolled(const struct MouseScrolledEvent& event);
    private:
        KeyboardState m_PreviousKeyboardState;
        KeyboardState m_CurrentKeyboardState;
        MouseState m_PreviousMouseState;
        MouseState m_CurrentMouseState;
    };
}

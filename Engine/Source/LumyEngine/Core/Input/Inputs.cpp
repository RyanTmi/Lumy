#include "Inputs.hpp"

#include "LumyEngine/Core/Event/EventManager.hpp"
#include "LumyEngine/Core/Event/KeyEvent.hpp"
#include "LumyEngine/Core/Event/MouseEvent.hpp"

#include <unordered_map>

namespace Lumy
{
    struct InputContext
    {
        std::unordered_map<KeyCode, UInt8> Keys;

        std::unordered_map<MouseButton, bool> Buttons;
        Float64 MouseX = 0.0;
        Float64 MouseY = 0.0;
    };

    static InputContext* s_Context;

    auto Inputs::Initialize() -> bool
    {
        s_Context = new InputContext();
        return true;
    }

    auto Inputs::Update() -> void {}

    auto Inputs::Shutdown() -> void
    {
        delete s_Context;
    }

    auto Inputs::KeyPressed(KeyCode key) -> bool
    {
        return s_Context->Keys[key] > 0;
    }

    auto Inputs::ButtonPressed(MouseButton button) -> bool
    {
        return s_Context->Buttons[button];
    }

    auto Inputs::MousePosition() -> std::pair<Float64, Float64>
    {
        return std::make_pair(s_Context->MouseX, s_Context->MouseY);
    }

    auto Inputs::MouseX() -> Float64
    {
        return s_Context->MouseX;
    }

    auto Inputs::MouseY() -> Float64
    {
        return s_Context->MouseY;
    }

    auto Inputs::ProcessKey(KeyCode key, bool pressed) -> void
    {
        if (pressed)
        {
            s_Context->Keys[key] = 1;
            EventManager::Fire<KeyPressEvent>(key);
        }
        else
        {
            s_Context->Keys[key] = 0;
            EventManager::Fire<KeyReleaseEvent>(key);
        }
    }

    auto Inputs::ProcessButton(MouseButton button, bool pressed) -> void
    {
        s_Context->Buttons[button] = pressed;

        if (pressed)
        {
            EventManager::Fire<MouseButtonPressEvent>(button);
        }
        else
        {
            EventManager::Fire<MouseButtonReleaseEvent>(button);
        }
    }

    auto Inputs::ProcessMouseMove(Float64 x, Float64 y) -> void
    {
        s_Context->MouseX = x;
        s_Context->MouseY = y;
        EventManager::Fire<MouseMoveEvent>(x, y);
    }

    auto Inputs::ProcessMouseScroll(Float64 deltaX, Float64 deltaY) -> void
    {
        EventManager::Fire<MouseScrollEvent>(deltaX, deltaY);
    }
}

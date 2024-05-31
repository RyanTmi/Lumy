#pragma once

#include "LumyEngine/Core/Types.hpp"
#include "KeyCode.hpp"
#include "MouseButton.hpp"

#include <utility>

namespace Lumy
{
    class Inputs final
    {
    public:
        Inputs() = delete;

    public:
        static auto Initialize() -> bool;
        static auto Update() -> void;
        static auto Shutdown() -> void;

    public:
        static auto KeyPressed(KeyCode key) -> bool;
        static auto ButtonPressed(MouseButton button) -> bool;

        static auto MousePosition() -> std::pair<Float64, Float64>;
        static auto MouseX() -> Float64;
        static auto MouseY() -> Float64;

    public:
        static auto ProcessKey(KeyCode key, bool pressed) -> void;
        static auto ProcessButton(MouseButton button, bool pressed) -> void;
        static auto ProcessMouseMove(Float64 x, Float64 y) -> void;
        static auto ProcessMouseScroll(Float64 x, Float64 y) -> void;
    };
}

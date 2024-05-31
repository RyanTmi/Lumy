#include "Game.hpp"

#include "LumyEngine/Core/Input/Inputs.hpp"

auto Game::Initialize() -> bool
{
    return true;
}

auto Game::Shutdown() -> void {}

auto Game::Update(Float64 deltaTime) -> bool
{
    if (Inputs::KeyPressed(KeyCode::F))
    {
        std::cout << "interact" << std::endl;
    }

    return true;
}

auto Game::Render(Float64 deltaTime) -> bool
{
    return true;
}

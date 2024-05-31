#include "Game.hpp"

#include <LumyEngine/EntryPoint.hpp>

Lumy::Application* Lumy::MakeApplication()
{
    Lumy::ApplicationSpecification applicationSpecification(
        {"Lumy test game", Rectangle<UInt32>(0, 0, 900, 600)});
    return new Game(applicationSpecification);
}

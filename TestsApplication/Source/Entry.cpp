#include "Game.hpp"

#include <LumyEngine/EntryPoint.hpp>

Lumy::Application* Lumy::MakeApplication()
{
    const char* applicationName = "Lumy test game";
    Lumy::WindowSpecification windowSpec(applicationName, {0, 0, 900, 600});
    Lumy::ApplicationSpecification applicationSpecification(applicationName, windowSpec);

    return new Game(applicationSpecification);
}

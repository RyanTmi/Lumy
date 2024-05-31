#pragma once

#include "LumyEngine/Core/Application.hpp"
#include "LumyEngine/Core/Engine.hpp"

auto main(int argc, char** argv) -> int
{
    using namespace Lumy;

    Application* application = MakeApplication();

    if (!Engine::Initialize(*application))
    {
        Log::Fatal("Failed to Initialize Engine");
        return EXIT_FAILURE;
    }
    Engine::Run();
    Engine::Shutdown();

    return EXIT_SUCCESS;
}

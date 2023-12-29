/**
 * @file EntryPoint.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief 
 * @version 0.2
 * @date 2023-11-20
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#include "Engine.hpp"
#include "LumyEngine/Debug/Profiler.hpp"

int main(int argc, const char** argv)
{
    LM_PROFILE_BEGIN_SESSION("Startup", "LumyProfile-Startup");
    Lumy::Engine& engine = Lumy::Engine::Create();
    engine.Initialize(Lumy::ApplicationCreate());
    LM_PROFILE_END_SESSION();

    LM_PROFILE_BEGIN_SESSION("Runtime", "LumyProfile-Runtime");
    engine.Run();
    LM_PROFILE_END_SESSION();

    LM_PROFILE_BEGIN_SESSION("Shutdown", "LumyProfile-Shutdown");
    engine.Shutdown();
    LM_PROFILE_END_SESSION();
}

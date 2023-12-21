/**
 * @file EntryPoint.hpp
 * @author Ryan Timeus (timeusryan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Lumy Game Engine is Copyright (c) Ryan Timeus 2023-2024
 * 
 */

#pragma once

#include "Foundation.hpp"
#include "Application.hpp"

extern Lumy::Application* Lumy::CreateApplication();

int main(int argc, const char** argv)
{
    Lumy::Log::Initialize();

    LM_PROFILE_BEGIN_SESSION("Startup", "LumyProfile-Startup");
    auto app = Lumy::CreateApplication();
    LM_PROFILE_END_SESSION();

    LM_PROFILE_BEGIN_SESSION("Runtime", "LumyProfile-Runtime");
    app->Run();
    LM_PROFILE_END_SESSION();

    LM_PROFILE_BEGIN_SESSION("Shutdown", "LumyProfile-Shutdown");
    delete app;
    LM_PROFILE_END_SESSION();
}

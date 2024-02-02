#pragma once

#include "Module.hpp"

#include "Foundation.hpp"

namespace Lumy
{
    enum ModuleType
    {
        ModuleType_Memory,
        ModuleType_Logging,
        ModuleType_Platform,
        ModuleType_Event,
        ModuleType_Input,
        ModuleType_Renderer,

        ModuleType_Max
    };

    class ModuleManager final
    {
    public:
        ModuleManager();
    public:
        void Initialize();
        void Update();
        void Shutdown();
    private:
        Array<UniquePtr<Module>, ModuleType_Max> m_Modules;
    };
}
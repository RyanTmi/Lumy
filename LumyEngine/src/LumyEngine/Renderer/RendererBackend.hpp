#pragma once

#include "LumyEngine/Core/Module.hpp"

namespace Lumy
{
    class RendererBackend : public Module
    {
    public:
        static RendererBackend* Create();
    public:
        virtual void Render() = 0;
    };
}

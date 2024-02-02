#pragma once

#include "LumyEngine/Renderer/Metal/MetalBackend.hpp"

#include <MetalKit/MetalKit.hpp>

namespace Lumy
{
    class MacOSViewDelegate : public MTK::ViewDelegate
    {
    public:
        MacOSViewDelegate(MetalBackend* metalBackend);
    private:
        MetalBackend* m_MetalBackend;
    };
}

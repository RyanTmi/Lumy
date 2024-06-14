#include "LumyEngine/Renderer/Metal/MetalContext.hpp"

#include "LumyEngine/Core/Engine.hpp"
#include "LumyEngine/Debug/Log.hpp"

#include <fstream>
#include <sstream>

namespace Lumy
{
    auto MetalContext::Initialize() -> bool
    {
        if (!m_Device.CreateSystemDefault())
        {
            return false;
        }

        auto& window = Engine::GetWindow();
        auto fbSize = window.GetFramebufferSize();
        m_Layer = reinterpret_cast<CA::MetalLayer*>(window.GetSurface());
        m_Layer->setDevice(m_Device.Handle());
        m_Layer->setDrawableSize(CGSizeMake(fbSize.first, fbSize.second));
        m_Layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
        m_Layer->setFramebufferOnly(true);

        m_MainRenderPass.Create(&m_Device, Color::Purple);

        return true;
    }

    auto MetalContext::Shutdown() -> void
    {
        m_MainRenderPass.Destroy();

        m_Device.Destroy();
    }

    auto MetalContext::Resize(UInt32 width, UInt32 height) -> void
    {
        m_Layer->setDrawableSize(CGSizeMake(width, height));
    }

    auto MetalContext::NextDrawable() -> bool
    {
        m_Drawable = m_Layer->nextDrawable();
        return m_Drawable != nullptr;
    }
}

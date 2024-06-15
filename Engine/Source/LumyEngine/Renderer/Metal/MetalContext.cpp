#include "LumyEngine/Renderer/Metal/MetalContext.hpp"

#include "LumyEngine/Core/Engine.hpp"
#include "LumyEngine/Debug/Log.hpp"

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

        NS::URL* url = NS::URL::fileURLWithPath(
            NS::String::string("Assets/Shaders/Metal/default.metallib", NS::ASCIIStringEncoding));
        NS::Error* error;
        m_Library = m_Device.Handle()->newLibrary(url, &error);
        if (error)
        {
            return false;
        }
        url->release();

        m_Shader.CreateFunctions(m_Library, "VertexObject", "FragmentObject");
        m_GraphicsPipeline.Create(m_Device, m_Shader, m_Layer->pixelFormat());

        // TODO: Temporary
        static Vector3 quad[] = {
            {-0.5f, -0.5, 0.0f},
            { 0.5f, -0.5, 0.0f},
            { 0.5f,  0.5, 0.0f},
            {-0.5f,  0.5, 0.0f},
        };
        static Color colors[] = {
            Color::Blue,
            Color::Red,
            Color::Yellow,
            Color::Green,
        };
        static UInt16 indices[] = {0, 1, 2, 0, 2, 3};

        m_VertexBuffer = m_Device.Handle()->newBuffer(quad, sizeof(quad), MTL::ResourceStorageModeShared);
        m_VertexColorBuffer = m_Device.Handle()->newBuffer(colors, sizeof(colors), MTL::ResourceStorageModeShared);
        m_IndexBuffer = m_Device.Handle()->newBuffer(indices, sizeof(indices), MTL::ResourceStorageModeShared);
        // TODO: End temporary
        
        return true;
    }

    auto MetalContext::Shutdown() -> void
    {
        m_IndexBuffer->release();
        m_VertexColorBuffer->release();
        m_VertexBuffer->release();

        m_GraphicsPipeline.Destroy();

        m_Shader.VertexFunction()->release();
        m_Shader.FragmentFunction()->release();

        m_Library->release();

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

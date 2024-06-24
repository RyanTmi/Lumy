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

        m_MainRenderPass.Create(&m_Device, Color(0.2f, 0.2f, 0.2f, 1.0f));

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
        static Vector3f quad[] = {
            {10 * -0.5f,10*  -0.5f, 10.0f},
            {10 * 0.5f, 10* -0.5f,  10.0f},
            {10 * 0.5f, 10* 0.5f,   10.0f},
            {10 * -0.5f,10*  0.5f,  10.0f},
            // {2.5f, 2.5f, 1.5f},
            // {3.5f, 2.5f, 1.5f},
            // {3.5f, 3.5f, 1.5f},
            // {2.5f, 3.5f, 1.5f},
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
        m_UniformsBuffer = m_Device.Handle()->newBuffer(2 * sizeof(Matrix4x4f), MTL::ResourceStorageModeShared);
        // TODO: End temporary

        return true;
    }

    auto MetalContext::Shutdown() -> void
    {
        m_UniformsBuffer->release();
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

    auto MetalContext::UpdateUniforms(const Matrix4x4f& projection, const Matrix4x4f& view) -> void
    {
        m_ViewProjection = view * projection;

        Matrix4x4f data[1] = {m_ViewProjection};
        std::memcpy(m_UniformsBuffer->contents(), data, sizeof(data));
        m_UniformsBuffer->didModifyRange(NS::Range(0, sizeof(data)));
    }

    auto MetalContext::FrameBufferSize() const -> Vector2f
    {
        auto width = static_cast<Float32>(m_Layer->drawableSize().width);
        auto height = static_cast<Float32>(m_Layer->drawableSize().height);
        return {width, height};
    }
}

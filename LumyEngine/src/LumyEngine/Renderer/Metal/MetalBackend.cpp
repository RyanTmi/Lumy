#include "MetalBackend.hpp"

#include "LumyEngine/Core/Foundation.hpp"
#include "LumyEngine/Platform/MacOS/MacOSScopeAutoReleasePool.hpp"

#include <AppKit/AppKit.hpp>

#include <fstream>
#include <sstream>

namespace Lumy
{
    RendererBackend* RendererBackend::Create()
    {
        return new MetalBackend();
    }

    void MetalBackend::Initialize()
    {
        Log::Info("Initialize Metalbackend");

        Log::Trace("  Create System Default Device");
        m_Device = MTL::CreateSystemDefaultDevice();

        if (m_Device == nullptr)
        {
            Log::Fatal("Can not create system default device");
        }

        // https://developer.apple.com/documentation/metal/mtldevice/device_inspection
        // TODO: complete
        Log::Debug("Device's feature support:");
        Log::Debug("  metal3:                           {}", m_Device->supportsFamily(MTL::GPUFamilyMetal3));
        Log::Debug("Device's informations:");
        Log::Debug("  name:                             {}", m_Device->name()->cString(NS::UTF8StringEncoding));
        Log::Debug("  architecture:                     {}", m_Device->architecture()->name()->cString(NS::UTF8StringEncoding));
        Log::Debug("  location:                         {}", m_Device->location());
        Log::Debug("  location number:                  {}", m_Device->locationNumber());
        Log::Debug("  low power:                        {}", m_Device->lowPower());
        Log::Debug("  removable:                        {}", m_Device->removable());
        Log::Debug("  headless:                         {}", m_Device->headless());
        Log::Debug("  peer group ID:                    {}", m_Device->peerGroupID());
        Log::Debug("  peer count:                       {}", m_Device->peerCount());
        Log::Debug("  peer index:                       {}", m_Device->peerIndex());
        Log::Debug("Device's Render Support");
        Log::Debug("  raytracing:                       {}", m_Device->supportsRaytracing());
        Log::Debug("  primitive motion blur:            {}", m_Device->supportsPrimitiveMotionBlur());
        Log::Debug("  raytracing from render:           {}", m_Device->supportsRaytracingFromRender());
        Log::Debug("Device's Compute Support");
        Log::Debug("  max thread group memory length:   {}", m_Device->maxThreadgroupMemoryLength());
        Log::Debug("  max threads per thread group:     {}", m_Device->maxThreadsPerThreadgroup().width);
        Log::Debug("Device's memory:");
        Log::Debug("  current allocated size:           {}", m_Device->currentAllocatedSize());
        Log::Debug("  recommended max working set size: {}", m_Device->recommendedMaxWorkingSetSize());
        Log::Debug("  max transfer rate:                {}", m_Device->maxTransferRate());
        
        Log::Trace("  Create New Command Queue");
        m_CommandQueue = m_Device->newCommandQueue();

        Log::Trace("  Build Shaders");
        BuildShaders();
    }
    void MetalBackend::Update()
    {

    }

    void MetalBackend::Shutdown()
    {
        Log::Info("Shutdown Metalbackend");

        Log::Trace("  Releasing Render Pipeline State");
        m_RenderPipelineState->release();

        Log::Trace("  Releasing Command Queue");
        m_CommandQueue->release();

        Log::Trace("  Releasing Metal Device");
        m_Device->release();
    }


    void MetalBackend::Render()
    {

    }

    void MetalBackend::Draw(MTK::View* view)
    {
        MTL::CommandBuffer* commandBuffer = m_CommandQueue->commandBuffer();
        MTL::RenderPassDescriptor* renderPass = view->currentRenderPassDescriptor();
        // renderPass->colorAttachments()->object(0)->setTexture(view->currentDrawable()->texture());
        renderPass->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
        renderPass->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.2, 0.5, 0.3, 1.0));

        const Array<Float32, 12> triangles = {
            -0.75, -0.75, 0.0,
             0.75,  0.75, 0.0,
             0.75, -0.75, 0.0,
            -0.75,  0.75, 0.0
        };
        
        const Array<Int16, 6> indices = {
            0, 1, 3,
            0, 1, 2
        };

        auto vertexBuffer = NS::TransferPtr(m_Device->newBuffer(triangles.data(), sizeof(Float32) * triangles.size(), MTL::ResourceStorageModeShared));
        auto indexBuffer = NS::TransferPtr(m_Device->newBuffer(indices.data(), sizeof(UInt16) * indices.size(), MTL::ResourceStorageModeShared));

        MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(renderPass);
        encoder->setRenderPipelineState(m_RenderPipelineState);
        encoder->setVertexBuffer(vertexBuffer.get(), 0, 0);
        // encoder->setTriangleFillMode(MTL::TriangleFillModeLines);

        // encoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));
        encoder->drawIndexedPrimitives(MTL::PrimitiveTypeTriangle, indices.size(), MTL::IndexTypeUInt16, indexBuffer.get(), 0);
        encoder->endEncoding();

        commandBuffer->presentDrawable(view->currentDrawable());
        commandBuffer->commit();
    }

    MTL::Device* MetalBackend::GetDevice() const
    {
        return m_Device;
    }

    MTL::CommandQueue* MetalBackend::GetCommandQueue()const
    {
        return m_CommandQueue;
    }
    
    void MetalBackend::BuildShaders()
    {
        const char* shaderPath = "assets/shaders/Builtin.Triangle.metal";
        std::ifstream shaderFile(shaderPath);
        if (!shaderFile.is_open())
        {
            Log::Error("Can not open shader file");
            return;
        }
        std::stringstream reader;
        reader << shaderFile.rdbuf();
        NS::String* sourceCode = NS::String::string(reader.str().c_str(), NS::StringEncoding::UTF8StringEncoding);

        NS::Error* error = nullptr;
        auto library = NS::TransferPtr(m_Device->newLibrary(sourceCode, nullptr, &error));
        if (library.get() == nullptr)
        {
            Log::Error("{}", error->localizedDescription()->utf8String());
        }

        auto vertexFunction = NS::TransferPtr(library->newFunction(NS::String::string("vertexMain", NS::UTF8StringEncoding)));
        auto fragmentFunction = NS::TransferPtr(library->newFunction(NS::String::string("fragmentMain", NS::UTF8StringEncoding)));

        auto renderPipelineDescriptor = NS::TransferPtr(MTL::RenderPipelineDescriptor::alloc()->init());
        renderPipelineDescriptor->setVertexFunction(vertexFunction.get());
        renderPipelineDescriptor->setFragmentFunction(fragmentFunction.get());
        renderPipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
        
        error = nullptr;
        m_RenderPipelineState = m_Device->newRenderPipelineState(renderPipelineDescriptor.get(), &error);
        if (m_RenderPipelineState == nullptr)
        {
            Log::Error("{}", error->localizedDescription()->utf8String());
        }
    }
}

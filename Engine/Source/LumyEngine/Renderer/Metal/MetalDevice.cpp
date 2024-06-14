#include "MetalDevice.hpp"

#include "LumyEngine/Debug/Log.hpp"

namespace Lumy
{
    MetalDevice::~MetalDevice()
    {
        Destroy();
    }

    auto MetalDevice::CreateSystemDefault() -> bool
    {
        m_Device = MTL::CreateSystemDefaultDevice();
        if (!m_Device)
        {
            Log::Error("Metal: Failed to create system default device");
            return false;
        }

        m_CommandQueue = m_Device->newCommandQueue();
        if (!m_CommandQueue)
        {
            Log::Error("Metal: Failed to create command queue");
            return false;
        }
        m_CommandQueue->setLabel(NS::String::string("Graphics command queue", NS::UTF8StringEncoding));

        return true;
    }

    // TODO: If multiple devices are available
    auto MetalDevice::Create() -> bool
    {
        return false;
    }

    auto MetalDevice::Destroy() -> void
    {
        if (m_CommandQueue)
        {
            m_CommandQueue->release();
        }

        if (m_Device)
        {
            m_Device->release();
        }
    }
}

#include "MetalDevice.hpp"

namespace Lumy
{
    MTL::Device* MetalDevice::GetDevice()
    {
        NS::Array* devices = MTL::CopyAllDevices();
        if (devices->count() == 0)
        {
            Log::Fatal("No devices");
            return nullptr;
        }

        Log::Info("{} device(s) found", devices->count());
        for (UInt8 i = 0; i < devices->count(); ++i)
        {
            MTL::Device* device = devices->object<MTL::Device>(i);
            if (IsValidDevice(device))
            {
                m_Device = device;
                return m_Device;
            }
        }
        return nullptr;
    }
    
    Bool8 MetalDevice::IsValidDevice(const MTL::Device* device)
    {
        // TODO: Test
        return device->supportsRaytracing();
    }
}

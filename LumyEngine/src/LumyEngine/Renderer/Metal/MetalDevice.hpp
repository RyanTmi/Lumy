#pragma once

#include "LumyEngine/Core/Foundation.hpp"

#include "Metal/MTLDevice.hpp"

namespace Lumy
{
    class MetalDevice
    {
    public:
        MetalDevice() = default;
    public:
        MTL::Device* GetDevice();
    private:
        static Bool8 IsValidDevice(const MTL::Device* device);
    private:
        MTL::Device* m_Device;
    };
}

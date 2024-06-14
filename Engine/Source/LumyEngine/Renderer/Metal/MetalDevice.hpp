#pragma once

#include <Metal/MTLDevice.hpp>
#include <Metal/MTLCommandQueue.hpp>

namespace Lumy
{
    class MetalDevice final
    {
    public:
        MetalDevice() = default;
        ~MetalDevice();

    public:
        auto CreateSystemDefault() -> bool;
        auto Create() -> bool;
        auto Destroy() -> void;

    public:
        auto Handle() const -> MTL::Device* { return m_Device; }

        auto CommandQueue() -> MTL::CommandQueue* { return m_CommandQueue; }

    private:
        MTL::Device* m_Device;
        MTL::CommandQueue* m_CommandQueue;
    };
}

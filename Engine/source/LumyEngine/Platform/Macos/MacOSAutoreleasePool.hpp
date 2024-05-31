#pragma once

#include <Foundation/NSAutoreleasePool.hpp>
#include <Foundation/NSSharedPtr.hpp>

namespace Lumy
{
    class AutoreleasePool
    {
    public:
        AutoreleasePool()
            : m_Pool(NS::TransferPtr(NS::AutoreleasePool::alloc()->init()))
        {}

    private:
        NS::SharedPtr<NS::AutoreleasePool> m_Pool;
    };
}

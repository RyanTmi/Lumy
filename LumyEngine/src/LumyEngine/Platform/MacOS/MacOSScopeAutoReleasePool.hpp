#pragma once

#include <Foundation/NSAutoreleasePool.hpp>

namespace Lumy
{
    class MacOSScopeAutoReleasePool
    {
    public:
        MacOSScopeAutoReleasePool();
        ~MacOSScopeAutoReleasePool();
    private:
        NS::AutoreleasePool* m_AutoReleasePool;
    };
}

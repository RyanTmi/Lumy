#include "MacOSScopeAutoReleasePool.hpp"

namespace Lumy
{
    MacOSScopeAutoReleasePool::MacOSScopeAutoReleasePool()
    {
        m_AutoReleasePool = NS::AutoreleasePool::alloc()->init();
    }

    MacOSScopeAutoReleasePool::~MacOSScopeAutoReleasePool()
    {
        m_AutoReleasePool->release();
    }
}

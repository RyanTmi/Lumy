#include "MacOSScopeAutoReleasePool.hpp"

#import <Foundation/Foundation.h>

namespace Lumy
{
    MacOSScopeAutoReleasePool::MacOSScopeAutoReleasePool()
    {
        m_AutoReleasePool = [[NSAutoreleasePool alloc] init];
    }

    MacOSScopeAutoReleasePool::~MacOSScopeAutoReleasePool()
    {
        Drain();
    }

    void MacOSScopeAutoReleasePool::Drain() const
    {
        [m_AutoReleasePool drain];
    }
}

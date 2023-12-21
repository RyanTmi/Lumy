#pragma once

#if defined(__OBJC__)

@class NSAutoreleasePool;
using AutoReleasePoolPointer = NSAutoreleasePool*;

#else // If C++

using AutoReleasePoolPointer = void*;

#endif

namespace Lumy
{
    class MacOSScopeAutoReleasePool
    {
    public:
        MacOSScopeAutoReleasePool();
        ~MacOSScopeAutoReleasePool();
    public:
        void Drain() const;
    private:
        AutoReleasePoolPointer m_AutoReleasePool;
    };
}

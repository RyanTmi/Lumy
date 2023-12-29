#include "MacOSViewDelegate.hpp"

namespace Lumy
{
    MacOSViewDelegate::MacOSViewDelegate(MetalBackend* metalBackend)
         : m_MetalBackend(metalBackend)
    {
    }

    void MacOSViewDelegate::drawInMTKView(MTK::View* view)
    {
        m_MetalBackend->Draw(view);
    }
}

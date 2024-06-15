#include "MetalShader.hpp"

#include "LumyEngine/Debug/Log.hpp"

namespace Lumy
{
    auto MetalShader::CreateFunctions(MTL::Library* library, const char* vertex, const char* fragment) -> bool
    {
        m_VertexFunction = library->newFunction(NS::String::string(vertex, NS::ASCIIStringEncoding));
        if (!m_VertexFunction)
        {
            return false;
        }

        m_FragmentFunction = library->newFunction(NS::String::string(fragment, NS::ASCIIStringEncoding));
        if (!m_FragmentFunction)
        {
            return false;
        }

        return true;
    }

    auto MetalShader::VertexFunction() const -> MTL::Function*
    {
        return m_VertexFunction;
    }

    auto MetalShader::FragmentFunction() const -> MTL::Function*
    {
        return m_FragmentFunction;
    }
}

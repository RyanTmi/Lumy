#pragma once

#include <Metal/Metal.hpp>

namespace Lumy
{
    class MetalShader
    {
    public:
        MetalShader() = default;

    public:
        auto CreateFunctions(MTL::Library* library, const char* vertex, const char* fragment) -> bool;

        auto VertexFunction() const -> MTL::Function*;
        auto FragmentFunction() const -> MTL::Function*;

    private:
        MTL::Function* m_VertexFunction;
        MTL::Function* m_FragmentFunction;
    };
}

#include <metal_stdlib>
using namespace metal;

[[vertex]] float4 vertexMain(const constant packed_float3* triangleVertices [[buffer(0)]],
                               const ushort vertexIndex [[vertex_id]])
{
    return float4(triangleVertices[vertexIndex], 1.0f);
}

[[fragment]] float4 fragmentMain()
{
    return float4(1.0, 0.0, 0.0, 1.0);
}

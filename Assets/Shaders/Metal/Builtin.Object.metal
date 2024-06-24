#include <metal_stdlib>

using namespace metal;

struct VertexIn
{
    float3 Position [[attribute(0)]];
    float4 Color    [[attribute(1)]];
};

struct Uniform
{
    float4x4 ViewProjection;
};

struct VertexOut
{
    float4 Position [[position]];
    float4 Color;
};

vertex VertexOut VertexObject(const VertexIn in [[stage_in]], constant Uniform& uniform [[buffer(10)]])
{
    float4 position = uniform.ViewProjection * float4(in.Position, 1.0f);
    // float4 position = float4(in.Position, 1.0f);
    return { .Position = position, .Color = in.Color };
}

fragment float4 FragmentObject(VertexOut in [[stage_in]])
{
    return in.Color;
}

#include <metal_stdlib>
using namespace metal;

struct VertexIn
{
    float4 Position [[attribute(0)]];
    float4 Color [[attribute(1)]];
};

struct VertexOut
{
    float4 Position [[position]];
    float4 Color;
};

vertex VertexOut VertexObject(const VertexIn in [[stage_in]])
{
    VertexOut out;
    out.Position = in.Position;
    out.Color = in.Color;
    return out;
}

fragment float4 FragmentObject(VertexOut in [[stage_in]])
{
    return in.Color;
}

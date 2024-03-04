cbuffer ConstantBuffer : register(b0)
{
    matrix WorldViewProjection;
    float4x4 gTexTransform;
}

struct VertexInput
{
    float3 position : POSITION;
    float4 color : COLOR;
    float2 TexC : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 TexC : TEXCOORD;
};

VertexOutput vs_main(VertexInput input)
{
    VertexOutput output;
    output.position = mul(float4(input.position, 1.0f), WorldViewProjection);
    output.color = input.color;
    return output;
}

float4 ps_main(VertexOutput input) : SV_TARGET
{
    return input.color;
}
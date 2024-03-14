Texture2D gTex : register(t0);
SamplerState gSampler : register(s0);


cbuffer cbObj : register(b0)
{
    matrix World;
}

cbuffer cbCam : register(b1)
{
    matrix ViewProjection;
}

struct VertexInput
{
    float3 position : POSITION;
    float2 TexC : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 TexC : TEXCOORD;
};

VertexOutput vs_main(VertexInput input)
{
    VertexOutput output;
    float4 position = mul(float4(input.position, 1.0f), World);
    output.position = mul(position, ViewProjection);
    output.TexC = input.TexC;
    return output;
}

float4 ps_main(VertexOutput input) : SV_TARGET
{
    return gTex.Sample(gSampler, input.TexC);
}
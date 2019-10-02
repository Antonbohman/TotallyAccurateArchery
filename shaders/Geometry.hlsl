struct GS_IN
{
    float4 Pos : POSITION;
    float3 Color : COLOR;
    float2 UV : TEXCOORD0;
};

struct PS_INOUT
{
    float4 Pos : POSITION;
    float3 Color : COLOR;
    float2 UV : TEXCOORD0;
};

cbuffer GS_CB_FLAGS : register(b0)
{
    bool SplitView;
    uint RenderMode;
};

cbuffer GS_CB_CAMERA : register(b1)
{
    float4 CameraOrigin;
    float4 CameraFocus;
};

[maxvertexcount(12)]
void GS_main(
	triangle GS_IN input[3],
	inout TriangleStream<PS_INOUT> OutputStream)
{
    PS_INOUT output = (PS_INOUT) 0;
    
    OutputStream.Append(output);
}
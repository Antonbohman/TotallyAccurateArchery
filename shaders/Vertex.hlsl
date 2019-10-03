struct VS_IN
{
    float3 Pos : POSITION;
    float4 Colour : COLOUR;
    float2 UV : UV_POS;
};

struct VS_OUT
{
    float4 Pos_H : POSITION;
    float4 Pos_W : SV_POSITION;
    float4 Colour : COLOUR;
    float2 UV : TEXCOORD0;
};

VS_OUT VS_main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.Pos_H = float4(input.Pos,1.0f);
    output.Pos_W = output.Pos_H;
    output.Colour = input.Colour;
    output.UV = input.UV;

    return output;
}
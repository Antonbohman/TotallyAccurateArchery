struct GS_INOUT
{
    float4 Pos_H : POSITION;
    float4 Pos_W : SV_POSITION;
    float4 Colour : COLOUR;
    float2 UV : TEXCOORD0;
};

[maxvertexcount(12)]
void GS_main(
	triangle GS_INOUT input[3],
	inout TriangleStream<GS_INOUT> OutputStream)
{
    GS_INOUT output = (GS_INOUT) 0;

    for (uint i = 0; i < 3; i++)
    {
        output.Pos_W = input[i].Pos_W;
        output.Pos_H = input[i].Pos_H;
        output.Colour = input[i].Colour;
        output.UV = input[i].UV;

        OutputStream.Append(output);
    }
}
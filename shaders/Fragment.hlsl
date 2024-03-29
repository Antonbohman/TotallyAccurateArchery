struct PS_IN
{
    float4 Pos_H : POSITION;
    float4 Pos_W : SV_POSITION;
    float4 Colour : COLOUR;
    float2 UV : TEXCOORD;
};

Texture2D Texture : register(t0);

SamplerState Sampling : register(s0);

cbuffer PS_CB_OPTIONS: register(b0)
{
    float wireframe;
    float textureLoaded;
};

float4 PS_main(PS_IN input) : SV_TARGET
{
    float4 pixelColour;
    
    if (wireframe)
        pixelColour = float4(input.Colour);
    else if (textureLoaded)
    {
        pixelColour = Texture.Sample(Sampling, input.UV);
        pixelColour = float4(
            pixelColour.r * input.Colour.r,
            pixelColour.g * input.Colour.g,
            pixelColour.b * input.Colour.b,
            pixelColour.a * input.Colour.a
        );
    }
    else
        pixelColour = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
    return pixelColour;
};
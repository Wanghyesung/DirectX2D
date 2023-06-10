struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};


//∑ª¥ı ≈∏∞Ÿ¿∏∑Œ
float4 main(VSOut In) : SV_TARGET
{
    return In.Color;
}
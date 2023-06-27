struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

Texture2D albedoTexture : register(t0);
//SamplerState������ ������ �ȼ� ũ�⸦ ���� �� �ۿ� ���� �ؽ����� �� �ȼ� ���̸� ��� ó���� ������ �����ϴ� State�� ���̴�. (UV��ǥ�� ��ȯ)
SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

//���� Ÿ������
float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float4) 0.f;
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    //������ UV��ǥ�� �ؽ��� �����ؼ� ����
    
    return color;
}
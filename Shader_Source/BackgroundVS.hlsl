struct VSIn
{
    //시멘틱으로 구분
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

cbuffer Transform : register(b0)
{
    //float4 Position;
    //열 우선 행렬
    row_major matrix World;
    row_major matrix View;
    row_major matrix Projection;
}


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f; //초기화
    
    //월드행렬
    float4 world = mul(float4(In.Pos, 1.f), World);
    //월드행렬 * 뷰행렬
    float4 view = mul(world, View);
    //뷰행렬 * 투영행렬
    float4 proj = mul(view, Projection);
    
    Out.Pos = proj;
    Out.Color = In.Color;
    Out.UV = In.UV;
    //Out.UV.x *= -1;

    return Out;
}
